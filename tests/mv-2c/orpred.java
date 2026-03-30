
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class orpred extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> orpred_map_pmap;

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        return json.isString(val) && (json.isString(val) && rt.is_valid_date(json.asString(val)) || json.isString(val) && rt.is_valid_time(json.asString(val)));
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            orpred_map_pmap = new HashMap<String, Checker>();
            orpred_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            orpred_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return orpred_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return orpred_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new orpred();
        Main.main("orpred", checker, VERSION, args);
    }
}
