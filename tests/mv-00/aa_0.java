
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class aa_0 extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> aa_0_map_pmap;

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
                res = json.isArray(arr_0_item);
                if (res)
                {
                    int arr_1_idx = -1;
                    Iterator<Object> arr_1_item_loop = json.arrayIterator(arr_0_item);
                    while (arr_1_item_loop.hasNext())
                    {
                        arr_1_idx++;
                        Object arr_1_item = arr_1_item_loop.next();
                        res = json.isString(arr_1_item);
                        if (! res)
                        {
                            break;
                        }
                    }
                }
                if (! res)
                {
                    break;
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
            aa_0_map_pmap = new HashMap<String, Checker>();
            aa_0_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            aa_0_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return aa_0_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return aa_0_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new aa_0();
        Main.main("aa_0", checker, VERSION, args);
    }
}
