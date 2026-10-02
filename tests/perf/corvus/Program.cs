/*
 * Corvus Benchmarking harness
 */
using System.Diagnostics;
using Corvus.Text.Json;
using Corvus.Text.Json.RuntimeEvaluator;

namespace CorvusBench;

internal static class Program
{
    private static int Main(string[] args)
    {
        if (args.Length == 0 || args[0] is "-h" or "--help" or "help")
        {
            Console.Error.WriteLine("""
                corvus-bench - Corvus 5 benchmarking

                Usage:
                  compile [--out <out.cjsp>] [--entry-point <ref>]
                                  [--dialect <name>] [--format] <schema.json>
                  validate [--jsonl] [--times <times>] [--verbose]
                                  [--diagnostics] <program.cjsp> <file>...
            """);
            return 0;
        }

        return args[0] switch
        {
            "compile" => Compile(args[1..]),
            "validate" => Validate(args[1..]),
            _ => throw new Exception($"Unknown command '{args[0]}'."),
        };
    }

    // ------------------------------------------------------------------ compile

    private static int Compile(string[] args)
    {
        string? schemaPath = null;
        string? outPath = null;
        string? entryPoint = null;
        bool assertFormat = false;
        JsonSchemaDialect? dialect = null;

        // fuzzy direct option/argument parser
        for (int i = 0; i < args.Length; i++)
        {
            switch (args[i])
            {
                case "-o" or "--out":
                    outPath = args[++i];
                    break;
                case "-e" or "--entry-point":
                    entryPoint = args[++i];
                    break;
                case "-f" or "--format":
                    assertFormat = true;
                    break;
                case "-nf" or "--no-format":
                    assertFormat = false;
                    break;
                case "-d" or "--dialect":
                    string name = args[++i];
                    if (!Enum.TryParse(name, ignoreCase: true, out JsonSchemaDialect parsed))
                        throw new Exception ($"Unknown dialect '{name}'. Valid: {string.Join(", ", Enum.GetNames<JsonSchemaDialect>())}.");
                    dialect = parsed;
                    break;
                default:
                    if (args[i].StartsWith('-'))
                        throw new Exception($"Unknown option '{args[i]}'.");
                    if (schemaPath is not null)
                        throw new Exception("compile takes exactly one schema file.");
                    schemaPath = args[i];
                    break;
            }
        }

        if (schemaPath is null)
            throw new Exception("compile requires a schema file.");

        string fullPath = Path.GetFullPath(schemaPath);
        byte[] schemaBytes = File.ReadAllBytes(fullPath);
        string baseDir = Path.GetDirectoryName(fullPath)!;

        var options = new JsonSchemaEvaluatorOptions
        {
            BaseUri = new Uri(fullPath).AbsoluteUri,
            AssertFormat = assertFormat ? true : null,
            AssertFormatInLegacyDrafts = assertFormat,

            // Resolve relative $ref targets (file: URIs) from disk so that the image is self-contained.
            DocumentResolver = FileResolver,
        };

        if (dialect is { } d)
            options.DefaultDialect = d;

        using var evaluator =
            entryPoint is null
                ? JsonSchemaEvaluator.Compile(schemaBytes, options)
                : JsonSchemaEvaluator.Compile(schemaBytes, entryPoint, options);

        byte[] image = evaluator.ToProgramImage();

        outPath ??= Path.ChangeExtension(fullPath, ".cjsp");
        File.WriteAllBytes(outPath, image);

        // summary output
        Console.WriteLine($"schema:        {fullPath}");
        Console.WriteLine($"image:         {Path.GetFullPath(outPath)}");
        Console.WriteLine($"image size:    {image.Length:N0} bytes (schema text: {schemaBytes.Length:N0} bytes)");
        Console.WriteLine($"nodes:         {evaluator.NodeCount:N0}");
        Console.WriteLine($"resources:     {evaluator.ResourceCount:N0}");
        Console.WriteLine($"dynamic scope: {evaluator.UsesDynamicScope}");

        return 0;

        bool FileResolver(string uri, out ReadOnlyMemory<byte> utf8Json)
        {
            utf8Json = default;
            if (!Uri.TryCreate(uri, UriKind.Absolute, out Uri? u) || !u.IsFile)
                return false;

            string path = u.LocalPath;
            if (!File.Exists(path))
            {
                // Fall back to a path relative to the root schema's directory.
                path = Path.Combine(baseDir, Path.GetFileName(path));
                if (!File.Exists(path))
                    return false;
            }

            utf8Json = File.ReadAllBytes(path);
            return true;
        }
    }

