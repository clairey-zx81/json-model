
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class nprops extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> nprops_map_pmap;

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
            if (prop.startsWith("a"))
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

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        boolean res = _jm_obj_0(val, null, null);
        if (res)
        {
            long ival_0 = json.objectSize(val);
            res = ival_0 <= 2 && ival_0 >= 1;
        }
        return res;
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            nprops_map_pmap = new HashMap<String, Checker>();
            nprops_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            nprops_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return nprops_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return nprops_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new nprops();
        Main.main("nprops", checker, VERSION, args);
    }
}
