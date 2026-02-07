import 'dart:convert';
import 'dart:io';
import 'dart:math';

// ---------------------------------------------------------------------------
// Typedefs for the injected functions
// ---------------------------------------------------------------------------

/// Initialize the validation library (e.g. setup regex engine)
typedef InitCallback = void Function();

/// The actual validation function.
/// [value]: The JSON data to check
/// [path]: The current path (usually starts empty)
/// [rep]: The list to store errors (if null, validation stops at first error)
typedef ValidatorCallback = bool Function(
    dynamic value, List<dynamic>? path, List<dynamic>? rep);

/// Free resources
typedef FreeCallback = void Function();

// ---------------------------------------------------------------------------
// Helpers
// ---------------------------------------------------------------------------

/// Formats the error path: .prop.index
String jsonPath(List<dynamic> path) {
  return '.' + path.join('.');
}

/// Formats the list of errors into a string similar to the JS reporting
String formatReport(List<dynamic>? rep) {
  if (rep == null || rep.isEmpty) return '';

  // rep structure: [[message, path], ...]
  // We mimic JS: unshift (reverse insertion) and join
  List<String> messages = [];
  for (var err in rep) {
    String msg = err[0].toString();
    List<dynamic> p = err[1];
    messages.insert(0, "${jsonPath(p)}: $msg");
  }
  return ' (' + messages.join('; ') + ')';
}

/// Measures the overhead of an empty loop to subtract from timing stats
double evalEmpty(int times) {
  if (times < 1) return 0.0;
  double empty = 0.0;
  final sw = Stopwatch();
  int n = times;
  while (n-- > 0) {
    sw.reset();
    sw.start();
    // Empty operation
    sw.stop();
    empty += sw.elapsedMicroseconds;
  }
  return empty / times;
}

// ---------------------------------------------------------------------------
// Core Logic
// ---------------------------------------------------------------------------

/// Processes a single validation case
int processing(
  String source,
  dynamic value,
  ValidatorCallback checker,
  bool? expected,
  bool report,
  int times,
  double emptyOverhead,
) {
  // 1. Single run for correctness
  List<dynamic>? rep = report ? [] : null;

  bool valid = checker(value, [], rep);
  int error = (expected == null || valid == expected) ? 0 : 1;

  String status = valid ? 'PASS' : 'FAIL';
  String reportStr = formatReport(rep);

  if (error != 0) {
    print("$source: ERROR unexpected $status$reportStr");
  } else {
    print("$source: $status$reportStr");
  }

  // 2. Performance run
  if (times > 1) {
    double sum = 0.0;
    double sum2 = 0.0;
    final sw = Stopwatch();

    for (int i = 0; i < times; i++) {
      List<dynamic>? loopRep = report ? [] : null;
      sw.reset();
      sw.start();
      checker(value, [], loopRep);
      sw.stop();
      if (loopRep != null) loopRep.clear(); // mimic rep.length = 0

      // Calculate delay in microseconds
      double delay = sw.elapsedMicroseconds.toDouble() - emptyOverhead;
      sum += delay;
      sum2 += delay * delay;
    }

    double avg = sum / times;
    double variance = (sum2 / times) - (avg * avg);
    double stdev = (variance > 0) ? sqrt(variance) : 0.0;
    String repTag = report ? 'rep' : 'nop';

    // Output strictly formatted to match JS: "source: rep PASS avg ± stdev µs (empty)"
    print(
      "WARN: $source: $repTag $status "
      "${avg.toStringAsFixed(3)} ± ${stdev.toStringAsFixed(3)} µs "
      "(${emptyOverhead.toStringAsFixed(3)})",
    );
  }

  return error;
}

/// Logic for https://github.com/sourcemeta-research/jsonschema-benchmark
void jsonschemaBenchmark(
  List<dynamic> values,
  ValidatorCallback checker,
  int times,
) {
  int errors = 0;
  final sw = Stopwatch();

  // 1. Cold Run
  sw.start();
  for (var v in values) {
    List<dynamic> rep = []; // pass list to detect errors
    checker(v, [], rep);
    if (rep.isNotEmpty) errors++;
  }
  sw.stop();
  double coldDelayMs = sw.elapsedMicroseconds / 1000.0;

  // 2. Warmup
  const double WARMUP_MAX_TIME_S = 10.0;
  const int WARMUP_ITERATIONS = 100;
  int maxIterations = (1000.0 * WARMUP_MAX_TIME_S / coldDelayMs).ceil();
  int warmupIterations = min(WARMUP_ITERATIONS, maxIterations);

  stderr.writeln("warmup iterations: $warmupIterations");

  for (int i = 0; i < warmupIterations; i++) {
    for (var v in values) {
      checker(v, [], null);
    }
  }

  // 3. Warm Run
  double sum1 = 0.0;
  double sum2 = 0.0;

  for (int i = 0; i < times; i++) {
    sw.reset();
    sw.start();
    for (var v in values) {
      checker(v, [], null);
    }
    sw.stop();

    double delayMs = sw.elapsedMicroseconds / 1000.0;
    sum1 += delayMs;
    sum2 += delayMs * delayMs;
  }

  double avgMs = sum1 / times;
  double variance = (sum2 / times) - (avgMs * avgMs);
  double stdevMs = (variance > 0) ? sqrt(variance) : 0.0;

  int pass = values.length - errors;

  stderr.writeln(
    "js validation: pass=$pass fail=$errors "
    "${(1000.0 * avgMs).toStringAsFixed(3)} ± ${(1000.0 * stdevMs).toStringAsFixed(3)} µs",
  );

  // CSV Output for benchmark tools
  print(
    "${(1000.0 * coldDelayMs).toStringAsFixed(0)},"
    "${(1000.0 * avgMs).toStringAsFixed(0)}",
  );

  exit(errors > 0 ? 1 : 0);
}

