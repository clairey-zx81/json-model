
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class dl_00 extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> dl_00_map_pmap;

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
            res = json_model_2(pval, null, null);
            if (! res)
            {
                return false;
            }
        }
        return true;
    }

    public boolean json_model_2(Object val, Path path, Report rep)
    {
        return json.isBoolean(val) || _jm_obj_0(val, null, null);
    }

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        return json_model_2(val, null, null);
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            dl_00_map_pmap = new HashMap<String, Checker>();
            dl_00_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_2(o, p, r);} });
            dl_00_map_pmap.put("rec", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_2(o, p, r);} });
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
            dl_00_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return dl_00_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return dl_00_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new dl_00();
        Main.main("dl_00", checker, VERSION, args);
    }
}
