package json_model;

import java.time.format.*;
import java.util.regex.Pattern;
import java.util.regex.Matcher;
import java.util.Arrays;
import java.util.Comparator;
import java.util.Iterator;
import java.net.URI;
import java.net.URL;

/**
 * JSON Model Java Runtime: the actual runtime.
 */
public class Runtime
{
    /** Comparison operators */
    public enum Operator {
        EQ, NE, LE, LT, GE, GT
    }

    /** JSON library interface */
    private JSON<Object> json;

    /** Runtime constructor */
    public Runtime(JSON<Object> json)
    {
        this.json = json;
    }

    /** Date/Time parsers helper */
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

    /** DateTime parsing helper */
    static public final DateTimeFormatter[] DATETIMES = {
        DateTimeFormatter.ISO_INSTANT,
        DateTimeFormatter.ISO_LOCAL_DATE_TIME,
        DateTimeFormatter.ISO_OFFSET_DATE_TIME
    };

    /** Is it a datetime? */
    public boolean is_valid_datetime(String s)
    {
        return _try_dt_parsing(s.replace(" ", "T"), DATETIMES);
    }

    /** Date parsing helper */
    static public final DateTimeFormatter[] DATES = {
        DateTimeFormatter.ISO_LOCAL_DATE,
        DateTimeFormatter.BASIC_ISO_DATE
    };

    /** Is it a date? */
    public boolean is_valid_date(String s)
    {
        return _try_dt_parsing(s, DATES);
    }

    /** Time parsing helper */
    static public final DateTimeFormatter[] TIMES = {
        DateTimeFormatter.ISO_LOCAL_TIME,
        DateTimeFormatter.ISO_OFFSET_TIME
    };

    /** Also try parsing time with regular expressions... */
    static public final Pattern
        TIME1 = Pattern.compile("^([01][0-9]|2[0-3])[0-5][0-9][0-5][0-9](\\.[0-9]*)?$"),
        TIME2 = Pattern.compile("^([01][0-9]|2[0-3]):[0-5][0-9]:[0-5][0-9](\\.[0-9]*)?([-+][01][0-9])?$");

    /** Is it a time? */
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

    /** Is it a regular expression? */
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

    /** Normalization helpers for Extended Regular Expressions */
    static public final Pattern
        EXREG1 = Pattern.compile("\\($\\w+\\)"),
        EXREG2 = Pattern.compile("\\($\\w+:(.*?)\\)");

    /** Is it an extended regular expression? */
    public boolean is_valid_exreg(String s)
    {
        Matcher r1 = EXREG1.matcher(s);
        s = r1.replaceAll(".*?");
        Matcher r2 = EXREG2.matcher(s);
        s = r2.replaceAll("$1");
        return is_valid_regex(s);
    }

    /** Is it a URL? */
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

    /** Email helper */
    static public final Pattern EMAIL = Pattern.compile("^[-.\\w]+@[-.\\w]+$");

    /** Is it an email? */
    public boolean is_valid_email(String s)
    {
        return EMAIL.matcher(s).find();
    }

    /** It it JSON? */
    public boolean is_valid_json(String s)
    {
        try {
            if (s.equals(""))
                return false;
            json.fromJSON(s);
            return true;
        }
        catch (Exception e) {
            return false;
        } 
    }

    /** UUID helper */
    static public final Pattern UUID =
        Pattern.compile("^[0-9a-fA-F]{8}(-[0-9a-fA-F]{4}){3}-[0-9a-fA-F]{12}$");

    /** Is it a UUID? */
    public boolean is_valid_uuid(String s)
    {
        return UUID.matcher(s).find();
    }

    /** JSON thing total order */
    int jcmp(Object o1, Object o2)
    {
        int t1 = json.type(o1), t2 = json.type(o2);
        if (t1 != t2)
            return t2 - t1;
        // same type, do typed comparison
        if (t1 == JSON.NULL)
            return 0;
        if (t1 == JSON.BOOLEAN)
            if (json.asBoolean(o1))
                return json.asBoolean(o2) ? 0 : 1;
            else
                return json.asBoolean(o2) ? -1 : 0;
        if (t1 == JSON.INTEGER) {
            long i1 = json.asLong(o1), i2 = json.asLong(o2);
            return i1 < i2 ? -1 : i1 == i2 ? 0 : 1;
        }
        if (t1 == JSON.NUMBER) {
            double d1 = json.asDouble(o1), d2 = json.asDouble(o2);
            return d1 < d2 ? -1 : d1 == d2 ? 0 : 1;
        }
        if (t1 == JSON.STRING) {
            String s1 = json.asString(o1), s2 = json.asString(o2);
            return s1.compareTo(s2);
        }
        if (t1 == JSON.ARRAY) {
            int len1 = json.arrayLength(o1), len2 = json.arrayLength(o2);
            if (len1 != len2)
                return len2 - len1;
            // same length, compare items
            for (int i = 0; i < len1 ; i++) {
                int cmp = jcmp(json.arrayItem(o1, i), json.arrayItem(o2, i));
                if (cmp != 0)
                    return cmp;
            }
            return 0;
        }
        // both objects
        if (t1 == JSON.OBJECT) {
            int len1 = json.objectSize(o1), len2 = json.objectSize(o2);
            if (len1 != len2)
                return len2 - len1;
            // same size
            String[] p1 = new String[len1], p2 = new String[len1];
            Iterator<String>
                i1 = json.objectIterator(o1),
                i2 = json.objectIterator(o2);
            for (int i = 0; i < len1; i++) {
                p1[i] = i1.next();
                p2[i] = i2.next();
            }
            Arrays.sort(p1);
            Arrays.sort(p2);
            // lexicographic property name comparison
            for (int i = 0; i < len1; i++) {
                int cmp = p1[i].compareTo(p2[i]);
                if (cmp != 0)
                    return cmp;
            }
            // same properties, look at first differing values
            for (int i = 0; i < len1; i++) {
                Object
                    v1 = json.objectValue(o1, p1[i]),
                    v2 = json.objectValue(o2, p2[i]);
                int cmp = jcmp(v1, v2);
                if (cmp != 0)
                    return cmp;
            }
        }
        return 0;
    }

    /** Is it a unique array? */
    public boolean array_is_unique(Object o, Path path, Report rep)
    {
        if (!json.isArray(o))
            return false;
        int length = json.arrayLength(o);
        if (length < 2)
            return true;

        // extract array of things
        Object[] array = new Object[length];
        for (int i = 0; i < length; i++)
            array[i] = json.arrayItem(o, i);

        // sort
        Arrays.sort(
            array,
            new Comparator<Object>() {
                public int compare(Object o1, Object o2) {
                    return jcmp(o1, o2);
                }
            }
        );

        // equal neighbors?
        for (int i = 0; i < length - 1; i++)
            if (this.jcmp(array[i], array[i+1]) == 0)
                return false;

        return true;
    }

    /** Get an int out of a JSON thing */
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

    /** Generic constraint check */
    public boolean check_constraint(Object val, Operator op, Object cst, Path path, Report rep)
    {
        int tc = json.type(cst), tv = json.type(val);

        switch (tc) {
            case JSON.INTEGER:
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
            case JSON.NUMBER:
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
            case JSON.STRING:
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
