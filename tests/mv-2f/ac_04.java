
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class ac_04 extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> ac_04_map_pmap;

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        return json.isInteger(val) && json.asLong(val) == 42;
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            ac_04_map_pmap = new HashMap<String, Checker>();
            ac_04_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            ac_04_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return ac_04_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return ac_04_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new ac_04();
        Main.main("ac_04", checker, VERSION, args);
    }
}
