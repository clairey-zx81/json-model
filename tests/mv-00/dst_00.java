
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class dst_00 extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> dst_00_map_pmap;

    public boolean _jm_obj_0(Object val, Path path, Report rep)
    {
        if (json.objectSize(val) != 2)
        {
            return false;
        }
        Object pval;
        if (! ((pval = json.objectValue(val, "a")) != null))
        {
            return false;
        }
        boolean res = json.isInteger(pval) && json.asLong(pval) >= 0;
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "c")) != null))
        {
            return false;
        }
        return json.isString(pval);
    }

    public boolean _jm_obj_1(Object val, Path path, Report rep)
    {
        if (json.objectSize(val) != 2)
        {
            return false;
        }
        Object pval;
        if (! ((pval = json.objectValue(val, "a")) != null))
        {
            return false;
        }
        boolean res = json.isInteger(pval) && json.asLong(pval) >= 0;
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "b")) != null))
        {
            return false;
        }
        return json.isInteger(pval) && json.asLong(pval) >= 1;
    }

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        boolean res = json.isObject(val);
        if (res)
        {
            if (json.objectHasProp(val, "b"))
            {
                res = _jm_obj_1(val, null, null);
            }
            else
            {
                res = json.objectHasProp(val, "c") && _jm_obj_0(val, null, null);
            }
        }
        return res;
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            dst_00_map_pmap = new HashMap<String, Checker>();
            dst_00_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            dst_00_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return dst_00_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return dst_00_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new dst_00();
        Main.main("dst_00", checker, VERSION, args);
    }
}
