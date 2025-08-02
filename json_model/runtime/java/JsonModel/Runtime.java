package JsonModel;

import java.time.format.*;
import java.util.regex.Pattern;
import java.net.URL;

public class Runtime
{
    private JSON json;

    public Runtime(JSON json)
    {
        this.json = json;
    }

    public boolean _try_dt_parsing(String s, DateTimeFormatter[] formats)
    {
        for (DateTimeFormatter format: formats)
        {
            try {
                format.parse(s);
                return true;
            }
            catch (Exception e) {}
        }
        return false;
    }

    static public final DateTimeFormatter[] DATETIMES = {
        DateTimeFormatter.ISO_INSTANT,
        DateTimeFormatter.ISO_LOCAL_DATE_TIME
    };

    public boolean is_valid_datetime(Object o)
    {
        return _try_dt_parsing(json.asString(o), DATETIMES);
    }

    static public final DateTimeFormatter[] DATES = {
        DateTimeFormatter.ISO_LOCAL_DATE,
        DateTimeFormatter.BASIC_ISO_DATE
    };

    public boolean is_valid_date(Object o)
    {
        return _try_dt_parsing(json.asString(o), DATES);
    }

    static public final DateTimeFormatter[] TIMES = {
        DateTimeFormatter.ISO_LOCAL_TIME
    };

    public boolean is_valid_time(Object o)
    {
        return _try_dt_parsing(json.asString(o), TIMES);
    }

    public boolean is_valid_regex(Object o)
    {
        try {
            Pattern.compile((String) o);
            return true;
         }
        catch (Exception e) {
            return false;
        }
    }

    public boolean is_valid_exreg(Object o)
    {
        // FIXME
        return is_valid_regex(o);
    }

    public boolean is_valid_url(Object o)
    {
        try {
            new URL((String) o);
            return true;
        }
        catch (Exception e) {
            return false;
        }
    }

    static public final Pattern EMAIL = Pattern.compile("^[-.\\w]+@[-.\\w]$");

    public boolean is_valid_email(Object o)
    {
        return EMAIL.matcher((String) o).find();
    }

    public boolean is_valid_json(Object o)
    {
        try {
            json.fromJSON((String) o);
            return true;
        }
        catch (Exception e) {
            return false;
        } 
    }

    
}
