package json_model;

import java.util.Set;

/**
 * Root class for generated JSON model checkers.
 */
public abstract class ModelChecker
{
    /** Whether the model is initialized */
    protected boolean initialized;

    /** JSON Model actual runtime */
    protected Runtime rt;

    /** JSON library interface */
    protected JSON json;

    /** Empty constructor, real initialization is in init() */
    public ModelChecker()
    {
        this.initialized = false;
        this.json = null;
        this.rt = null;
    }

    /** Instance initialization */
    public void init(JSON json)
    {
        this.json = json;
        this.rt = new Runtime(json);
        this.initialized = true;
    }

    /** Instance cleanup */
    public void free()
    {
        this.initialized = false;
        this.json = null;
        this.rt = null;
    }

    /** Check this JSON value */
    public boolean check(Object value, String name, Report rep) throws JSON.Exception
    {
        if (!initialized)
            throw new JSON.Exception("ModelChecker is not initialized");
        Checker checker = get(name);
        if (checker == null)
            throw new JSON.Exception("unexpected model name: " + name);
        Path path = rep != null ? new Path() : null;
        return checker.call(value, path, rep);
    }

    /** Get checker by name */
    public abstract Checker get(String name);

    /** Get available models */
    public abstract Set<String> models();
}
