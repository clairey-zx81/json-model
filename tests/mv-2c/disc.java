
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class disc extends ModelChecker
{
    static public final String VERSION = "2";

    Map<Object, Checker> _jm_map_0_cmap;
    public Map<String, Checker> disc_map_pmap;

    public boolean _jm_obj_0(Object val, Path path, Report rep)
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
        if (! ((pval = json.objectValue(val, "d")) != null))
        {
            return false;
        }
        boolean res = json.isInteger(pval) && json.asLong(pval) == 0;
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "a")) != null))
        {
            return false;
        }
        return json.isString(pval);
    }

    public boolean _jm_obj_1(Object val, Path path, Report rep)
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
        if (! ((pval = json.objectValue(val, "d")) != null))
        {
            return false;
        }
        boolean res = json.isInteger(pval) && json.asLong(pval) == 1;
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "a")) != null))
        {
            return false;
        }
        return json.isInteger(pval) && json.asLong(pval) >= 0;
    }

    public boolean _jm_obj_2(Object val, Path path, Report rep)
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
        if (! ((pval = json.objectValue(val, "d")) != null))
        {
            return false;
        }
        boolean res = json.isInteger(pval) && json.asLong(pval) == 2;
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "a")) != null))
        {
            return false;
        }
        return json.isNull(pval);
    }

    public boolean _jm_obj_3(Object val, Path path, Report rep)
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
        if (! ((pval = json.objectValue(val, "d")) != null))
        {
            return false;
        }
        boolean res = json.isInteger(pval) && json.asLong(pval) == 3;
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "a")) != null))
        {
            return false;
        }
        return json.isBoolean(pval);
    }


    public boolean json_model_1(Object val, Path path, Report rep)
    {
        boolean res = json.isObject(val);
        if (res)
        {
            if (json.objectHasProp(val, "d"))
            {
                Object tag_0 = json.objectValue(val, "d");
                Checker fun_0 = _jm_map_0_cmap.get(tag_0);
                res = fun_0 != null && fun_0.call(val, null, null);
            }
            else
            {
                res = false;
            }
        }
        return res;
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            _jm_map_0_cmap = new HashMap<Object, Checker>();
            _jm_map_0_cmap.put(json.safeJSON("0"), new Checker() { public boolean call(Object o, Path p, Report r) { return _jm_obj_0(o, p, r);} });
            _jm_map_0_cmap.put(json.safeJSON("1"), new Checker() { public boolean call(Object o, Path p, Report r) { return _jm_obj_1(o, p, r);} });
            _jm_map_0_cmap.put(json.safeJSON("2"), new Checker() { public boolean call(Object o, Path p, Report r) { return _jm_obj_2(o, p, r);} });
            _jm_map_0_cmap.put(json.safeJSON("3"), new Checker() { public boolean call(Object o, Path p, Report r) { return _jm_obj_3(o, p, r);} });
            disc_map_pmap = new HashMap<String, Checker>();
            disc_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            _jm_map_0_cmap = null;
            disc_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return disc_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return disc_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new disc();
        Main.main("disc", checker, VERSION, args);
    }
}
