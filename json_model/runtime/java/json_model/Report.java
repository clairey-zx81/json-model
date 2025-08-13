package json_model;

import java.util.List;
import java.util.LinkedList;

/**
 * Report holds reasons for rejecting a value wrt to a model.
 */
public class Report
{
    /** Report entry */
    class Entry
    {
        /** Generated message, aka rejection motivation */
        String message;

        /** Path in the value to which the message applies */
        Object[] path;

        /** Stupid constructor */
        public Entry(String message, Object[] path)
        {
            this.message = message;
            this.path = path;
        }

        /** Convert to string for display */
        public String toString()
        {
            boolean comma = false;
            StringBuffer sb = new StringBuffer();
            for (Object o: path)
            {
                if (comma)
                    sb.append(", ");
                else
                    comma = true;
                sb.append(o.toString());
            }
            sb.append(": ").append(message);
            return sb.toString();
        }
    }

    /** Current report entries */
    List<Entry> entries = new LinkedList<Entry>();

    /** Add a new entry to the report */
    public void addEntry(String message, Path path)
    {
        this.entries.add(new Entry(message, path.toArray()));
    }

    /** Clear all entries from report */
    public void clearEntries()
    {
        entries.clear();
    }

    /** Display helper */
    public String toString()
    {
        // probably something more clever and functional would be possible
        StringBuffer sb = new StringBuffer();
        boolean sep = false;
        for (Entry e: entries)
        {
            if (sep)
                sb.append("; ");
            else
                sep = true;
            sb.append(e.toString());
        }
        return sb.toString();
    }
}