// ---------------------------------------------------------------------------
// Entry Point Wrapper
// ---------------------------------------------------------------------------

/// This is the function you call from your generated `main` or entry point.
/// It accepts the checker functions as arguments.
Future<void> runValidation(
  List<String> args,
  InitCallback checkerInit,
  Function checkerFun,
  FreeCallback checkerFree,
) async {
  checkerInit();

  bool verbose = false;
  int times = 1;
  bool report = true;
  bool test = false;
  bool jsonl = false;
  bool benchmark = false;
  List<String> files = [];

  for (int i = 0; i < args.length; i++) {
    String arg = args[i];
    if (arg == '-v' || arg == '--verbose') {
      verbose = true;
    } else if (arg == '-r' || arg == '--report') {
      report = true;
    } else if (arg == '--no-report') {
      report = false;
    } else if (arg == '-t' || arg == '--test') {
      test = true;
    } else if (arg == '-L' || arg == '--jsonl') {
      jsonl = true;
    } else if (arg == '-B' || arg == '--jsonschema-benchmark') {
      benchmark = true; // WARNING NOT TESTED AT ALL
    } else if (arg.startsWith('-T') || arg.startsWith('--time')) {
      String? val;
      if (arg.contains('=')) {
        val = arg.split('=')[1];
      } else if (i + 1 < args.length) {
        val = args[++i];
      }
      if (val != null) times = int.tryParse(val) ?? 1;
    } else if (!arg.startsWith('-')) {
      files.add(arg);
    }
  }

  // In JS: if (benchmarking) jsonl = true;
  if (benchmark) jsonl = true;
  // In JS: if (!benchmarking && args.values.jsonl) args.values.test = true;
  if (!benchmark && jsonl) test = true;

  // --- Overhead Estimation ---
  // We need the JIT to kick in, so we run evalEmpty multiple times
  double emptyOverhead = 0.0;
  if (times > 1) {
    List<double> samples = [
      evalEmpty(times),
      evalEmpty(times),
      evalEmpty(times),
      evalEmpty(times),
      evalEmpty(times),
      evalEmpty(times),
    ];
    samples.sort();
    emptyOverhead = samples.first;
  }

  int totalErrors = 0;

  for (String fname in files) {
    try {
      final file = File(fname);
      String content = await file.readAsString();
      dynamic value;

      if (jsonl) {
        // Handle JSONL (Newline Delimited JSON)
        List<String> lines = content.split('\n');
        // Filter out empty lines (often trailing newline)
        var validLines = lines.where((l) => l.trim().isNotEmpty);

        if (benchmark) {
          value = validLines.map((s) => jsonDecode(s)).toList();
        } else if (test) {
          // JS map logic: s => [null, JSON.parse(s)]
          // We store exactly what JS expects for the loop below
          value = validLines.map((s) => [null, jsonDecode(s)]).toList();
        } else {
          value = validLines.map((s) => jsonDecode(s)).toList();
        }
      } else {
        // Standard JSON
        value = jsonDecode(content);
      }

      // --- Benchmark Mode ---
      if (benchmark) {
        if (value is! List) value = [value];
        jsonschemaBenchmark(value, checkerFun(""), times);
        return; // Exits internally
      }

      // --- Test Mode ---
      if (test) {
        if (value is! List) {
          print("$fname: ERROR expecting an array");
          totalErrors++;
          continue;
        }

        int index = 0;
        for (var item in value) {
          String display = "$fname[${jsonl ? index + 1 : index}]";

          // Skip comments
          if (item is String) continue;

          // Check tuple structure
          if (item is! List || item.length < 2 || item.length > 3) {
            print("$display: ERROR expecting a 2-tuple or 3-tuple");
            totalErrors++;
            continue;
          }

          bool? expected;
          String name = '';
          dynamic val;

          // [expected, name, val] OR [expected, val]
          if (item.length == 3) {
            expected = item[0];
            name = item[1];
            val = item[2];
          } else {
            expected = item[0];
            val = item[1];
            name = '';
          }

          if (expected is! bool) {
            print("$display: ERROR expecting a boolean first item");
            totalErrors++;
            continue;
          }
          if (name is! String) {
            print("$display: ERROR expecting a string for name");
            totalErrors++;
            continue;
          }

          ValidatorCallback checker = checkerFun(name);

          totalErrors += processing(
            display,
            val,
            checker,
            expected,
            report,
            times,
            emptyOverhead,
          );
          index++;
        }
      }
      // --- Normal Mode ---
      else {
        ValidatorCallback checker = checkerFun('');
        totalErrors += processing(
          fname,
          value,
          checker,
          null,
          report,
          times,
          emptyOverhead,
        );
      }
    } catch (e) {
      totalErrors++;
      String msg = e.toString().replaceAll('\n', '\\n');
      print("$fname: ERROR ($msg)");
    }
  }

  checkerFree();
  exit(totalErrors > 0 ? 4 : 0);
}
