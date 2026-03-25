
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class noreg extends ModelChecker
{
    static public final String VERSION = "2";

    public Pattern _jm_re_0_pat = null;
    public Map<String, Checker> noreg_map_pmap;

    public boolean _jm_re_0(String val, Path path, Report rep)
    {
        return _jm_re_0_pat.matcher(val).find();
    }

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        boolean res = json.isString(val);
        if (res)
        {
            boolean is_0 = _jm_re_0(json.asString(val), null, null);
            res = ! is_0;
        }
        return res;
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            _jm_re_0_pat = Pattern.compile("^[0-9]");
            noreg_map_pmap = new HashMap<String, Checker>();
            noreg_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            _jm_re_0_pat = null;
            noreg_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return noreg_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return noreg_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new noreg();
        Main.main("noreg", checker, VERSION, args);
    }
}
