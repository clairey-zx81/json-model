package json_model;

import java.lang.Math;
import java.io.Reader;
import java.io.FileReader;
import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.Map;
import java.util.HashMap;
import gnu.getopt.Getopt;  // old school :-)
import gnu.getopt.LongOpt;

public class Main
{
    static void exit(int status, String message)
    {
        if (message != null && status > 0)
            System.err.println(message);
        if (message != null && status == 0)
            System.out.println(message);
        System.exit(status);
    }

    static int jsonschema_benchmark(Object[] values, ModelChecker checker, String display, int time)
        throws JSON.Exception
    {
        int errors = 0;

        // cold run
        long cold_start = System.nanoTime();
        for (Object value: values)
            if (checker.check(value, "", null))
                errors++;
        double cold_run = 0.001 * (System.nanoTime() - cold_start);

        // warmup
        int niters = (int) (10 * 1E6 / cold_run);
        if (niters > time) niters = time;
        while (niters-- > 0)
            for (Object value: values)
                checker.check(value, "", null);

        // measure
        double sum = 0.0, sum2 = 0.0;
        for (int n = time; n > 0; time--)
        {
            long start = System.nanoTime();
            for (Object value: values)
                checker.check(value, "", null);
            double delay = 0.001 * (System.nanoTime() - start);
            sum += delay;
            sum2 += delay * delay;
        }

        // show result
        double
            avg = sum / time,
            stdev = Math.sqrt(sum2 / time - avg * avg);
        String
            savg = String.format("%.03f", avg),
            ssdv = String.format("%.03f", stdev);

        System.err.println(display + ": " + savg + " ± " + ssdv + " µs");
        System.out.println((long) (1000 * cold_run + 0.5) + "," + (long) (1000 * avg + 0.5));

        return errors;
    }

    static boolean process(
        Object value, String display, String name, ModelChecker checker,
        Boolean expect, int time, boolean report)
            throws JSON.Exception
    {
        // get and report the result
        Report rep = report ? new Report() : null;
        boolean valid = checker.check(value, name, rep);
        String result = (valid ? "PASS" : "FAIL") + ((!valid && report) ? (" (" + rep + ")") : "");

        if (expect == null || expect == valid)
            System.out.println(display + ": " + result);
        else
            System.out.println(display + ": ERROR unexpected " + result);

        // no performance measure
        if (time <= 0)
            return expect != valid;

        // performance measure overhead estimation
        double empty = 0.0;  // µs
        for (int i = time; i > 0; i--) {
            long start = System.nanoTime();
            empty += 0.001 * (System.nanoTime() - start);
        }
        empty /= time;

        // no warmup?

        // performance loop
        double sum = 0.0, sum2 = 0.0;
        for (int i = time; i > 0; i--) {
            long start = System.nanoTime();
            if (report) rep.clearEntries();
            checker.check(value, name, rep);
            double delay = 0.001 * (System.nanoTime() - start) - empty;
            sum += delay;
            sum2 += delay * delay;
        }

        // show performance result
        double
            avg = sum / time,
            stddev = Math.sqrt(sum2 / time - avg * avg);
        String
            savg = String.format("%.03f", avg),
            ssdv =  String.format("%.03f", stddev),
            sempty = String.format("%.03f", empty);

        System.out.println(display + ": " + savg + " ± " + ssdv + " µs [" + sempty + "]");

        // return if error
        return expect != null && expect != valid;
    }

