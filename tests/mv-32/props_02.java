
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class props_02 extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> props_02_map_pmap;

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        return false;
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            props_02_map_pmap = new HashMap<String, Checker>();
            props_02_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            props_02_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return props_02_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return props_02_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new props_02();
        Main.main("props_02", checker, VERSION, args);
    }
}
