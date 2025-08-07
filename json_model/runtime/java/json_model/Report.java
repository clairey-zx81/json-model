package json_model;

import java.util.List;
import java.util.LinkedList;

public class Report
{
    class Entry
    {
        String message;
        Object[] path;

        public Entry(String message, Object[] path)
        {
            this.message = message;
            this.path = path;
        }

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

    List<Entry> entries = new LinkedList<Entry>();

    public void addEntry(String message, Path path)
    {
        this.entries.add(new Entry(message, path.toArray()));
    }

    public void clearEntries()
    {
        entries.clear();
    }

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
