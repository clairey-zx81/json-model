#include <exception>
#include <string>

#include "path.hpp"

using std::string;

Path::Path(size_t index) : previous(), name(), index(index), depth(0) {}
Path::Path(string& name) : previous(), name(name), index(), depth(0) {}

Path::Path(Path* previous, size_t index) : previous(previous), name(), index(index), depth(previous->depth + 1) {}
Path::Path(Path* previous, string& name) : previous(previous), name(name), index(), depth(previous->depth + 1) {}

string Path::toString() const {
    string s("");

    const Path* cursor = this;
    vector<const Path*> hierarchy(depth + 1);
    hierarchy.push_back(cursor);
    for (size_t i = 0; i < depth; i++)
    {
        if (!cursor->previous.has_value()) {
            throw std::exception();
        }
        cursor = cursor->previous.value();
        hierarchy.push_back(cursor);
    }

    for (size_t i = 0; i < depth + 1; i++)
    {
        if (hierarchy[i]->name) {
            s.append(hierarchy[i]->name.value()).append("/");
        }
        else {
            s.append(std::to_string(hierarchy[i]->index.value())).append("/");
        }
    }

    s.pop_back();

    return s;
}
