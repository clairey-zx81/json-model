
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class luhn extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> luhn_map_pmap;
    public Pattern jm_is_card_pat = null;

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        return json.isString(val) && jm_is_card(json.asString(val), null, null);
    }


    public boolean jm_is_card(String val, Path path, Report rep)
    {
        return jm_is_card_pat.matcher(val).find();
    }

    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            luhn_map_pmap = new HashMap<String, Checker>();
            luhn_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
            jm_is_card_pat = Pattern.compile("^[0-9]{16}$");
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
            luhn_map_pmap = null;
            jm_is_card_pat = null;
        }
    }

    public Checker get(String name)
    {
        return luhn_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return luhn_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new luhn();
        Main.main("luhn", checker, VERSION, args);
    }
}
