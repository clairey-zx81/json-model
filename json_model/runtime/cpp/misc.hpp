#pragma once

#include<string>
#include <nlohmann/json.hpp>

using std::string;
using nlohmann::json;

class Path;
class Report;

std::string version_string;

bool is_scalar(const json* val);


// using Checker = std::function<bool(const json&, Path*, Report*)>;
// extern std::unordered_map<std::string, Checker> checker_map;
// Checker get_checker(const std::string& name);

typedef bool (*Checker) (const json&, Path*, Report*);

namespace isValid {
    // Date / time
    bool isValidDate(const std::string& date, Path* path, Report* report);
    bool isValidTime(const std::string& time, Path* path, Report* report);
    bool isValidDateTime(const std::string& datetime, Path* path, Report* report);

    // Identifiers
    bool isValidUUID(const std::string& uuid, Path* path, Report* report);
    bool isValidRegex(const std::string& pattern, bool extended, Path* path, Report* report);
    bool isValidURL(const std::string& url, Path* path, Report* report);
    bool isValidEmail(const std::string& email, Path* path, Report* report);

    // JSON
    bool isValidJSON(const std::string& json, Path* path, Report* report);

}   // namespace isValid
