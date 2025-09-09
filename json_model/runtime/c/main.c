#include <stdio.h>
#include <unistd.h>
#include <assert.h>
#include <time.h>
#include <getopt.h>
#include <math.h>
#include <errno.h>
#include <string.h>

#include <json-model.h>

typedef enum {
    expect_nothing,
    expect_anything,
    expect_fail,
    expect_pass
} process_mode_t;

// return realtime µs
static INLINE double now(void)
{
    struct timespec ts;
    if (unlikely(clock_gettime(CLOCK_REALTIME, &ts)))
    {
        fprintf(stderr, "cannot get time (%d): %s\n", errno, strerror(errno));
        exit(2);
    }
    return 1000000.0 * ts.tv_sec + 0.001 * ts.tv_nsec;
}

// overhead estimation µs
static double empty_run(int loop)
{
    double empty = 0.0;
    for (int i = loop; i; i--)
    {
        double start = now();
        empty += now() - start;
    }
    empty /= loop;
    return empty;
}

// check value and report if there was some error wrt expectations
static bool
process_value(const char *name, const json_t * value,
    const char *fname, size_t index, process_mode_t mode, bool report, int loop)
{
    // get checker function
    const jm_check_fun_t checker = CHECK_fun(name);
    if (checker == NULL)
    {
        fprintf(stderr, "check function not found for %s\n", name);
        return true;
    }

    // check value against model, fast (no path nor reasons)
    bool valid = true;
    double empty = 0.0;

    // performance loop in µs
    if (loop > 1)
    {
        // minimize overhead estimation over 10 runs
        empty = empty_run(loop);
        for (int i = 1; i < 10; i++)
        {
            double e = empty_run(loop);
            if (e < empty)
                empty = e;
        }

        // validation estimation
        double sum = 0.0, sum2 = 0.0;

        for (int i = loop; i; i--)
        {
            double start = now();

            valid = checker(value, NULL, NULL);

            double delay = now() - start - empty;
            sum += delay;
            sum2 += delay * delay;
        }

        double avg = sum / loop;
        double stdev = sqrt(sum2 / loop - avg * avg);

        fprintf(stderr, "%s%s%s[%zu] nop %s %.03f ± %.03f µs/check (%.03f)\n",
                fname, strlen(name)? ".": "", name, index, valid ? "PASS": "FAIL",
                avg, stdev, empty);
    }

    // get result
    valid = checker(value, NULL, NULL);
    bool unexpected = (mode == expect_fail && valid) || (mode == expect_pass && !valid);

    if (mode == expect_nothing)  // just show, no index
        fprintf(stdout, "%s: %s", fname, valid ? "PASS" : "FAIL");
    else if (mode == expect_anything)  // just show, including index
        fprintf(stdout, "%s[%zu]: %s", fname, index, valid ? "PASS" : "FAIL");
    else if (unexpected)
        fprintf(stdout, "%s[%zu]: ERROR unexpected %s", fname, index, valid ? "PASS" : "FAIL");
    else  // as expected
        fprintf(stdout, "%s[%zu]: %s", fname, index, valid ? "PASS" : "FAIL");

    // maybe second pass with report collection
    if ((loop > 1 || !valid) && report)
    {
        jm_path_t path;
        jm_report_t report;

        bool valid2 = true;

        // loop just for measuring performance, including cleanup
        if (loop > 1)
        {
            double sum = 0.0, sum2 = 0.0;

            for (int i = loop; i; i--)
            {
                double start = now();

                path = (jm_path_t) { "", 0, NULL, NULL };
                report = (jm_report_t) { NULL };
                valid2 = checker(value, &path, &report);
                jm_report_free_entries(&report);

                double delay = now() - start - empty;
                sum += delay;
                sum2 += delay * delay;
            }

            double avg = sum / loop;
            double stdev = sqrt(sum2 / loop - avg * avg);

            fprintf(stderr, "%s%s%s[%zu] rep %s %.03f ± %.03f µs/check (%.03f)\n",
                    fname, strlen(name)? ".": "", name, index, valid ? "PASS": "FAIL",
                    avg, stdev, empty);
        }

        // get the result for display
        path = (jm_path_t) { "", 0, NULL, NULL };
        report = (jm_report_t) { NULL };
        valid2 = checker(value, &path, &report);

        assert(valid == valid2);

        if (report.entry)
        {
            bool first = true;
            fprintf(stdout, " (");

            for (jm_report_entry_t *entry = report.entry; entry != NULL; entry = entry->prev)
            {
                if (first)
                    first = false;
                else
                    fprintf(stdout, "; ");
                fprintf(stdout, "%s: %s", entry->path, entry->message);
            }

            fprintf(stdout, ")");
        }

        jm_report_free_entries(&report);
    }

    fprintf(stdout, "\n");

    return !unexpected;
}

