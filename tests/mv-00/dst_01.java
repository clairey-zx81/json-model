
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class dst_01 extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> dst_01_map_pmap;

    public boolean _jm_obj_0(Object val, Path path, Report rep)
    {
        if (json.objectSize(val) != 3)
        {
            return false;
        }
        Object pval;
        boolean res;
        if (! ((pval = json.objectValue(val, "a")) != null))
        {
            return false;
        }
        res = json.isInteger(pval) && json.asLong(pval) >= 0;
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "c")) != null))
        {
            return false;
        }
        res = json.isInteger(pval) && json.asLong(pval) >= 1;
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "f")) != null))
        {
            return false;
        }
        return json.isString(pval);
    }

    public boolean _jm_obj_1(Object val, Path path, Report rep)
    {
        if (json.objectSize(val) != 3)
        {
            return false;
        }
        Object pval;
        boolean res;
        if (! ((pval = json.objectValue(val, "a")) != null))
        {
            return false;
        }
        res = json.isInteger(pval) && json.asLong(pval) >= 0;
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "c")) != null))
        {
            return false;
        }
        res = json.isInteger(pval) && json.asLong(pval) >= 1;
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "e")) != null))
        {
            return false;
        }
        return json.isString(pval);
    }

    public boolean _jm_obj_2(Object val, Path path, Report rep)
    {
        if (json.objectSize(val) != 3)
        {
            return false;
        }
        Object pval;
        boolean res;
        if (! ((pval = json.objectValue(val, "a")) != null))
        {
            return false;
        }
        res = json.isInteger(pval) && json.asLong(pval) >= 0;
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "c")) != null))
        {
            return false;
        }
        res = json.isInteger(pval) && json.asLong(pval) >= 1;
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "d")) != null))
        {
            return false;
        }
        return json.isString(pval);
    }

    public boolean _jm_obj_3(Object val, Path path, Report rep)
    {
        if (json.objectSize(val) != 3)
        {
            return false;
        }
        Object pval;
        boolean res;
        if (! ((pval = json.objectValue(val, "a")) != null))
        {
            return false;
        }
        res = json.isInteger(pval) && json.asLong(pval) >= 0;
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "b")) != null))
        {
            return false;
        }
        res = json.isInteger(pval) && json.asLong(pval) >= 1;
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "f")) != null))
        {
            return false;
        }
        return json.isString(pval);
    }

    public boolean _jm_obj_4(Object val, Path path, Report rep)
    {
        if (json.objectSize(val) != 3)
        {
            return false;
        }
        Object pval;
        boolean res;
        if (! ((pval = json.objectValue(val, "a")) != null))
        {
            return false;
        }
        res = json.isInteger(pval) && json.asLong(pval) >= 0;
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "b")) != null))
        {
            return false;
        }
        res = json.isInteger(pval) && json.asLong(pval) >= 1;
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "e")) != null))
        {
            return false;
        }
        return json.isString(pval);
    }

    public boolean _jm_obj_5(Object val, Path path, Report rep)
    {
        if (json.objectSize(val) != 3)
        {
            return false;
        }
        Object pval;
        boolean res;
        if (! ((pval = json.objectValue(val, "a")) != null))
        {
            return false;
        }
        res = json.isInteger(pval) && json.asLong(pval) >= 0;
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "b")) != null))
        {
            return false;
        }
        res = json.isInteger(pval) && json.asLong(pval) >= 1;
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "d")) != null))
        {
            return false;
        }
        return json.isString(pval);
    }

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        return json.isObject(val) && (json.objectHasProp(val, "d") && _jm_obj_5(val, null, null) || json.objectHasProp(val, "e") && _jm_obj_4(val, null, null) || json.objectHasProp(val, "f") && _jm_obj_3(val, null, null) || json.objectHasProp(val, "d") && _jm_obj_2(val, null, null) || json.objectHasProp(val, "e") && _jm_obj_1(val, null, null) || json.objectHasProp(val, "f") && _jm_obj_0(val, null, null));
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            dst_01_map_pmap = new HashMap<String, Checker>();
            dst_01_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            dst_01_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return dst_01_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return dst_01_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new dst_01();
        Main.main("dst_01", checker, VERSION, args);
    }
}
