package json_model;

/** Simplistic JSON path representation as a linked list */
public class Path
{
    /** Previous path segment */
    protected Path previous = null;

    /** Array index, or -1 if not an array */
    protected int index = -1;

    /** Object property, or null if not an object */
    protected String property = null;

    /** Constructor for an array */
    public Path(int index, Path previous)
    {
        this.previous = previous;
        this.index = index;
        // assert index >= 0
    }

    /** Constructor for an object */
    public Path(String property, Path previous)
    {
        this.previous = previous;
        this.property = property;
        // assert property != null
    }

    /** Empty constructor */
    public Path() {}

    /** Export as an array */
    public Object[] toArray()
    {
        int size = 0;
        for (Path p = this; p != null; p = p.previous)
            size++;
        Object[] array = new Object[size-1];
        int index = size - 2;
        for (Path p = this; index >= 0; p = p.previous)
            array[index--] = p.property != null ? p.property : (Integer) p.index;
        return array;
    }

    /** Cleanup for reuse */
    public void reset()
    {
        this.previous = null;
        this.property = null;
        this.index = -1;
    }
}