    // ----------------------------------------------------------------- validate

    private static int Validate(string[] args)
    {
        bool jsonl = false, diagnostics = false, verbose = false;
        int times = 1;
        var positional = new List<string>();

        // collect options and arguments
        for (int i = 0; i < args.Length; i++)
        {
            switch (args[i])
            {
                case "-J" or "--jsonl":
                    jsonl = true;
                    break;
                case "-d" or "--diagnostics":
                    diagnostics = true;
                    break;
                case "-nd" or "--no-diag" or "--no-diagnostics":
                    diagnostics = false;
                    break;
                case "-T" or "--times":
                    times = int.Parse(args[++i]);
                    break;
                case "-v" or "--verbose":
                    verbose = true;
                    break;
                default:
                    if (args[i].StartsWith('-'))
                        throw new Exception($"Unknown option '{args[i]}'.");
                    positional.Add(args[i]);
                    break;
            }
        }

        if (positional.Count < 1)
            throw new Exception("validate requires a program image.");

        // read precompiled evaluator image
        byte[] image = File.ReadAllBytes(positional[0]);
        using JsonSchemaEvaluator evaluator = JsonSchemaEvaluator.FromProgramImage(image);

        // evaluate empty performance overhead
        double empty = 0.0;
        for (int i = 0; i < 1_000_000; i++)
        {
            long start = Stopwatch.GetTimestamp();
            // FIXME some basic computations to avoid over optimizations?
            long ticks = Stopwatch.GetTimestamp() - start;
            double edelay = toMicroSeconds(ticks);
            empty = empty == 0.0 ? edelay : edelay < empty ? edelay : empty;
        }

        foreach (string file in positional.Skip(1))
        {
            if (verbose)
                Console.Error.WriteLine($"Considering file {file} (jsonl={jsonl})");

            // read file
            byte[] content = File.ReadAllBytes(file);
            var lines = new List<ReadOnlyMemory<byte>>();

            if (jsonl)
            {
                // pedestrial split content on nl
                int start = 0;
                while (start <= content.Length)
                {
                    int nl = content.AsSpan(start).IndexOf((byte) '\n');
                    // get eof if last line does not end with nl
                    int end = nl < 0 ? content.Length : (start + nl);
                    if (end != start)
                        lines.Add(content.AsMemory(start, end - start));
                    start = end + 1;
                }
            }
            else
                lines.Add(content);

            // Console.Error.WriteLine($"Number of objects: {lines.Count}");

            // parse JSON
            // TODO collect parse time?
            var jsons = new List<ParsedJsonDocument<JsonElement>>();
            foreach (ReadOnlyMemory<byte> line in lines)
                jsons.Add(ParsedJsonDocument<JsonElement>.Parse(line));

            // validate
            for(int i = 0; i < jsons.Count; i++)
            {
                var entry = jsonl ? $"{file}[{i+1}]" : file;
                ProcessValue(evaluator, entry, jsons[i], diagnostics, times, empty);
            }
        }

        return 0;
    }

    private static void ProcessValue(
        JsonSchemaEvaluator evaluator,
        string label,
        ParsedJsonDocument<JsonElement> doc,
        bool diagnostics,
        int times,
        double empty)
    {
        JsonElement root = doc.RootElement;

        bool ok = true;
        double sum = 0.0, sum2 = 0.0;  // µs accumulation

        for (int i = 0; i < times; i++)
        {
            long ticks;

            if (diagnostics)
            {
                long start = Stopwatch.GetTimestamp();
                using var collector = JsonSchemaResultsCollector.Create(JsonSchemaResultsLevel.Verbose);
                ok = evaluator.Evaluate(root, collector);
                collector.Dispose();
                ticks = Stopwatch.GetTimestamp() - start;
            }
            else
            {
                long start = Stopwatch.GetTimestamp();
                ok = evaluator.Evaluate(root);
                ticks = Stopwatch.GetTimestamp() - start;
            }

            double delay = toMicroSeconds(ticks) - empty;
            sum += delay;
            sum2 += delay * delay;
        }

        double avg = sum / times;
        double stdev = Math.Sqrt(sum2 / times - avg * avg);

        Console.WriteLine(
            $"{label}: {(ok ? "PASS" : "FAIL")} {avg:F3} ± {stdev:F3} µs/check ({empty:F3})"
        );
    }

    private static double toMicroSeconds(long ticks) => ticks * (1_000_000.0 / Stopwatch.Frequency);
}
