
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class jmc_tests extends ModelChecker
{
    static public final String VERSION = "2";

    public Pattern _jm_re_0_pat = null;
    public Map<String, Checker> jmc_tests_map_pmap;

    public boolean json_model_2(Object val, Path path, Report rep)
    {
        return json.isString(val) && json.asString(val).startsWith("#");
    }

    public boolean json_model_3(Object val, Path path, Report rep)
    {
        boolean res = json.isArray(val) && json.arrayLength(val) == 2;
        if (res)
        {
            res = json.isBoolean(json.arrayItem(val, 0));
            if (res)
                res = true;
        }
        return res;
    }

    public boolean _jm_re_0(String val, Path path, Report rep)
    {
        return _jm_re_0_pat.matcher(val).find();
    }

    public boolean json_model_4(Object val, Path path, Report rep)
    {
        boolean res = json.isArray(val) && json.arrayLength(val) == 3;
        if (res)
        {
            res = json.isBoolean(json.arrayItem(val, 0));
            if (res)
            {
                res = json.isString(json.arrayItem(val, 1)) && _jm_re_0(json.asString(json.arrayItem(val, 1)), null, null);
                if (res)
                    res = true;
            }
        }
        return res;
    }

    public boolean json_model_5(Object val, Path path, Report rep)
    {
        return json_model_2(val, null, null) || json_model_3(val, null, null) || json_model_4(val, null, null);
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
                res = json_model_5(arr_0_item, null, null);
                if (! res)
                    break;
            }
        }
        return res;
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            _jm_re_0_pat = Pattern.compile("(?s)^[-\\w]*$");
            jmc_tests_map_pmap = new HashMap<String, Checker>();
            jmc_tests_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
            jmc_tests_map_pmap.put("Comment", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_2(o, p, r);} });
            jmc_tests_map_pmap.put("Test2", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_3(o, p, r);} });
            jmc_tests_map_pmap.put("Test3", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_4(o, p, r);} });
            jmc_tests_map_pmap.put("Test", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_5(o, p, r);} });
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
            jmc_tests_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return jmc_tests_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return jmc_tests_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new jmc_tests();
        Main.main("jmc_tests", checker, VERSION, args);
    }
}
