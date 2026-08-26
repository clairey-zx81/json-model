
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class jmc_errors extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> jmc_errors_map_pmap;

    public boolean json_model_2(Object val, Path path, Report rep)
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
                res = json.isInteger(arr_0_item) && json.asLong(arr_0_item) >= 0;
                if (! res)
                    break;
            }
        }
        if (res)
            res = rt.array_is_unique(val, null, null);
        return res;
    }

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        if (! json.isObject(val))
            return false;
        boolean res;
        Iterator<String> prop_loop = json.objectIterator(val);
        while (prop_loop.hasNext())
        {
            String prop = prop_loop.next();
            Object pval = json.objectValue(val, prop);
            if (prop.compareTo("schema") == 0)
            {
                res = json_model_2(pval, null, null);
                if (! res)
                    return false;
                continue;
            }
            else if (prop.compareTo("dynpy") == 0)
            {
                res = json_model_2(pval, null, null);
                if (! res)
                    return false;
                continue;
            }
            else if (prop.compareTo("js") == 0)
            {
                res = json_model_2(pval, null, null);
                if (! res)
                    return false;
                continue;
            }
            else if (prop.compareTo("sql") == 0)
            {
                res = json_model_2(pval, null, null);
                if (! res)
                    return false;
                continue;
            }
            else if (prop.compareTo("pl") == 0)
            {
                res = json_model_2(pval, null, null);
                if (! res)
                    return false;
                continue;
            }
            else if (prop.compareTo("java") == 0)
            {
                res = json_model_2(pval, null, null);
                if (! res)
                    return false;
                continue;
            }
            else if (prop.compareTo("c") == 0)
            {
                res = json_model_2(pval, null, null);
                if (! res)
                    return false;
                continue;
            }
            else if (prop.compareTo("py") == 0)
            {
                res = json_model_2(pval, null, null);
                if (! res)
                    return false;
                continue;
            }
            else if (prop.compareTo("ts") == 0)
            {
                res = json.isBoolean(pval);
                if (! res)
                    return false;
                continue;
            }
            else if (prop.compareTo("auto.diverse") == 0)
            {
                res = json.isBoolean(pval);
                if (! res)
                    return false;
                continue;
            }
            if (prop.startsWith("#"))
            {
                res = json.isString(pval);
                if (! res)
                    return false;
            }
            else
                return false;
        }
        return true;
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            jmc_errors_map_pmap = new HashMap<String, Checker>();
            jmc_errors_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
            jmc_errors_map_pmap.put("ErrorIndex", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_2(o, p, r);} });
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
            jmc_errors_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return jmc_errors_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return jmc_errors_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new jmc_errors();
        Main.main("jmc_errors", checker, VERSION, args);
    }
}
