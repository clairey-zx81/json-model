
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class semver extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> semver_map_pmap;
    public Pattern jm_is_semver_pat = null;

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        return json.isString(val) && jm_is_semver(json.asString(val), null, null);
    }


    public boolean jm_is_semver(String val, Path path, Report rep)
    {
        return jm_is_semver_pat.matcher(val).find();
    }

    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            semver_map_pmap = new HashMap<String, Checker>();
            semver_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
            jm_is_semver_pat = Pattern.compile("^([0-9]|[1-9][0-9]+)\\.([0-9]|[1-9][0-9]+)\\.([0-9]|[1-9][0-9]+)(-(([0-9]|[1-9][0-9]+)|[-0-9a-zA-Z]*[-a-zA-Z][-0-9a-zA-Z]*)(\\.(([0-9]|[1-9][0-9]+)|[-0-9a-zA-Z]*[-a-zA-Z][-0-9a-zA-Z]*))*)?(\\+(([0-9]|[1-9][0-9]+)|[-0-9a-zA-Z]*[-a-zA-Z][-0-9a-zA-Z]*)(\\.(([0-9]|[1-9][0-9]+)|[-0-9a-zA-Z]*[-a-zA-Z][-0-9a-zA-Z]*))*)?$");
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
            semver_map_pmap = null;
            jm_is_semver_pat = null;
        }
    }

    public Checker get(String name)
    {
        return semver_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return semver_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new semver();
        Main.main("semver", checker, VERSION, args);
    }
}
