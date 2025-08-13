package json_model;

import java.util.List;
import java.util.Map;
import java.util.Iterator;
import java.io.Reader;
import java.lang.reflect.Type;
import com.google.gson.reflect.TypeToken;
import com.google.gson.GsonBuilder;
import com.google.gson.ToNumberPolicy;
import com.google.gson.Strictness;
import com.google.gson.Gson;

/**
 * GSON checker abstraction.
 *
 * @see <a href="https://github.com/google/gson">GSON</a>
 */
public class GSON extends JSON<Object>
{
    private static Type type = new TypeToken<Object>() {}.getType();  // deep voodoo

    private static final Gson gson = new GsonBuilder()
        .setObjectToNumberStrategy(ToNumberPolicy.LONG_OR_DOUBLE)
        .setStrictness(Strictness.STRICT)
        .create();

    public Object fromJSON(String json) throws JSON.Exception
    {
        return gson.fromJson(json, type);
    }

    public Object fromJSON(Reader reader) throws JSON.Exception
    {
        return gson.fromJson(reader, type);
    }

    public String toJSON(Object o) throws JSON.Exception
    {
        return gson.toJson(o);
    }

    public boolean isNull(Object o)
    {
        return o == null;        
    }

    public boolean isBoolean(Object o)
    {
        return o instanceof Boolean;
    }

    public boolean asBoolean(Object o)
    {
        return (boolean) o;
    }

    public boolean isInteger(Object o)
    {
        return o instanceof Integer || o instanceof Long;
    }

    public int asInteger(Object o)
    {
        return (int) o;
    }

    public long asLong(Object o)
    {
        return (long) o;
    }

    public boolean isDouble(Object o)
    {
        return o instanceof Double;
    }

    public double asDouble(Object o)
    {
        return (double) o;
    }

    public boolean isNumber(Object o)
    {
        return isInteger(o) || isDouble(o);
    }

    public double asNumber(Object o)
    {
        return isDouble(o) ? asDouble(o) : (double) asLong(o);
    }

    public boolean isString(Object o)
    {
        return o instanceof String;
    }

    public String asString(Object o)
    {
        return (String) o;
    }

    public boolean isArray(Object o)
    {
        return o instanceof List; 
    }

    public int arrayLength(Object o)
    {
        return ((List) o).size();
    }

    public Object arrayItem(Object o, int index)
    {
        return ((List) o).get(index);
    }

    public Iterator<? extends Object> arrayIterator(Object o)
    {
        return ((List) o).iterator();
    }

    public boolean isObject(Object o)
    {
        return o instanceof Map;
    }

    public int objectSize(Object o)
    {
        return ((Map<String, Object>) o).size();
    }

    public Object objectValue(Object o, String prop)
    {
        return ((Map<String, Object>) o).get(prop);
    }

    public boolean objectHasProp(Object o, String prop)
    {
        return ((Map<String, Object>) o).containsKey(prop);
    }

    public Iterator<String> objectIterator(Object o)
    {
        return ((Map<String, Object>) o).keySet().iterator();
    }
}