#if defined(JSONSCHEMA_BENCHMARK)
// for https://github.com/sourcemeta-research/jsonschema-benchmark
static void jsonschema_benchmark_run(int argc, char *argv[], const char *name, int loop)
{
    const jm_check_fun_t checker = CHECK_fun(name);
    if (checker == NULL)
    {
        fprintf(stderr, "no validation function found for %s\n", name);
        exit(2);
    }

    size_t size = 1024;
    int nvalues = 0;
    json_t **values = (json_t **) malloc(sizeof(json_t *) * size);

    // load jsonl
    for (int i = optind; i < argc; i++)
    {
        FILE *input = fopen(argv[i], "r");

        if (input == NULL)
        {
            fprintf(stderr, "%s: ERROR while opening file\n", argv[i]);
            exit(3);
        }

        json_error_t error;
        json_t *value;
        while ((value = json_loadf(input,
                                   JSON_DISABLE_EOF_CHECK|JSON_DECODE_ANY|JSON_ALLOW_NUL,
                                   &error)))
        {
            if (nvalues == size) {
                size *= 2;
                values = (json_t **) realloc(values, sizeof(json_t *) * size);
            }
            values[nvalues++] = value;
        }
    }

    // evaluate empty run
    int count = 0;
    double empty_start = now();
    for (int i = 0; i < nvalues; i++)
        if (values[i] != NULL)
            count++;
    double empty_delay = now() - empty_start;

    // run once in for counting
    int npass = 0, nfail = 0;
    double cold_start = now();
    for (int i = 0; i < nvalues; i++)
        if (checker(values[i], NULL, NULL))
            npass++;
        else
            nfail++;
    double cold_delay = now() - cold_start;

    // collect performance data over a loop
    double sum = 0.0, sum2 = 0.0;
    for (int n = loop; n; n--)
    {
        double start = now();
        for (int i = 0; i < nvalues; i++)
            checker(values[i], NULL, NULL);
        double delay = now() - start;
        sum += delay;
        sum2 += delay * delay;
    }

    double avg = sum / loop;
    double stdev = sqrt(sum2 / loop - avg * avg);

    // report
    fprintf(stderr, "C validation: pass=%d fail=%d %.03f ± %.03f µs [%.03f]\n",
            npass, nfail, avg, stdev, empty_delay);
    fprintf(stdout, "%lld,%lld\n",
            (long long int) (1000 * cold_delay), (long long int) (1000 * avg));

    exit(nfail ? 1 : 0);
}
#endif // JSONSCHEMA_BENCHMARK

