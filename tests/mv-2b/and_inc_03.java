
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class and_inc_03 extends ModelChecker
{
    static public final String VERSION = "2";

    public Pattern _jm_re_0_pat = null;
    public Pattern _jm_re_1_pat = null;
    public Pattern _jm_re_2_pat = null;
    public Pattern _jm_re_3_pat = null;
    public Map<String, Checker> and_inc_03_map_pmap;

    public boolean _jm_re_0(String val, Path path, Report rep)
    {
        return _jm_re_0_pat.matcher(val).find();
    }

    public boolean _jm_re_1(String val, Path path, Report rep)
    {
        return _jm_re_1_pat.matcher(val).find();
    }

    public boolean _jm_re_2(String val, Path path, Report rep)
    {
        return _jm_re_2_pat.matcher(val).find();
    }

    public boolean _jm_re_3(String val, Path path, Report rep)
    {
        return _jm_re_3_pat.matcher(val).find();
    }

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        if (! json.isObject(val))
        {
            return false;
        }
        boolean res;
        Iterator<String> prop_loop = json.objectIterator(val);
        while (prop_loop.hasNext())
        {
            String prop = prop_loop.next();
            Object pval = json.objectValue(val, prop);
            if (prop.compareTo("a") == 0)
            {
                res = json.isString(pval) && _jm_re_1(json.asString(pval), null, null) && _jm_re_0(json.asString(pval), null, null);
                if (! res)
                {
                    return false;
                }
                continue;
            }
            else if (prop.compareTo("b") == 0)
            {
                res = json.isString(pval) && _jm_re_3(json.asString(pval), null, null) && _jm_re_2(json.asString(pval), null, null);
                if (! res)
                {
                    return false;
                }
                continue;
            }
            return false;
        }
        return true;
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            _jm_re_0_pat = Pattern.compile("^[aA]");
            _jm_re_1_pat = Pattern.compile("[aA]$");
            _jm_re_2_pat = Pattern.compile("^[bB]");
            _jm_re_3_pat = Pattern.compile("[bB]$");
            and_inc_03_map_pmap = new HashMap<String, Checker>();
            and_inc_03_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
                super.init(json);
            }
            catch (Exception e) {
                throw new Error("cannot initialized model checker: " + e);
            }
        }
    }

    public void free()
    {
        if (initialized)
        {
            super.free();
            _jm_re_0_pat = null;
            _jm_re_1_pat = null;
            _jm_re_2_pat = null;
            _jm_re_3_pat = null;
            and_inc_03_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return and_inc_03_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return and_inc_03_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new and_inc_03();
        Main.main("and_inc_03", checker, VERSION, args);
    }
}
