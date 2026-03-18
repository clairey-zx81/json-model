
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class and_inc_00 extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> and_inc_00_map_pmap;

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
            if (prop.startsWith("foo"))
            {
                res = json.isString(pval);
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


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            and_inc_00_map_pmap = new HashMap<String, Checker>();
            and_inc_00_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            and_inc_00_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return and_inc_00_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return and_inc_00_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new and_inc_00();
        Main.main("and_inc_00", checker, VERSION, args);
    }
}
