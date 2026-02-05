#include "report.hpp"

#include <sstream>

#include "path.hpp"

void Report::addEntry(const std::string& message, Path* path)
{
    std::string spath = path->toString();

    entry = std::make_unique<ReportEntry>(
        message,
        spath,
        std::move(entry)
    );
}

void Report::clear()
{
    entry.reset();
}
