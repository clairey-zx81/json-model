
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class sre_10 extends ModelChecker
{
    static public final String VERSION = "2";

    public Pattern _jm_re_0_pat = null;
    public Map<String, Checker> sre_10_map_pmap;

    public boolean _jm_re_0(String val, Path path, Report rep)
    {
        return _jm_re_0_pat.matcher(val).find();
    }

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        return json.isString(val) && _jm_re_0(json.asString(val), null, null);
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            _jm_re_0_pat = Pattern.compile("^[ABCDEF0123456789]+$");
            sre_10_map_pmap = new HashMap<String, Checker>();
            sre_10_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            sre_10_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return sre_10_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return sre_10_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new sre_10();
        Main.main("sre_10", checker, VERSION, args);
    }
}
