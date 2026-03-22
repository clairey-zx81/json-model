
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class email_address extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> email_address_map_pmap;
    public Pattern jm_is_email_pat = null;

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        return json.isString(val) && jm_is_email(json.asString(val), null, null);
    }


    public boolean jm_is_email(String val, Path path, Report rep)
    {
        return jm_is_email_pat.matcher(val).find();
    }

    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            email_address_map_pmap = new HashMap<String, Checker>();
            email_address_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
            jm_is_email_pat = Pattern.compile("(?i)^([-+!#$%&'`*/=?^{}|~_a-z0-9]+)(\\.([-+!#$%&'`*/=?^{}|~_a-z0-9]+))*@([a-z0-9][-a-z0-9]{0,62})(\\.([a-z0-9][-a-z0-9]{0,62}))*$");
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
            email_address_map_pmap = null;
            jm_is_email_pat = null;
        }
    }

    public Checker get(String name)
    {
        return email_address_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return email_address_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new email_address();
        Main.main("email_address", checker, VERSION, args);
    }
}
