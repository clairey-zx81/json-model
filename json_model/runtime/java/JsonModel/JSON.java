package JsonModel;

import java.util.List;
import java.util.Map;
import java.util.Iterator;
import java.io.Reader;

/**
 * Convenient abstraction for JSON libraries such as GSON and Jackson.
 */
public abstract class JSON<T>
{
    public static class Exception extends java.lang.Exception
    {
        public Exception(String s) {
            super(s);
        }
    }

    public abstract T fromJSON(String json) throws Exception;
    public abstract T fromJSON(Reader reader) throws Exception;
    public abstract String toJSON(T o) throws Exception;
    public abstract boolean isNull(T o);
    public abstract boolean isBoolean(T o);
    public abstract boolean asBoolean(T o);
    public abstract boolean isInteger(T o);
    public abstract int asInteger(T o);
    public abstract long asLong(T o);
    public abstract boolean isDouble(T o);
    public abstract double asDouble(T o);

    public boolean isNumber(T o)
    {
        return isInteger(o) || isDouble(o);
    }

    public double asNumber(T o)
    {
        return isDouble(o) ? asDouble(o) : (double) asLong(o);
    }

    public abstract boolean isString(T o);
    public abstract String asString(T o);
    public abstract boolean isArray(T o);
    public abstract int arrayLength(T o);
    public abstract T arrayItem(T o, int index);
    public abstract Iterator<? extends T> arrayIterator(T o);
    public abstract boolean isObject(T o);
    public abstract int objectSize(T o);
    public abstract T objectValue(T o, String prop);
    public abstract Iterator<String> objectIterator(T o);
}
