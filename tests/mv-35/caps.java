
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class caps extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> caps_map_pmap;

    public boolean json_model_2(Object val, Path path, Report rep)
    {
        return json.isString(val);
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
            caps_map_pmap = new HashMap<String, Checker>();
            caps_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_2(o, p, r);} });
            caps_map_pmap.put("OK", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_2(o, p, r);} });
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
            caps_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return caps_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return caps_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new caps();
        Main.main("caps", checker, VERSION, args);
    }
}
