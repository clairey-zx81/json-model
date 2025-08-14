package json_model;

import java.util.List;
import java.util.Map;
import java.util.Iterator;
import java.io.Reader;

/**
 * Convenient abstraction for JSON libraries such as GSON and Jackson.
 *
 * This interface allows to run a compiled checker with different JSON libraries.
 */
public abstract class JSON<T>
{

    /** All JSON types */
    static public final int NULL = 1;
    static public final int BOOLEAN = 2;
    static public final int INTEGER = 3;
    static public final int NUMBER = 4;
    static public final int STRING = 5;
    static public final int ARRAY = 6;
    static public final int OBJECT = 7;

    /** Internal exception for JSON errors */
    public static class Exception extends java.lang.Exception
    {
        public Exception(String s) {
            super(s);
        }
    }

    /** Convert string to JSON thing */
    public abstract T fromJSON(String json) throws Exception;

    /** No exception version, for generated json */
    public T safeJSON(String json)
    {
        try {
            return fromJSON(json);
        }
        catch (Exception e) {
            throw new Error("unexpected exception while converting from json: " + e);
        }
    }

    /** Convert text flow to JSON thing */
    public abstract T fromJSON(Reader reader) throws Exception;

    /** Generate JSON string from Java string */
    public T strToJSON(String s)
    {
        return (T) s;
    }

    /** Convert JSON thing to a serialized JSON string */
    public abstract String toJSON(T o) throws Exception;

    /** Tell whether JSON thing is "null" */
    public abstract boolean isNull(T o);

    /** Tell whether JSON thing is a "boolean" */
    public abstract boolean isBoolean(T o);

    /** Extract boolean value from JSON thing */
    public abstract boolean asBoolean(T o);

    /** Tell whether JSON thing is an "integer" */
    public abstract boolean isInteger(T o);

    /** Extract int value from JSON thing */
    public abstract int asInteger(T o);

    /** Extract long value from JSON thing */
    public abstract long asLong(T o);

    /** Tell whether JSON thing is a "double" */
    public abstract boolean isDouble(T o);

    /** Extract double value from JSON thing */
    public abstract double asDouble(T o);

    /** Tell whether JSON thing is a "number" */
    public boolean isNumber(T o)
    {
        return isInteger(o) || isDouble(o);
    }

    /** Extract number value from JSON thing */
    public double asNumber(T o)
    {
        return isDouble(o) ? asDouble(o) : (double) asLong(o);
    }

    /** Tell whether JSON thing is a "string" */
    public abstract boolean isString(T o);

    /** Extract string value from JSON thing */
    public abstract String asString(T o);

    /** Tell whether JSON thing is a scalar */
    public boolean isScalar(T o)
    {
        return isString(o) || isNumber(o) || isBoolean(o) || isNull(o);
    }

    /** Tell whether JSON thing is an array */
    public abstract boolean isArray(T o);

    /** Get array length */
    public abstract int arrayLength(T o);

    /** Get array item at index */
    public abstract T arrayItem(T o, int index);

    /** Iterate over array items */
    public abstract Iterator<? extends T> arrayIterator(T o);

    /** Extract JSON array as a Java array */
    public Object[] asArray(T o)
    {
        int length = arrayLength(o);
        Object[] array = new Object[length];
        for (int i = 0; i < length; i++)
            array[i] = arrayItem(o, i);
        return array;
    }

    /** Tell whether JSON thing is an object */
    public abstract boolean isObject(T o);

    /** Get object size (aka number of properties) */
    public abstract int objectSize(T o);

    /** Get value for an object property */
    public abstract T objectValue(T o, String prop);

    /** Tell whether JSON thing has a property */
    public abstract boolean objectHasProp(T o, String prop);

    /** Iterate over a JSON object properties */
    public abstract Iterator<String> objectIterator(T o);

    /** Get JSON thing type */
    public int type(T o)
    {
        if (isNull(o))
            return NULL;
        if (isBoolean(o))
            return BOOLEAN;
        if (isInteger(o))
            return INTEGER;
        if (isDouble(o))
            return NUMBER;
        if (isString(o))
            return STRING;
        if (isArray(o))
            return ARRAY;
        if (isObject(o))
            return OBJECT;
        throw new Error("unexpected object: " + o);
    }
}
