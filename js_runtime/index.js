// JSON Model Runtime

export function jm_is_valid_regex(pattern, options)
{
    try {
        new RegExp(pattern, options);
        return true;
    }
    catch (e) {
        return false;
    }
}

const MONTH_DAYS = [ 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 ];

export function jm_is_valid_date(date)
{
    if (typeof date !== 'string' || date.length != 10)
        return false;

    try {
        // parsing is rather approximate…
        const [y, m, d] = date.split("-", 3);
        const year = Number(y);
        const month = Number(m);
        const day = Number(d);

        if (!Number.isInteger(year) || !Number.isInteger(month) || !Number.isInteger(day))
            return false;
        if (year < 1)
            return false;
        if (month < 1 || month > 12)
            return false;
        if (day < 1 || day > MONTH_DAYS[month - 1])
            return false;
        if (day === 29 && month === 2)  // only on leap years
            return (year % 4 === 0 && year % 100 !== 0) || (year % 400 === 0);
        return true;
    }
    catch (e) {
        return false;
    }
}

export function jm_is_valid_uuid(uuid)
{
    // TODO
    return false;
}

export function jm_is_valid_url(url)
{
    // TODO
    return false;
}
