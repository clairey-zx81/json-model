
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class duration extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> duration_map_pmap;
    public Pattern jm_is_duration_pat = null;

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        return json.isString(val) && jm_is_duration(json.asString(val), null, null);
    }


    public boolean jm_is_duration(String val, Path path, Report rep)
    {
        return jm_is_duration_pat.matcher(val).find();
    }

    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            duration_map_pmap = new HashMap<String, Checker>();
            duration_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
            jm_is_duration_pat = Pattern.compile("^P(([0-9]+D|[0-9]+M([0-9]+D)?|[0-9]+Y([0-9]+M([0-9]+D)?)?)(T([0-9]+H([0-9]+M([0-9]+S)?)?|[0-9]+M([0-9]+S)?|[0-9]+S))?|T([0-9]+H([0-9]+M([0-9]+S)?)?|[0-9]+M([0-9]+S)?|[0-9]+S)|[0-9]+W)$");
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
            duration_map_pmap = null;
            jm_is_duration_pat = null;
        }
    }

    public Checker get(String name)
    {
        return duration_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return duration_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new duration();
        Main.main("duration", checker, VERSION, args);
    }
}
