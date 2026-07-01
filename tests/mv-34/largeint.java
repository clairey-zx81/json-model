
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class largeint extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> largeint_map_pmap;

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        return ((json.isInteger(val) || (json.isDouble(val) && json.asDouble(val) == ((long) json.asDouble(val))))) && json.asLong(val) == 9876543210L;
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            largeint_map_pmap = new HashMap<String, Checker>();
            largeint_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            largeint_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return largeint_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return largeint_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new largeint();
        Main.main("largeint", checker, VERSION, args);
    }
}
