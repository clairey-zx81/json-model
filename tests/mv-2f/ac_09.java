
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class ac_09 extends ModelChecker
{
    static public final String VERSION = "2";

    public Pattern _jm_re_0_pat = null;
    public Map<String, Checker> ac_09_map_pmap;

    public boolean _jm_re_0(String val, Path path, Report rep)
    {
        return _jm_re_0_pat.matcher(val).find();
    }

    public boolean _jm_obj_0(Object val, Path path, Report rep)
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
                res = json.isString(pval) && json.asString(pval).startsWith("bla");
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
        boolean res = json.isArray(val);
        if (res)
        {
            int arr_0_idx = -1;
            Iterator<Object> arr_0_item_loop = json.arrayIterator(val);
            while (arr_0_item_loop.hasNext())
            {
                arr_0_idx++;
                Object arr_0_item = arr_0_item_loop.next();
                res = json.isString(arr_0_item) && json.asString(arr_0_item).startsWith("foo");
                if (! res)
                {
                    break;
                }
            }
        }
        return res || _jm_obj_0(val, null, null);
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            _jm_re_0_pat = Pattern.compile("^[a-zA-Z]+$");
            ac_09_map_pmap = new HashMap<String, Checker>();
            ac_09_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            ac_09_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return ac_09_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return ac_09_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new ac_09();
        Main.main("ac_09", checker, VERSION, args);
    }
}
