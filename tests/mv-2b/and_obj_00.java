
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class and_obj_00 extends ModelChecker
{
    static public final String VERSION = "2";

    public Pattern _jm_re_0_pat = null;
    public Map<String, Checker> and_obj_00_map_pmap;

    public boolean _jm_re_0(String val, Path path, Report rep)
    {
        return _jm_re_0_pat.matcher(val).find();
    }

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        if (! json.isObject(val))
        {
            return false;
        }
        if (json.objectSize(val) != 1)
        {
            return false;
        }
        Object pval;
        boolean res;
        if (! ((pval = json.objectValue(val, "a")) != null))
        {
            return false;
        }
        return json.isString(pval) && _jm_re_0(json.asString(pval), null, null);
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            _jm_re_0_pat = Pattern.compile("^[aA]");
            and_obj_00_map_pmap = new HashMap<String, Checker>();
            and_obj_00_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            and_obj_00_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return and_obj_00_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return and_obj_00_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new and_obj_00();
        Main.main("and_obj_00", checker, VERSION, args);
    }
}
