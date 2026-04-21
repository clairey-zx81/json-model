
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class sre_19 extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> sre_19_map_pmap;

    public boolean json_model_1(Object val, Path path, Report rep)
    {
        if (! json.isObject(val))
        {
            return false;
        }
        boolean res;
        Iterator<String> prop_loop = json.objectIterator(val);
        while (prop_loop.hasNext())
        {
            String prop = prop_loop.next();
            Object pval = json.objectValue(val, prop);
            res = json.isString(pval);
            if (! res)
            {
                return false;
            }
        }
        return true;
    }


    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            sre_19_map_pmap = new HashMap<String, Checker>();
            sre_19_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
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
            sre_19_map_pmap = null;
        }
    }

    public Checker get(String name)
    {
        return sre_19_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return sre_19_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new sre_19();
        Main.main("sre_19", checker, VERSION, args);
    }
}
