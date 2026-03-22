
import json_model.*;
import java.util.Map;
import java.util.Set;
import java.util.HashMap;
import java.util.HashSet;
import java.util.Iterator;
import java.util.regex.Pattern;
import java.util.regex.Matcher;

@SuppressWarnings("unchecked")
public class hosts extends ModelChecker
{
    static public final String VERSION = "2";

    public Map<String, Checker> hosts_map_pmap;
    public Pattern jm_is_host_pat = null;
    public Pattern jm_is_ip4_pat = null;
    public Pattern jm_is_ip6_pat = null;

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
            if (prop.compareTo("host") == 0)
            {
                res = json.isString(pval) && jm_is_host(json.asString(pval), null, null) && json.asString(pval).length() <= 255;
                if (! res)
                {
                    return false;
                }
                continue;
            }
            else if (prop.compareTo("ipv4") == 0)
            {
                res = json.isString(pval) && jm_is_ip4(json.asString(pval), null, null);
                if (! res)
                {
                    return false;
                }
                continue;
            }
            else if (prop.compareTo("ipv6") == 0)
            {
                res = json.isString(pval) && jm_is_ip6(json.asString(pval), null, null);
                if (! res)
                {
                    return false;
                }
                continue;
            }
            return false;
        }
        return true;
    }


    public boolean jm_is_host(String val, Path path, Report rep)
    {
        return jm_is_host_pat.matcher(val).find();
    }

    public boolean jm_is_ip4(String val, Path path, Report rep)
    {
        return jm_is_ip4_pat.matcher(val).find();
    }

    public boolean jm_is_ip6(String val, Path path, Report rep)
    {
        return jm_is_ip6_pat.matcher(val).find();
    }

    public void init(JSON json)
    {
        if (!initialized)
        {
            try {
            hosts_map_pmap = new HashMap<String, Checker>();
            hosts_map_pmap.put("", new Checker() { public boolean call(Object o, Path p, Report r) { return json_model_1(o, p, r);} });
            jm_is_host_pat = Pattern.compile("(?i)^([a-z0-9][-a-z0-9]{0,62})(\\.([a-z0-9][-a-z0-9]{0,62}))*$");
            jm_is_ip4_pat = Pattern.compile("^(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])$");
            jm_is_ip6_pat = Pattern.compile("(?i)^[a-f0-9:]+$");
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
            hosts_map_pmap = null;
            jm_is_host_pat = null;
            jm_is_ip4_pat = null;
            jm_is_ip6_pat = null;
        }
    }

    public Checker get(String name)
    {
        return hosts_map_pmap.get(name);
    }

    public Set<String> models()
    {
        return hosts_map_pmap.keySet();
    }

    static public void main(String[] args) throws Exception
    {
        ModelChecker checker = new hosts();
        Main.main("hosts", checker, VERSION, args);
    }
}
