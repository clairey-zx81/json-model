#include <iostream>
#include <fstream>
#include <sstream>
#include <ctime>
#include <getopt.h>
#include <cmath>
#include <string>
#include <vector>
#include <chrono>
#include <cstdlib>

#include <nlohmann/json.hpp>

#include <report.hpp>
#include <path.hpp>
#include <misc.hpp>
#include <rt.hpp>

using json = nlohmann::json;

enum class ProcessMode {
    ExpectNothing,
    ExpectAnything,
    ExpectFail,
    ExpectPass
};

// Return realtime in µs
inline double now() {
    auto tp = std::chrono::steady_clock::now();
    auto us = std::chrono::time_point_cast<std::chrono::microseconds>(tp).time_since_epoch().count();
    return static_cast<double>(us);
}

// Overhead estimation µs
double empty_run(int loop) {
    double empty = 0.0;
    for (int i = 0; i < loop; i++) {
        double start = now();
        empty += now() - start;
    }
    return empty / loop;
}

// Check value and report
bool process_value(const std::string& name, const json& value,
    const std::string& fname, size_t index,
    ProcessMode mode, bool report, int loop)
{
    Checker checker = get_checker(name);
    if (!checker) {
        std::cerr << "Check function not found for " << name << "\n";
        return true;
    }

    // Check value against model, fast (no path nor reasons)
    bool valid = true;
    double empty = 0.0;

    // Performance loop in µs
    if (loop > 1) {
        // Minimize overhead estimation over 10 runs
        empty = empty_run(loop);
        for (int i = 1; i < 10; i++) {
            double e = empty_run(loop);
            if (e < empty) empty = e;
        }

        // Validation estimation
        double sum = 0.0, sum2 = 0.0;
        for (int i = 0; i < loop; i++) {
            double start = now();
            valid = checker(value, nullptr, nullptr);
            double delay = now() - start - empty;
            sum += delay;
            sum2 += delay * delay;
        }

        double avg = sum / loop;
        double stdev = std::sqrt(sum2 / loop - avg * avg);

        std::cerr << fname << (name.empty() ? "" : ".") << name
            << "[" << index << "] nop "
            << (valid ? "PASS" : "FAIL") << " "
            << avg << " ± " << stdev << " µs/check (" << empty << ")\n";
    }

    // Get result
    valid = checker(value, nullptr, nullptr);
    bool unexpected = (mode == ProcessMode::ExpectFail && valid) ||
        (mode == ProcessMode::ExpectPass && !valid);

    if (mode == ProcessMode::ExpectNothing) // Just show, no index
        std::cout << fname << ": " << (valid ? "PASS" : "FAIL");
    else if (mode == ProcessMode::ExpectAnything) // Just show, including index
        std::cout << fname << "[" << index << "]: " << (valid ? "PASS" : "FAIL");
    else if (unexpected)
        std::cout << fname << "[" << index << "]: ERROR unexpected " << (valid ? "PASS" : "FAIL");
    else // as expected
        std::cout << fname << "[" << index << "]: " << (valid ? "PASS" : "FAIL");


    // Maybe second pass with report collection
    if ((loop > 1 || !valid) && report) {
        bool valid2 = true;

        // Loop just for measuring performance, including cleanup
        if (loop > 1) {
            double sum = 0.0, sum2 = 0.0;

            for (int i = 0; i < loop; ++i) {
                double start = now();

                Path path(0);
                Report rep;

                valid2 = checker(value, &path, &rep);

                rep.clear();

                double delay = now() - start - empty;
                sum += delay;
                sum2 += delay * delay;
            }

            double avg = sum / loop;
            double stdev = std::sqrt(sum2 / loop - avg * avg);

            std::cerr << fname << (name.empty() ? "" : ".") << name
                << "[" << index << "] rep "
                << (valid ? "PASS" : "FAIL") << " "
                << avg << " ± " << stdev << " µs/check (" << empty << ")\n";
        }

        // Get the result for display
        Path path(0);
        Report rep;
        valid2 = checker(value, &path, &rep);

        assert(valid == valid2);

        if (const ReportEntry* entry = rep.head()) {
            bool first = true;
            std::cout << " (";
            for (const ReportEntry* e = entry; e; e = e->prev.get()) {
                if (!first) std::cout << "; ";
                std::cout << e->path << ": " << e->message;
                first = false;
            }
            std::cout << ")";
        }
    }

    std::cout << "\n";
    return !unexpected;
}

