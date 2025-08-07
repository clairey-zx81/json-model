package json_model;

public abstract class ModelChecker
{
    protected boolean initialized;
    protected Runtime rt;
    protected JSON json;

    /* empty constructor, real initialization is in init() */
    public ModelChecker()
    {
        this.initialized = false;
        this.json = null;
        this.rt = null;
    }

    /* instance initialization */
    public void init(JSON json)
    {
        this.json = json;
        this.rt = new Runtime(json);
        this.initialized = true;
    }

    /* instance cleanup */
    public void free()
    {
        this.initialized = false;
        this.json = null;
        this.rt = null;
    }

    /* check this JSON value */
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

    /* get checker by name */
    public abstract Checker get(String name);
}
