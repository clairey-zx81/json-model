
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class ac_03 extends ModelChecker
{
    static public final String VERSION = "2";

    public Pattern _jm_re_0_pat = null;
    public Pattern _jm_re_1_pat = null;
    public Map<String, Checker> ac_03_map_pmap;

    public boolean _jm_re_0(String val, Path path, Report rep)
    {
        return _jm_re_0_pat.matcher(val).find();
    }

    public boolean _jm_re_1(String val, Path path, Report rep)
    {
        return _jm_re_1_pat.matcher(val).find();
    }

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        boolean res = json.isArray(val);
        if (res)
        {
            int arr_1_idx = -1;
            Iterator<Object> arr_1_item_loop = json.arrayIterator(val);
            while (arr_1_item_loop.hasNext())
            {
                arr_1_idx++;
                Object arr_1_item = arr_1_item_loop.next();
                res = json.isString(arr_1_item) && _jm_re_1(json.asString(arr_1_item), null, null);
                if (! res)
                {
                    break;
                }
            }
            if (res)
            {
                int arr_0_idx = -1;
                Iterator<Object> arr_0_item_loop = json.arrayIterator(val);
                while (arr_0_item_loop.hasNext())
                {
                    arr_0_idx++;
                    Object arr_0_item = arr_0_item_loop.next();
                    res = json.isString(arr_0_item) && _jm_re_0(json.asString(arr_0_item), null, null);
                    if (! res)
                    {
                        break;
                    }
                }
            }
        }
        return res;
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            _jm_re_0_pat = Pattern.compile("y");
            _jm_re_1_pat = Pattern.compile("x");
            ac_03_map_pmap = new HashMap<String, Checker>();
            ac_03_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            ac_03_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return ac_03_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return ac_03_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new ac_03();
        Main.main("ac_03", checker, VERSION, args);
    }
}
