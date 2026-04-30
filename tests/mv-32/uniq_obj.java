
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class uniq_obj extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> uniq_obj_map_pmap;

    public boolean json_model_2(Object val, Path path, Report rep)
    {
        if (! json.isObject(val))
        {
            return false;
        }
        if (json.objectSize(val) != 2)
        {
            return false;
        }
        Object pval;
        if (! ((pval = json.objectValue(val, "x")) != null))
        {
            return false;
        }
        boolean res = json.isString(pval);
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "y")) != null))
        {
            return false;
        }
        return json.isString(pval);
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
                res = json_model_2(arr_0_item, null, null);
                if (! res)
                {
                    break;
                }
            }
        }
        if (res)
        {
            res = rt.array_is_unique(val, null, null);
        }
        return res;
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            uniq_obj_map_pmap = new HashMap<String, Checker>();
            uniq_obj_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
            uniq_obj_map_pmap.put("XY", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_2(o, p, r);} });
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
            uniq_obj_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return uniq_obj_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return uniq_obj_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new uniq_obj();
        Main.main("uniq_obj", checker, VERSION, args);
    }
}
