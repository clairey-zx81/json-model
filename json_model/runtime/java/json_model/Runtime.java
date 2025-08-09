package json_model;

import java.time.format.*;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
import java.util.Arrays;
import java.net.URI;
import java.net.URL;

public class Runtime
{
    public enum Operator {
        EQ, NE, LE, LT, GE, GT
    }

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
        DateTimeFormatter.ISO_LOCAL_DATE_TIME,
        DateTimeFormatter.ISO_OFFSET_DATE_TIME
    };

    public boolean is_valid_datetime(String s)
    {
        return _try_dt_parsing(s.replace(" ", "T"), DATETIMES);
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
        DateTimeFormatter.ISO_LOCAL_TIME,
        DateTimeFormatter.ISO_OFFSET_TIME
    };

    static public final Pattern
        TIME1 = Pattern.compile("^([01][0-9]|2[0-3])[0-5][0-9][0-5][0-9](\\.[0-9]*)?$"),
        TIME2 = Pattern.compile("^([01][0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9](\\.[0-9]*)?([-+][01][0-9])?$");

    public boolean is_valid_time(String s)
    {
        if (s.length() == 0)
            return false;
        if (s.startsWith("T"))
            s = s.substring(1);
        if (_try_dt_parsing(s, TIMES))
            return true;
        // java is not very good at times
        if (TIME1.matcher(s).find())
            return true;
        return TIME2.matcher(s).find();
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

    static public final Pattern
        EXREG1 = Pattern.compile("\\($\\w+\\)"),
        EXREG2 = Pattern.compile("\\($\\w+:(.*?)\\)");

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
            new URI(s).toURL();
            return true;
        }
        catch (Exception e) {
            return false;
        }
    }

    static public final Pattern EMAIL = Pattern.compile("^[-.\\w]+@[-.\\w]+$");

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
        Pattern.compile("^[0-9a-fA-F]{8}(-[0-9a-fA-F]{4}){3}-[0-9a-fA-F]{12}$");

    public boolean is_valid_uuid(String s)
    {
        return UUID.matcher(s).find();
    }

    // FIXME inefficient, although n log n
    public boolean array_is_unique(Object o, Path path, Report rep)
    {
        if (!json.isArray(o))
            return false;
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

    public long any_int(Object o)
    {
        if (json.isArray(o))
            return json.arrayLength(o);
        if (json.isObject(o))
            return json.objectSize(o);
        if (json.isString(o))
            return json.asString(o).length();
        return json.asLong(o);
    }

    public boolean check_constraint(Object val, Operator op, Object cst, Path path, Report rep)
    {
        JSON.JType
            tc = json.type(cst),
            tv = json.type(val);

        switch (tc) {
            case JSON.JType.INTEGER:
                long vi = any_int(val), ci = json.asLong(cst);
                switch (op) {
                    case Operator.EQ:
                        return vi == ci;
                    case Operator.NE:
                        return vi != ci;
                    case Operator.LE:
                        return vi <= ci;
                    case Operator.LT:
                        return vi < ci;
                    case Operator.GE:
                        return vi >= ci;
                    case Operator.GT:
                        return vi > ci;
                    default:
                        throw new Error("unexpected comparison operator " + op);
                }
            case JSON.JType.NUMBER:
                double cd = json.asNumber(cst), vd = json.asNumber(val);
                switch (op) {
                    case Operator.EQ:
                        return vd == cd;
                    case Operator.NE:
                        return vd != cd;
                    case Operator.LE:
                        return vd <= cd;
                    case Operator.LT:
                        return vd < cd;
                    case Operator.GE:
                        return vd >= cd;
                    case Operator.GT:
                        return vd > cd;
                    default:
                        throw new Error("unexpected comparison operator " + op);
                }
            case JSON.JType.STRING:
                String cs = json.asString(cst), vs = json.asString(val);
                int cmp = vs.compareTo(cs);
                switch (op) {
                    case Operator.EQ:
                        return cmp == 0;
                    case Operator.NE:
                        return cmp != 0;
                    case Operator.LE:
                        return cmp <= 0;
                    case Operator.LT:
                        return cmp < 0;
                    case Operator.GE:
                        return cmp >= 0;
                    case Operator.GT:
                        return cmp > 0;
                    default:
                        throw new Error("unexpected comparison operator " + op);
                }
            default:
                throw new Error("not implemented yet for json type " + tc);
        }
    }
}
