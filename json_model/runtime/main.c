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
    expect_fail,
    expect_pass
} process_mode_t;

// return µs
static double now(void)
{
    struct timespec ts;
    if (clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts))
    {
        fprintf(stderr, "cannot get time (%d): %s\n", errno, strerror(errno));
        exit(2);
    }
    return 1000000.0 * ts.tv_sec + 0.001 * ts.tv_nsec;
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
        // overhead estimation
        for (int i = loop; i; i--)
        {
            double start = now();
            empty += now() - start;
        }
        empty /= loop;

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

        fprintf(stderr, "%s.%s[%zu] nop %s %.03f ± %.03f µs/check (%.03f)\n",
                fname, name, index, valid ? "PASS": "FAIL", avg, stdev, empty);
    }

    // get result
    valid = checker(value, NULL, NULL);
    bool unexpected = (mode == expect_fail && valid) || (mode == expect_pass && !valid);

    if (mode == expect_nothing)  // just show
        fprintf(stdout, "%s: %s", fname, valid ? "PASS" : "FAIL");
    else if (unexpected)
        fprintf(stdout, "%s[%zu]: ERROR unexpected %s", fname, index, valid ? "PASS" : "FAIL");
    else  // as expected
        fprintf(stdout, "%s[%zu]: %s", fname, index, valid ? "PASS" : "FAIL");

    // maybe second pass with report collection
    if ((loop > 1 || !valid) && report)
    {
        jm_path_t path = (jm_path_t) { "", 0, NULL, NULL };
        jm_report_t report = (jm_report_t) { NULL };

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

            fprintf(stderr, "%s.%s[%zu] rep %s %.03f ± %.03f µs/check (%.03f)\n",
                    fname, name, index, valid ? "PASS": "FAIL", avg, stdev, empty);
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

int main(int argc, char* argv[])
{
    // get options
    int opt;
    char *name = "";
    bool report = false;
    bool test = false;
    bool list = false;
    int loop = 1;

    const struct option options[] = {
        { "help", no_argument, NULL, 'h' },
        { "version", no_argument, NULL, 'v' },
        { "list", no_argument, NULL, 'l' },
        { "name", required_argument, NULL, 'n' },
        { "report", no_argument, NULL, 'r' },
        { "test", no_argument, NULL, 't' },
        { "time", required_argument, NULL, 'T' },
        { "fast", no_argument, NULL, 1000 },
        { "slow", no_argument, NULL, 1001 },
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
                fprintf(stdout, "C from JSON Model compiler version %s\n", jm_version_string);
                return 0;
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
            case 1000:
                jm_is_valid_regex = jm_is_valid_regex_fast;
                jm_is_valid_date = jm_is_valid_date_fast;
                break;
            case 1001:
                jm_is_valid_regex = jm_is_valid_regex_slow;
                jm_is_valid_date = jm_is_valid_date_slow;
                break;
            case '?':
            default:
                fprintf(stdout, "unexpected option encountered\n");
                return 1;
        }
    }

    // initialization
    const char *error;
    if ((error = CHECK_init()) != NULL)
    {
        fprintf(stderr, "JSON Model initialization error: %s\n", error);
        return 2;
    }

    // delayed after the initialization
    if (list)
    {
        fprintf(stdout, "JSON Model names (empty for default):");
        for (int i = 0; i < CHECK_map_size; i++)
            fprintf(stdout, "%s ", CHECK_map_tab[i].name);
        fprintf(stdout, "\n");
        return 0;
    }

    int errors = 0;

    for (int i = optind; i < argc; i++)
    {
        json_error_t error;

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

            size_t index;
            json_t *val;
            json_array_foreach(value, index, val)
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
            }
        }
        else
            if (!process_value(name, value, argv[i], 0, expect_nothing, report, loop))
                errors++;

        // free json value
        json_decref(value);
    }

    CHECK_free();

    return errors? 4: 0;
}