#if defined(JSONSCHEMA_BENCHMARK)
// C
// // for https://github.com/sourcemeta-research/jsonschema-benchmark
// static void jsonschema_benchmark_run(int argc, char* argv[], const char* name, int loop)
// {
//     const jm_check_fun_t checker = CHECK_fun(name);
//     if (checker == NULL)
//     {
//         fprintf(stderr, "no validation function found for %s\n", name);
//         exit(2);
//     }

//     size_t size = 1024;
//     int nvalues = 0;
//     json_t** values = (json_t**)malloc(sizeof(json_t*) * size);

//     // load jsonl
//     for (int i = optind; i < argc; i++)
//     {
//         FILE* input = fopen(argv[i], "r");

//         if (input == NULL)
//         {
//             fprintf(stderr, "%s: ERROR while opening file\n", argv[i]);
//             exit(3);
//         }

//         json_error_t error;
//         json_t* value;
//         while ((value = json_loadf(input,
//             JSON_DISABLE_EOF_CHECK | JSON_DECODE_ANY | JSON_ALLOW_NUL,
//             &error)))
//         {
//             if (nvalues == size) {
//                 size *= 2;
//                 values = (json_t**)realloc(values, sizeof(json_t*) * size);
//             }
//             values[nvalues++] = value;
//         }
//     }

//     // evaluate empty run
//     int count = 0;
//     double empty_start = now();
//     for (int i = 0; i < nvalues; i++)
//         if (values[i] != NULL)
//             count++;
//     double empty_delay = now() - empty_start;

//     // run once in for counting
//     int npass = 0, nfail = 0;
//     double cold_start = now();
//     for (int i = 0; i < nvalues; i++)
//         if (checker(values[i], NULL, NULL))
//             npass++;
//         else
//             nfail++;
//     double cold_delay = now() - cold_start;

//     // collect performance data over a loop
//     double sum = 0.0, sum2 = 0.0;
//     for (int n = loop; n; n--)
//     {
//         double start = now();
//         for (int i = 0; i < nvalues; i++)
//             checker(values[i], NULL, NULL);
//         double delay = now() - start;
//         sum += delay;
//         sum2 += delay * delay;
//     }

//     double avg = sum / loop;
//     double stdev = sqrt(sum2 / loop - avg * avg);

//     // report
//     fprintf(stderr, "C validation: pass=%d fail=%d %.03f ± %.03f µs [%.03f]\n",
//         npass, nfail, avg, stdev, empty_delay);
//     fprintf(stdout, "%lld,%lld\n",
//         (long long int) (1000 * cold_delay), (long long int) (1000 * avg));

//     exit(nfail ? 1 : 0);
// }
#endif // JSONSCHEMA_BENCHMARK


