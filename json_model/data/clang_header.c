#include <string.h>
#include <stdlib.h>
#include <jansson.h>

#define array_length(arr) (sizeof(arr) / sizeof((arr)[0]))
typedef enum { false, true } bool;

// linked list of report entries
typedef struct ReportEntry {
  const char *message;
  char *path;
  struct ReportEntry *prev;
} ReportEntry;

typedef struct Report {
  ReportEntry *entry;
} Report;

// path is collected in stack
typedef struct Path {
    const char *name;
    size_t index;
    struct Path *prev;
    struct Path *next;
} Path;

typedef bool (*check_fun_t)(const json_t *, Path *, Report *);

/* property mapping management */
typedef int (*cmp_fun_t)(const void *, const void *);

typedef struct {
    const char *name;
    check_fun_t val_check;
} check_prop_t;

static bool initialized = false;

/* module API */
void CHECK_FUNCTION_NAME_init(void);
check_fun_t CHECK_FUNCTION_NAME_fun(const char *name);
bool CHECK_FUNCTION_NAME(json_t* val, const char *name, Report *rep, bool *error);
void CHECK_FUNCTION_NAME_free(void);

/* helper functions */
static int prop_cmp(const check_prop_t *e1, const check_prop_t *e2)
{
    return strcmp(e1->name, e2->name);
}

static check_fun_t
check_prop_find(const char *name, const check_prop_t *props, int nprops)
{
    check_prop_t searched = (check_prop_t) { name, NULL };
    check_prop_t *entry = (check_prop_t *)
        bsearch(&searched, props, nprops, sizeof(check_prop_t), (cmp_fun_t) prop_cmp);
    return entry ? entry->val_check : NULL;
}

static void report_add_entry(Report* rep, const char *msg, Path *path)
{
    ReportEntry *entry = malloc(sizeof(ReportEntry));
    *entry = (ReportEntry) { msg, NULL, rep->entry };
    rep->entry = entry;
    if (path)
    {
        // path segments are stored in reverse order
        size_t size = 1;
        Path *current = path;
        Path *next = NULL;
        // dive to compute the path length and build the back path
        while (current != NULL)
        {
            // "." name or "." number
            size += 1 + (current->name ? strlen(current->name) : (3 * sizeof(size_t)));
            Path *prev = current->prev;
            current->next = next;  // needed to backtrack
            next = current;  // future next
            current = prev;
        }
        // allocate path
        char *spath = malloc(size);
        char *spos = spath;
        bool first = true;
        // backtrack along path upward
        current = next;
        while (current != NULL)
        {
            // append "." and segment name/number unless first
            if (!first || !current->next)
                *spos++ = '.';
            if (current->name)
                spos = stpcpy(spos, current->name);
            else
                spos += sprintf(spos, "%zu", current->index);
            current = current->next;
            first = false;
        }
        *spos = '\0';
        entry->path = spath;
    }
}

static void report_free_entries(Report *rep)
{
    ReportEntry *entry = rep->entry;
    rep->entry = NULL;

    while (entry != NULL) {
        ReportEntry *follow = entry->prev;
        if (entry->path)
            free(entry->path);
        free(entry);
        entry = follow;
    }
}
