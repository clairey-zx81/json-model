
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class md3_hobbes extends ModelChecker
{
    static public final String VERSION = "2";

    public Pattern _jm_re_0_pat = null;
    public Map<String, Checker> md3_hobbes_map_pmap;

    public boolean _jm_re_0(String val, Path path, Report rep)
    {
        return _jm_re_0_pat.matcher(val).find();
    }

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        if (! json.isObject(val))
            return false;
        boolean res;
        long must_count = 0;
        Iterator<String> prop_loop = json.objectIterator(val);
        while (prop_loop.hasNext())
        {
            String prop = prop_loop.next();
            Object pval = json.objectValue(val, prop);
            if (prop.compareTo("name") == 0)
            {
                must_count += 1;
                res = json.isString(pval) && _jm_re_0(json.asString(pval), null, null);
                if (! res)
                    return false;
                continue;
            }
            else if (prop.compareTo("birth") == 0)
            {
                must_count += 1;
                res = json.isString(pval) && rt.is_valid_date(json.asString(pval));
                if (! res)
                    return false;
                continue;
            }
            if (prop.compareTo("friends") == 0)
            {
                res = json.isArray(pval);
                if (res)
                {
                    int arr_0_idx = -1;
                    Iterator<Object> arr_0_item_loop = json.arrayIterator(pval);
                    while (arr_0_item_loop.hasNext())
                    {
                        arr_0_idx++;
                        Object arr_0_item = arr_0_item_loop.next();
                        res = json.isString(arr_0_item) && _jm_re_0(json.asString(arr_0_item), null, null);
                        if (! res)
                            break;
                    }
                }
                if (! res)
                    return false;
                continue;
            }
            return false;
        }
        return must_count == 2;
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            _jm_re_0_pat = Pattern.compile("(?s)^\\w+$");
            md3_hobbes_map_pmap = new HashMap<String, Checker>();
            md3_hobbes_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            md3_hobbes_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return md3_hobbes_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return md3_hobbes_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new md3_hobbes();
        Main.main("md3_hobbes", checker, VERSION, args);
    }
}
