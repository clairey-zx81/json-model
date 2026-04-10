
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class ac_00 extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> ac_00_map_pmap;

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        if (! json.isObject(val))
        {
            return false;
        }
        Object pval;
        if (! ((pval = json.objectValue(val, "a")) != null))
        {
            return false;
        }
        boolean res = json.isString(pval);
        if (! res)
        {
            return false;
        }
        if (! ((pval = json.objectValue(val, "b")) != null))
        {
            return false;
        }
        res = json.isString(pval);
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


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            ac_00_map_pmap = new HashMap<String, Checker>();
            ac_00_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            ac_00_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return ac_00_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return ac_00_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new ac_00();
        Main.main("ac_00", checker, VERSION, args);
    }
}
