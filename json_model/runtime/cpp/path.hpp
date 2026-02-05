#include <optional>
#include <vector>
#include <string>

using std::optional;
using std::vector;
using std::string;


class Path {
public:
    Path(size_t index);
    Path(string& name);
    Path(Path* previous, size_t index);
    Path(Path* previous, string& name);
    string toString() const;

private:
    optional<Path*> previous;
    optional<string> name;
    optional<size_t> index;
    size_t depth;
};
