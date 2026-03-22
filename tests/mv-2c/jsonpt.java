
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class jsonpt extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> jsonpt_map_pmap;
    public Pattern jm_is_jsonpt_pat = null;

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        return json.isString(val) && jm_is_jsonpt(json.asString(val), null, null);
    }


    public boolean jm_is_jsonpt(String val, Path path, Report rep)
    {
        return jm_is_jsonpt_pat.matcher(val).find();
    }

    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            jsonpt_map_pmap = new HashMap<String, Checker>();
            jsonpt_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
            jm_is_jsonpt_pat = Pattern.compile("(?s)^(/([^~]|~0|~1)*)*$");
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
            jsonpt_map_pmap = null;
            jm_is_jsonpt_pat = null;
        }
    }

    public Checker get(String name)
    {
        return jsonpt_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return jsonpt_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new jsonpt();
        Main.main("jsonpt", checker, VERSION, args);
    }
}
