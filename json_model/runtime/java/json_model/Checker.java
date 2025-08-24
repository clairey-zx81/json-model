package json_model;

/**
 * Wrapper class to call a generated check function.
 */
public abstract class Checker
{
    /** Call a check function on a JSON thing */
    public abstract boolean call(Object o, Path p, Report r);

    /** Call a check function without reporting */
    public boolean call(Object o) {
        return call(o, null, null);
    }
}
