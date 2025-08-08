package json_model;

import java.util.List;
import java.util.Map;
import java.util.Iterator;
import java.io.Reader;

/**
 * Convenient abstraction for JSON libraries such as GSON and Jackson.
 */
public abstract class JSON<T>
{
    enum JType {
        NULL,
        BOOLEAN,
        INTEGER,
        NUMBER,
        STRING,
        ARRAY,
        OBJECT
    }

    public static class Exception extends java.lang.Exception
    {
        public Exception(String s) {
            super(s);
        }
    }

    public abstract T fromJSON(String json) throws Exception;

    /** no exception version, for generated json */
    public T safeJSON(String json)
    {
        try {
            return fromJSON(json);
        }
        catch (Exception e) {
            throw new Error("unexpected exception while converting from json: " + e);
        }
    }

    public abstract T fromJSON(Reader reader) throws Exception;

    public T strToJSON(String s)
    {
        return (T) s;
    }

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

    public boolean isScalar(T o)
    {
        return isString(o) || isNumber(o) || isBoolean(o) || isNull(o);
    }

    public abstract boolean isArray(T o);
    public abstract int arrayLength(T o);
    public abstract T arrayItem(T o, int index);
    public abstract Iterator<? extends T> arrayIterator(T o);

    public Object[] asArray(T o)
    {
        int length = arrayLength(o);
        Object[] array = new Object[length];
        for (int i = 0; i < length; i++)
            array[i] = arrayItem(o, i);
        return array;
    }

    public abstract boolean isObject(T o);
    public abstract int objectSize(T o);
    public abstract T objectValue(T o, String prop);
    public abstract boolean objectHasProp(T o, String prop);
    public abstract Iterator<String> objectIterator(T o);

    // inefficient default
    public JType type(T o)
    {
        if (isNull(o))
            return JType.NULL;
        if (isBoolean(o))
            return JType.BOOLEAN;
        if (isInteger(o))
            return JType.INTEGER;
        if (isDouble(o))
            return JType.NUMBER;
        if (isString(o))
            return JType.STRING;
        if (isArray(o))
            return JType.ARRAY;
        if (isObject(o))
            return JType.OBJECT;
        throw new Error("unexpected object: " + o);
    }
}
