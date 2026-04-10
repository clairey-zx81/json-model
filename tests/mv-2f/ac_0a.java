
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class ac_0a extends ModelChecker
{
    static public final String VERSION = "2";

    public Pattern _jm_re_0_pat = null;
    public Map<String, Checker> ac_0a_map_pmap;

    public boolean _jm_re_0(String val, Path path, Report rep)
    {
        return _jm_re_0_pat.matcher(val).find();
    }

    public boolean json_model_2(Object val, Path path, Report rep)
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
            if (_jm_re_0(prop, null, null))
            {
                res = json_model_2(pval, null, null);
                if (! res)
                {
                    return false;
                }
            }
            else
            {
                return false;
            }
        }
        return true;
    }

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        return json_model_2(val, null, null);
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            _jm_re_0_pat = Pattern.compile("^[a-zA-Z]+$");
            ac_0a_map_pmap = new HashMap<String, Checker>();
            ac_0a_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_2(o, p, r);} });
            ac_0a_map_pmap.put("map", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_2(o, p, r);} });
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
            ac_0a_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return ac_0a_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return ac_0a_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new ac_0a();
        Main.main("ac_0a", checker, VERSION, args);
    }
}
