package json_model;

import java.util.List;
import java.util.Map;
import java.util.Iterator;
import java.io.Reader;
import java.io.StringReader;
import java.io.StringWriter;
import java.io.IOException;

// WTF?!
// import javax.json.*;
import jakarta.json.*;

/**
 * JSONP JSON abstraction.
 *
 * Although it is a standard, this abstraction seems to have chosen to implement
 * JSON typing as is (if it can be called a type system): integer and numbers are merged,
 * true and false are two distinct types.
 *
 * At least one bug found with the _joy_ implementation tested: 100E99 != 10E100.
 *
 * @see <a href="https://jakarta.ee/specifications/jsonp/2.1/apidocs/">JSONP</a>
 */
public class JSONP extends JSON<Object>
{
    public Object fromJSON(String json) throws JSON.Exception
    {
        return Json.createReader(new StringReader(json)).readValue();
    }

    public Object fromJSON(Reader reader) throws JSON.Exception
    {
        return Json.createReader(reader).readValue();
    }

    public Object strToJSON(String s)
    {
        return Json.createValue(s);
    }

    protected JsonValue.ValueType _type(Object o)
    {
        return ((JsonValue) o).getValueType();
    }

    public String toJSON(Object o) throws JSON.Exception
    {
        StringWriter sw = new StringWriter();
        Json.createWriter(sw).write((JsonValue) o);
        return sw.toString();
    }

    public boolean isNull(Object o)
    {
        return _type(o) == JsonValue.ValueType.NULL;
    }

    public boolean isBoolean(Object o)
    {
        JsonValue.ValueType t = _type(o);
        return t == JsonValue.ValueType.TRUE || t == JsonValue.ValueType.FALSE;
    }

    public boolean asBoolean(Object o)
    {
        return _type(o) == JsonValue.ValueType.TRUE;
    }

    public boolean isInteger(Object o)
    {
        return _type(o) == JsonValue.ValueType.NUMBER && ((JsonNumber) o).isIntegral();
    }

    public int asInteger(Object o)
    {
        return ((JsonNumber) o).intValue();
    }

    public long asLong(Object o)
    {
        return ((JsonNumber) o).longValue();
    }

    public boolean isDouble(Object o)
    {
        return _type(o) == JsonValue.ValueType.NUMBER;
    }

    public double asDouble(Object o)
    {
        return ((JsonNumber) o).doubleValue();
    }

    public boolean isNumber(Object o)
    {
        return _type(o) == JsonValue.ValueType.NUMBER;
    }

    public double asNumber(Object o)
    {
        return ((JsonNumber) o).doubleValue();
    }

    public boolean isString(Object o)
    {
        return _type(o) == JsonValue.ValueType.STRING;
    }

    public String asString(Object o)
    {
        return ((JsonString) o).getString();
    }

    public boolean isArray(Object o)
    {
        return _type(o) == JsonValue.ValueType.ARRAY;
    }

    public int arrayLength(Object o)
    {
        return ((JsonValue) o).asJsonArray().size();
    }

    public Object arrayItem(Object o, int index)
    {
        return ((JsonValue) o).asJsonArray().get(index);
    }

    public Iterator<? extends Object> arrayIterator(Object o)
    {
        return ((JsonValue) o).asJsonArray().iterator();
    }

    public boolean isObject(Object o)
    {
        return _type(o) == JsonValue.ValueType.OBJECT;
    }

    public int objectSize(Object o)
    {
        return ((JsonValue) o).asJsonObject().size();
    }

    public Object objectValue(Object o, String prop)
    {
        return ((JsonValue) o).asJsonObject().get(prop);
    }

    public boolean objectHasProp(Object o, String prop)
    {
        return ((JsonValue) o).asJsonObject().containsKey(prop);
    }

    public Iterator<String> objectIterator(Object o)
    {
        return ((JsonValue) o).asJsonObject().keySet().iterator();
    }

    public int type(Object o)
    {
        switch (_type(o)) {
            case JsonValue.ValueType.NULL:
                return JSON.NULL;
            case JsonValue.ValueType.TRUE:
            case JsonValue.ValueType.FALSE:
                return JSON.BOOLEAN;
            case JsonValue.ValueType.NUMBER:
                return ((JsonNumber) o).isIntegral() ? JSON.INTEGER : JSON.NUMBER;
            case JsonValue.ValueType.STRING:
                return JSON.STRING;
            case JsonValue.ValueType.ARRAY:
                return JSON.ARRAY;
            case JsonValue.ValueType.OBJECT:
                return JSON.OBJECT;
            default:
                throw new Error("unexpected JsonValue");
        }
    }
}
