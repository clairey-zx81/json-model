#pragma once

#include <string>
#include <memory>

using std::string;

class ReportEntry {
public:
    string message;
    string path;
    std::unique_ptr<ReportEntry> prev;

    ReportEntry(string msg,
        string p,
        std::unique_ptr<ReportEntry> previous)
        : message(std::move(msg)),
        path(std::move(p)),
        prev(std::move(previous)) {
    }
};

class Report {
public:
    Report() = default;
    ~Report() = default;

    Report(const Report&) = delete;
    Report& operator=(const Report&) = delete;

    void addEntry(const string& message, Path* path);
    void clear();

    const ReportEntry* head() const { return entry.get(); }
private:
    std::unique_ptr<ReportEntry> entry;
};
