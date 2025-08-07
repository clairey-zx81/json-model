package json_model;

// simplistic linked list
public class Path
{
    protected Path previous = null;
    protected int index = -1;
    protected String property = null;

    public Path(int index, Path previous)
    {
        this.previous = previous;
        this.index = index;
        // assert index >= 0
    }

    public Path(String property, Path previous)
    {
        this.previous = previous;
        this.property = property;
        // assert property != null
    }

    public Path() {}

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
}