    static public void main(String program, ModelChecker checker, String version, String[] args)
        throws JSON.Exception
    {
        // option management
        Getopt g = new Getopt(program, args, "hvln:rtT:", new LongOpt[] {
            new LongOpt("help", LongOpt.NO_ARGUMENT, null, 'h'),
            new LongOpt("version", LongOpt.NO_ARGUMENT, null, 'v'),
            new LongOpt("list", LongOpt.NO_ARGUMENT, null, 'l'),
            new LongOpt("json", LongOpt.REQUIRED_ARGUMENT, null, 'j'),
            new LongOpt("name", LongOpt.REQUIRED_ARGUMENT, null, 'n'),
            new LongOpt("time", LongOpt.REQUIRED_ARGUMENT, null, 'T'),
            new LongOpt("report", LongOpt.NO_ARGUMENT, null, 'r'),
            new LongOpt("no-report", LongOpt.NO_ARGUMENT, null, 1003),
            new LongOpt("test", LongOpt.NO_ARGUMENT, null, 't'),
            new LongOpt("jsonl", LongOpt.NO_ARGUMENT, null, 'L'),
            new LongOpt("jsonschema-benchmark", LongOpt.NO_ARGUMENT, null, 1002)
        });

        String json_lib = "Jackson";
        String model_name = "";
        int time = 1;
        boolean
            report = false,
            jsbench = false,
            test = false,
            jsonl = false;

        int c;
        while ((c = g.getopt()) != -1)
        {
            switch (c)
            {
                case 'h':
                    exit(0, program + " help: ...");
                case 'v':
                    exit(0, program + " version: " + version);
                case 'l':
                    exit(0, program + " models: ...");
                case 'j':
                    json_lib = g.getOptarg();
                    break;
                case 'n':
                    model_name = g.getOptarg();
                    break;
                case 'T':
                    time = Integer.parseInt(g.getOptarg());
                    if (time < 0)
                        exit(1, "unexpected value for parameter time: " + time);
                    break;
                case 'r':
                    report = true;
                    break;
                case 't':
                    test = true;
                    break;
                case 'L':
                    jsonl = true;
                    break;
                case 1002:  // --jsonschema-benchmark
                    break;
                case 1003:  // --no-report
                    report = false;
                    break;
                case '?':
                    exit(1, "unexpected error");
            }
        }

        // consistency check
        if (test && jsonl)
            exit(1, "cannot mix --test and --jsonl");

        // load and initialize with JSON library
        JSON json;
        try {
            if (json_lib.equals("GSON"))
                json_lib = "json_model.GSON";
            else if (json_lib.equals("Jackson"))
                json_lib = "json_model.Jackson";
            // else keep as is
            json = (JSON) Class.forName(json_lib).newInstance();
        }
        catch (Exception e) {
            exit(1, "unexpected JSON library: " + json_lib + " (" + e + ")");
            return;
        }
        checker.init(json);

        // process arguments
        int errors = 0;

        for (int idx = g.getOptind(); idx < args.length; idx++)
        {
            String fname = args[idx];

            // get file contents
            String[] contents;
            try {
                Reader reader = fname.equals("-") ?
                    new InputStreamReader(System.in) : new FileReader(fname);
                BufferedReader bf = new BufferedReader(reader);
                contents = bf.lines().toArray(n -> new String[n]);
            }
            catch (Exception e) {
                System.err.println("skipping file " + fname + ": " + e);
                continue;
            }

            // process contents
            if (jsonl)
            {
                // convert JSON list
                Object[] values = new Object[contents.length];
                for (int i = 0; i < contents.length; i++)
                    values[i] = json.fromJSON(contents[i]);

                // process
                errors += jsonschema_benchmark(values, checker, fname, time);
            }
            else
            {
                Object value = json.fromJSON(String.join("", contents));

                if (test)
                {
                    if (!json.isArray(value)) {
                        System.err.println("skipping non array file: " + fname);
                        errors++;
                    }
                    Object[] values = json.asArray(value);
                    int index = -1;
                    for (Object item: values)
                    {
                        if (json.isString(item))
                            continue;  // skip comment string
                        index++;
                        if (!json.isArray(item)) {
                            System.err.println("unexpected non array in file: " + fname);
                            errors++;
                        }
                        Object[] vector = json.asArray(item);
                        if (vector.length < 2 || vector.length > 3) {
                            System.err.println("unexpected test vector length in file: " + fname);
                            errors++;
                        }

                        // extract vector contents
                        boolean expect;
                        String name;
                        Object val;

                        if (vector.length == 0) {
                            expect = json.asBoolean(json.arrayItem(vector, 0));
                            name = "";
                            val = json.arrayItem(vector, 1);
                        }
                        else {
                            expect = json.asBoolean(json.arrayItem(vector, 0));
                            name = json.asString(json.arrayItem(vector, 1));
                            val = json.arrayItem(vector, 2);
                        }
                        String display = fname + "[" + index + "]";
                        if (process(val, display, name, checker, expect, time, report))
                            errors++;
                    }
                }
                else
                {
                    if (process(value, fname, model_name, checker, null, time, report))
                        errors++;
                }
            }
        }

        // cleanup
        checker.free();
        System.exit(errors > 0 ? 2 : 0);
    }
}
