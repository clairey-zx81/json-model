
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class mu extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> mu_map_pmap;

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        return json.isString(val) && json.asString(val).compareTo("\u03bc") == 0;
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            mu_map_pmap = new HashMap<String, Checker>();
            mu_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            mu_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return mu_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return mu_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new mu();
        Main.main("mu", checker, VERSION, args);
    }
}
