
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class def_00 extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> def_00_map_pmap;

    public boolean json_model_2(Object val, Path path, Report rep)
    {
        return json.isDouble(val) && json.asDouble(val) >= 0.0;
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
            def_00_map_pmap = new HashMap<String, Checker>();
            def_00_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_2(o, p, r);} });
            def_00_map_pmap.put("pos", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_2(o, p, r);} });
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
            def_00_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return def_00_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return def_00_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new def_00();
        Main.main("def_00", checker, VERSION, args);
    }
}
