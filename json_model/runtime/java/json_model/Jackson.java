package json_model;

import java.util.List;
import java.util.Map;
import java.util.Iterator;
import java.io.Reader;
import java.io.IOException;

import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.JsonNode;
import com.fasterxml.jackson.databind.node.TextNode;

/**
 * Jackson JSON abstraction.
 *
 * @see <a href="https://github.com/FasterXML/jackson">Jackson</a>
 */
public class Jackson extends JSON<Object>
{
    private static ObjectMapper mapper = new ObjectMapper();

    public Object fromJSON(String json) throws JSON.Exception
    {
        try {
            return mapper.readTree(json);
        }
        catch (JsonProcessingException e) {
            throw new JSON.Exception("jackson error: " + e);
        }
    }

    public Object fromJSON(Reader reader) throws JSON.Exception
    {
        try {
            return mapper.readTree(reader);
        }
        catch (JsonProcessingException e) {
            throw new JSON.Exception("jackson error: " + e);
        }
        catch (IOException e) {
            throw new JSON.Exception("io error: " + e);
        }
    }

    public Object strToJSON(String s)
    {
        return new TextNode(s);
    }

    public String toJSON(Object o) throws JSON.Exception
    {
        try {
            return mapper.writeValueAsString((JsonNode) o);
        }
        catch (JsonProcessingException e) {
            throw new JSON.Exception("jackson error: " + e);
        }
    }

    public boolean isNull(Object o)
    {
        return ((JsonNode) o).isNull();
    }

    public boolean isBoolean(Object o)
    {
        return ((JsonNode) o).isBoolean(); 
    }

    public boolean asBoolean(Object o)
    {
        return ((JsonNode) o).asBoolean();
    }

    public boolean isInteger(Object o)
    {
        JsonNode n = (JsonNode) o;
        return n.isLong() || n.isInt();
    }

    public int asInteger(Object o)
    {
        return ((JsonNode) o).asInt();
    }

    public long asLong(Object o)
    {
        return ((JsonNode) o).asLong();
    }

    public boolean isDouble(Object o)
    {
        return ((JsonNode) o).isDouble();
    }

    public double asDouble(Object o)
    {
        return ((JsonNode) o).asDouble();
    }

    public boolean isNumber(Object o)
    {
        return ((JsonNode) o).isNumber();
    }

    public double asNumber(Object o)
    {
        return ((JsonNode) o).doubleValue();
    }

    public boolean isString(Object o)
    {
        return ((JsonNode) o).isTextual();
    }

    public String asString(Object o)
    {
        return ((JsonNode) o).asText();
    }

    public boolean isArray(Object o)
    {
        return ((JsonNode) o).isArray();
    }

    public int arrayLength(Object o)
    {
        return ((JsonNode) o).size();
    }

    public Object arrayItem(Object o, int index)
    {
        return ((JsonNode) o).get(index);
    }

    public Iterator<? extends Object> arrayIterator(Object o)
    {
        return ((JsonNode) o).iterator();
    }

    public boolean isObject(Object o)
    {
        return ((JsonNode) o).isObject();
    }

    public int objectSize(Object o)
    {
        return ((JsonNode) o).size();
    }

    public Object objectValue(Object o, String prop)
    {
        return ((JsonNode) o).get(prop);
    }

    public boolean objectHasProp(Object o, String prop)
    {
        return ((JsonNode) o).get(prop) != null;
    }

    public Iterator<String> objectIterator(Object o)
    {
        return ((JsonNode) o).propertyStream().map(entry -> entry.getKey()).iterator();
    }
}