int main(int argc, char* argv[]) {
    // Get options
    int opt;
    std::string name;
    bool report = false;
    bool test = false;
    bool jsonl = false;
    bool list = false;
    bool version = false;
    bool jsonschema_benchmark = false;
    int loop = 1;

    const struct option options[] = {
        { "help", no_argument, nullptr, 'h' },
        { "version", no_argument, nullptr, 'v' },
        { "list", no_argument, nullptr, 'l' },
        { "name", required_argument, nullptr, 'n' },
        { "report", no_argument, nullptr, 'r' },
        { "test", no_argument, nullptr, 't' },
        { "time", required_argument, nullptr, 'T' },
        { "jsonl", no_argument, nullptr, 'L' },
        { "fast", no_argument, nullptr, 1000 },
        { "slow", no_argument, nullptr, 1001 },
        { "jsonschema-benchmark", no_argument, nullptr, 1002 },
        { "no-report", no_argument, nullptr, 1003 },
        { nullptr, 0, nullptr, 0 }
    };

    while ((opt = getopt_long(argc, argv, "hvln:rtT:", options, &optind)) != -1) {
        switch (opt) {
        case 'h':
            std::cout << "Usage: " << argv[0] << " [-hvl] [-r] [-n name] [-t] [-T repeat] [files...]\n"
                << "Check JSON values validity against a JSON model\n"
                << "Generated by jmc (JSON Model Compiler) version "
                << version_string << "\nsee https://github.com/clairey-zx81/json-model\n";
            return 0;
        case 'l': list = true; break;
        case 'v': version = true; break;
        case 'n': name = optarg; break;
        case 'r': report = true; break;
        case 't': test = true; break;
        case 'T': loop = std::atoi(optarg); break;
        case 'L': jsonl = true; break;
        case 1000: break;
        case 1001: break;
        case 1002:
            jsonl = true;
            jsonschema_benchmark = true;
            break;
        case 1003:
            report = false;
            break;
        case '?':
        default: std::cerr << "Unexpected option\n"; return 1;
        }
    }

    // Option consistency
    if (jsonl && test) {
        std::cerr << "Value input format cannot be both jsonl and test\n";
        return 1;
    }

    // Initialization
    if (checker_map.empty()) {
        std::cerr << "JSON Model initialization error: no checkers defined\n";
        return 2;
    }

    // Delayed after the initialization
    if (version) {
        std::cout << "C++ from JSON Model compiler version " << version_string << "\n";
        return 0;
    }

    if (list) {
        std::cout << "JSON Model names (empty for default): ";
        for (const auto& [name, _] : checker_map) {
            std::cout << name << " ";
        }
        std::cout << std::endl;
        return 0;
    }

    int errors = 0;

    if (jsonschema_benchmark) {
#if defined(JSONSCHEMA_BENCHMARK)
        jsonschema_benchmark_run(argc, argv, name, loop);
#else
        std::cerr << "jsonschema benchmark unavailable, recompile with -D JSONSCHEMA_BENCHMARK\n";
        return 3;
#endif // JSONSCHEMA_BENCHMARK
    }

    for (int i = optind; i < argc; i++) {
        const std::string filename = argv[i];

        if (jsonl) {
            std::ifstream input(filename);
            if (!input.is_open()) {
                std::cerr << filename << ": ERROR while opening file\n";
                errors++;
                continue;
            }

            std::string line;
            int count = 1;
            while (std::getline(input, line)) {
                if (line.empty()) continue;

                try {
                    json value = json::parse(line, nullptr, true); // allow exceptions
                    if (!process_value(name, value, filename, count, ProcessMode::ExpectAnything, report, loop))
                        errors++;
                    count++;
                }
                catch (json::parse_error& e) {
                    std::cerr << filename << ": ERROR (" << e.what() << ")\n";
                    errors++;
                }
            }
        }
        else {
            // Read and parse JSON file
            json value;
            try {
                std::ifstream f(filename);
                if (!f.is_open()) throw std::runtime_error("Cannot open file");
                f >> value;
            }
            catch (std::exception& e) {
                std::cerr << filename << ": ERROR (" << e.what() << ")\n";
                errors++;
                continue;
            }

            if (test) {
                if (!value.is_array()) {
                    std::cerr << filename << ": ERROR not a JSON array in test mode\n";
                    errors++;
                    continue;
                }

                size_t index = 0;
                for (const auto& val : value) {
                    if (val.is_string())
                        continue; // skip string comments

                    // else must be an array (size is 0 for non-arrays)
                    if (!val.is_array() || !(val.size() == 2 || val.size() == 3)) {
                        std::cerr << filename << "[" << index << "]: ERROR not a 2 or 3-tuple\n";
                        errors++;
                        index++;
                        continue;
                    }

                    const auto& first = val[0];
                    const auto& second = val[1];

                    if (!first.is_boolean() || (val.size() == 3 && !second.is_string())) {
                        std::cerr << filename << "[" << index << "]: ERROR first element not boolean or second not string\n";
                        errors++;
                        index++;
                        continue;
                    }

                    std::string tname = (val.size() == 3) ? second.get<std::string>() : name;
                    const json& target_value = (val.size() == 3) ? val[2] : second;
                    ProcessMode mode = first.get<bool>() ? ProcessMode::ExpectPass : ProcessMode::ExpectFail;

                    if (!process_value(tname, target_value, filename, index, mode, report, loop))
                        errors++;

                    index++;
                }
            }
            else {
                if (!process_value(name, value, filename, 0, ProcessMode::ExpectNothing, report, loop))
                    errors++;
            }
        }
    }

    return errors ? 4 : 0;
}