int main(int argc, char* argv[])
{
    // get options
    int opt;
    char *name = "";
    bool report = false;
    bool test = false;
    bool jsonl = false;
    bool list = false;
    bool version = false;
    bool jsonschema_benchmark = false;
    int loop = 1;

    const struct option options[] = {
        { "help", no_argument, NULL, 'h' },
        { "version", no_argument, NULL, 'v' },
        { "list", no_argument, NULL, 'l' },
        { "name", required_argument, NULL, 'n' },
        { "report", no_argument, NULL, 'r' },
        { "test", no_argument, NULL, 't' },
        { "time", required_argument, NULL, 'T' },
        { "jsonl", no_argument, NULL, 'L' },
        { "fast", no_argument, NULL, 1000 },
        { "slow", no_argument, NULL, 1001 },
        { "jsonschema-benchmark", no_argument, NULL, 1002 },
        { "no-report", no_argument, NULL, 1003 },
        { NULL, 0, NULL, 0 }
    };

    while ((opt = getopt_long(argc, argv, "hvln:rtT:", options, &optind)) != -1)
    {
        switch (opt) {
            case 'h':  // FIXME expand help!
                fprintf(stdout,
                        "Usage: %s [-hvl] [-r] [-n name] [-t] [-T repeat] [files...]\n"
                        "Check JSON values validity against a JSON model\n"
                        "Generated by jmc (JSON Model Compiler) version %s\n"
                        "see https://github.com/clairey-zx81/json-model\n",
                        argv[0], jm_version_string);
                return 0;
            case 'l':
                list = true;
                break;
            case 'v':
                version = true;
                break;
            case 'n':
                name = optarg;
                break;
            case 'r':
                report = true;
                break;
            case 't':
                test = true;
                break;
            case 'T':
                loop = atoi(optarg);
                break;
            case 'L':
                jsonl = true;
                break;
            case 1000:
                jm_is_valid_regex = jm_is_valid_regex_fast;
                jm_is_valid_date = jm_is_valid_date_fast;
                break;
            case 1001:
                jm_is_valid_regex = jm_is_valid_regex_slow;
                jm_is_valid_date = jm_is_valid_date_slow;
                break;
            case 1002:
                jsonl = true;
                jsonschema_benchmark = true;
                break;
            case 1003:
                report = false;
                break;
            case '?':
            default:
                fprintf(stdout, "unexpected option encountered\n");
                return 1;
        }
    }

    // option consistency
    if (jsonl && test)
    {
        fprintf(stderr, "Value input format cannot be both jsonl and test\n");
        return 1;
    }

    // initialization
    const char *error;
    if ((error = CHECK_init()) != NULL)
    {
        fprintf(stderr, "JSON Model initialization error: %s\n", error);
        return 2;
    }

    // delayed after the initialization
    if (version)
    {
        fprintf(stdout, "C from JSON Model compiler version %s\n", jm_version_string);
        return 0;
    }
    if (list)
    {
        fprintf(stdout, "JSON Model names (empty for default):");
        for (int i = 0; i < CHECK_map_size; i++)
            fprintf(stdout, "%s ", CHECK_map_tab[i].name);
        fprintf(stdout, "\n");
        return 0;
    }

    int errors = 0;

    if (jsonschema_benchmark)
    {
#if defined(JSONSCHEMA_BENCHMARK)
        jsonschema_benchmark_run(argc, argv, name, loop);
#else
        fprintf(stderr,
                "jsonschema benchmark unavailable, recompile with -D JSONSCHEMA_BENCHMARK\n");
        return 3;
#endif  // JSONSCHEMA_BENCHMARK
    }

    for (int i = optind; i < argc; i++)
    {
        json_error_t error;
        json_t *value;

        if (jsonl)
        {
            FILE *input = fopen(argv[i], "r");
            int count = 1;

            if (input == NULL)
            {
                fprintf(stderr, "%s: ERROR while opening file\n", argv[i]);
                errors++;
                continue;
            }

            while ((value = json_loadf(input,
                                       JSON_DISABLE_EOF_CHECK|JSON_DECODE_ANY|JSON_ALLOW_NUL,
                                       &error)))
            {
                if (!process_value(name, value, argv[i], count, expect_anything, report, loop))
                    errors++;
                count++;
                json_decref(value);
            }

            if (value == NULL)  // if not EOF, it is probably an error
            {
                unsigned char c;
                if (fread(&c, 1, 1, input) != 0)
                {
                    fprintf(stdout, "%s: ERROR (%s at %d:%d)\n",
                            argv[i], error.text, error.line, error.column);
                    errors++;
                    continue;
                }
            }
        }
        else
        {
            // read and parse JSON file
            json_t *value = json_load_file(argv[i], JSON_DECODE_ANY|JSON_ALLOW_NUL, &error);
            if (value == NULL)
            {
                fprintf(stdout, "%s: ERROR (%s at %d:%d)\n",
                        argv[i], error.text, error.line, error.column);
                errors++;
                continue;
            }

            if (test)
            {
                if (!json_is_array(value))
                {
                    fprintf(stdout, "%s: ERROR not a JSON array in test mode\n", argv[i]);
                    errors++;
                    continue;
                }

                size_t _, index = 0;
                json_t *val;
                json_array_foreach(value, _, val)
                {
                    if (json_is_string(val))
                        // skip string comments
                        continue;

                    // else must be an array (size is 0 for non-arrays)
                    size_t size = json_array_size(val);
                    if (!(size == 2 || size == 3))
                    {
                        fprintf(stdout,
                                "%s[%zu]: ERROR not a 2 or 3-tuple\n",
                                argv[i], index);
                        errors++;
                        continue;
                    }

                    const json_t
                        *first = json_array_get(val, 0),
                        *second = json_array_get(val, 1);

                    if (!json_is_boolean(first) || (size == 3 && !json_is_string(second)))
                    {
                        fprintf(stdout,
                                "%s[%zu]: ERROR first element not boolean or second not string\n",
                                argv[i], index);
                        errors++;
                        continue;
                    }

                    const char *tname = size == 3 ? json_string_value(second) : name;
                    const json_t *value = size == 3 ? json_array_get(val, 2) : second;
                    process_mode_t mode = json_is_true(first) ? expect_pass : expect_fail;

                    if (!process_value(tname, value, argv[i], index, mode, report, loop))
                        errors++;

                    index++;
                }
            }
            else
                if (!process_value(name, value, argv[i], 0, expect_nothing, report, loop))
                    errors++;

            // free json value
            json_decref(value);
        }
    }

    CHECK_free();

    return errors? 4: 0;
}
