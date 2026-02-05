#include "misc.hpp"
#include "report.hpp"
#include "path.hpp"

#include <ctime>
#include <cctype>
#include <cassert>
#include <nlohmann/json.hpp>
#include<string>

using nlohmann::json;
using std::string;
using std::unordered_map;

string version_string = "<unknown>";

bool is_scalar(const json* val) {
    if (!val) return false;

    return val->is_string()
        || val->is_number()
        || val->is_boolean()
        || val->is_null();
}

// Checkers
unordered_map<string, Checker> checker_map;

Checker get_checker(const string& name) {
    auto it = checker_map.find(name);
    if (it == checker_map.end())
        throw std::runtime_error("Checker not found: " + name);
    return it->second;
}


namespace isValid {
    bool isValidDate(const std::string& date, Path* path, Report* report)
    {
        int year, month, day;
        if (std::sscanf(date.c_str(), "%4d-%2d-%2d", &year, &month, &day) != 3)
            return false;

        std::tm tm{};
        tm.tm_year = year - 1900;
        tm.tm_mon = month - 1;
        tm.tm_mday = day;

        std::time_t t = std::mktime(&tm);
        if (t == -1 ||
            tm.tm_year != year - 1900 ||
            tm.tm_mon != month - 1 ||
            tm.tm_mday != day)
        {
            if (report)
                report->addEntry("invalid date", path);
            return false;
        }
        return true;
    }

    bool isValidTime(const std::string& time, Path* path, Report* report)
    {
        int h, m, s;
        if (std::sscanf(time.c_str(), "%2d:%2d:%2d", &h, &m, &s) != 3)
            return false;

        if (h < 0 || h >= 24 || m < 0 || m >= 60 || s < 0 || s >= 60) {
            if (report)
                report->addEntry("invalid time", path);
            return false;
        }
        return true;
    }

    bool isValidDateTime(const std::string& datetime, Path* path, Report* report)
    {
        if (datetime.size() < 19)
            return false;

        return isValidDate(datetime.substr(0, 10), path, report) &&
            isValidTime(datetime.substr(11), path, report);
    }

    bool isValidUUID(const std::string& uuid, Path*, Report*)
    {
        const int sections[] = { 8, 4, 4, 4, 12 };
        std::size_t i = 0;

        for (int len : sections) {
            for (int j = 0; j < len; ++j)
                if (i >= uuid.size() || !std::isxdigit(uuid[i++]))
                    return false;
            if (i < uuid.size() && uuid[i] == '-')
                ++i;
        }
        return i == uuid.size();
    }

    bool isValidRegex(const std::string& pattern, Path*, Report*)
    {
        return !pattern.empty();
    }

    bool isValidURL(const std::string& url, Path*, Report*)
    {
        for (unsigned char c : url)
            if (c < 33 || c >= 126 || c == '"' || c == '<' || c == '>')
                return false;
        return true;
    }

    static bool isEmailChar(char c)
    {
        return std::isalnum(c) || c == '_' || c == '.' || c == '-';
    }

    bool isValidEmail(const std::string& email, Path*, Report*)
    {
        std::size_t at = email.find('@');
        if (at == std::string::npos || at == 0 || at + 1 >= email.size())
            return false;

        for (std::size_t i = 0; i < email.size(); ++i)
            if (i != at && !isEmailChar(email[i]))
                return false;

        return true;
    }

    bool isValidJSON(const std::string& json, Path*, Report*)
    {
        std::size_t i = 0;
        while (i < json.size() && std::isspace(json[i])) ++i;
        if (i == json.size()) return false;

        return json[i] == '{' || json[i] == '[';
    }

} // namespace isValid


// Initialize checker_map
std::unordered_map<string, Checker> checker_map = {
    {"date",     [](const json& j, Path* p, Report* r) { return isValid::isValidDate(j.get<string>(), p, r); }},
    {"time",     [](const json& j, Path* p, Report* r) { return isValid::isValidTime(j.get<string>(), p, r); }},
    {"datetime", [](const json& j, Path* p, Report* r) { return isValid::isValidDateTime(j.get<string>(), p, r); }},
    {"uuid",     [](const json& j, Path* p, Report* r) { return isValid::isValidUUID(j.get<string>(), p, r); }},
    {"regex",    [](const json& j, Path* p, Report* r) { return isValid::isValidRegex(j.get<string>(), p, r); }},
    {"url",      [](const json& j, Path* p, Report* r) { return isValid::isValidURL(j.get<string>(), p, r); }},
    {"email",    [](const json& j, Path* p, Report* r) { return isValid::isValidEmail(j.get<string>(), p, r); }},
    {"json",     [](const json& j, Path* p, Report* r) { return isValid::isValidJSON(j.get<string>(), p, r); }}
};
