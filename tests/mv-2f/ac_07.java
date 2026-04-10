
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class ac_07 extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> ac_07_map_pmap;

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        if (! json.isObject(val))
        {
            return false;
        }
        boolean res;
        long must_count = 0;
        Iterator<String> prop_loop = json.objectIterator(val);
        while (prop_loop.hasNext())
        {
            String prop = prop_loop.next();
            Object pval = json.objectValue(val, prop);
            if (prop.compareTo("a") == 0)
            {
                must_count += 1;
                res = json.isInteger(pval) && json.asLong(pval) >= 1;
                if (! res)
                {
                    return false;
                }
                continue;
            }
            if (prop.compareTo("b") == 0)
            {
                res = json.isInteger(pval) && json.asLong(pval) >= 1;
                if (! res)
                {
                    return false;
                }
                continue;
            }
            return false;
        }
        return must_count == 1;
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            ac_07_map_pmap = new HashMap<String, Checker>();
            ac_07_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            ac_07_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return ac_07_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return ac_07_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new ac_07();
        Main.main("ac_07", checker, VERSION, args);
    }
}
