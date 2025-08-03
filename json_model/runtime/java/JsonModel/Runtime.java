package JsonModel;

import java.time.format.*;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
import java.util.Arrays;
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

    public boolean is_valid_datetime(String s)
    {
        return _try_dt_parsing(s, DATETIMES);
    }

    static public final DateTimeFormatter[] DATES = {
        DateTimeFormatter.ISO_LOCAL_DATE,
        DateTimeFormatter.BASIC_ISO_DATE
    };

    public boolean is_valid_date(String s)
    {
        return _try_dt_parsing(s, DATES);
    }

    static public final DateTimeFormatter[] TIMES = {
        DateTimeFormatter.ISO_LOCAL_TIME
    };

    public boolean is_valid_time(String s)
    {
        return _try_dt_parsing(s, TIMES);
    }

    public boolean is_valid_regex(String s)
    {
        try {
            Pattern.compile(s);
            return true;
         }
        catch (Exception e) {
            return false;
        }
    }

    static public final Pattern EXREG1 = Pattern.compile("\\($\\w+\\)");
    static public final Pattern EXREG2 = Pattern.compile("\\($\\w+:(.*?)\\)");

    public boolean is_valid_exreg(String s)
    {
        Matcher r1 = EXREG1.matcher(s);
        s = r1.replaceAll(".*?");
        Matcher r2 = EXREG2.matcher(s);
        s = r2.replaceAll("$1");
        return is_valid_regex(s);
    }

    public boolean is_valid_url(String s)
    {
        try {
            new URL(s);
            return true;
        }
        catch (Exception e) {
            return false;
        }
    }

    static public final Pattern EMAIL = Pattern.compile("^[-.\\w]+@[-.\\w]$");

    public boolean is_valid_email(String s)
    {
        return EMAIL.matcher(s).find();
    }

    public boolean is_valid_json(String s)
    {
        try {
            json.fromJSON(s);
            return true;
        }
        catch (Exception e) {
            return false;
        } 
    }

    static public final Pattern UUID =
        Pattern.compile("^[0-9a-fA-F]{8}(-[0-9a-fA-F]){3}[0-9a-fA-F]{12}$");

    public boolean is_valid_uuid(String s)
    {
        return UUID.matcher(s).find();
    }

    // FIXME inefficient, although n log n
    public boolean array_is_unique(Object o)
    {
        int length = json.arrayLength(o);
        if (length < 2)
            return true;

        // extract array of strings
        String[] array = new String[length];
        try {
            for (int i = 0; i < length ; i++)
                array[i] = json.toJSON(json.arrayItem(o, i));
        }
        catch (JSON.Exception e) {
            return false;
        }

        // sort
        Arrays.sort(array);

        // equal neighbors?
        for (int i = 0; i < length - 1; i++)
            if (array[i].equals(array[i+1]))
                return false;
        return true;
    }
}
