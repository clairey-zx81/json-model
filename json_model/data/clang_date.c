#include <stdio.h>
#include <ctype.h>
#include <time.h>

static inline bool _is_valid_date(const char *value)
{
    int year, month, day;

    if (value == NULL || sscanf(value, "%4d-%2d-%2d", &year, &month, &day) != 3)
        return false;

    struct tm ti = (struct tm) { .tm_year = year - 1900, .tm_mon = month - 1, .tm_mday = day};
    time_t t = mktime(&ti);

    return t != -1 && ti.tm_year == year - 1900 && ti.tm_mon == month - 1 && ti.tm_mday == day;
}
