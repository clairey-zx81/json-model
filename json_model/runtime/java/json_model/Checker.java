package json_model;

/**
 * Wrapper class to call an generated check function.
 */
public interface Checker
{                                                                                 
    /** Call a check function on a JSON thing */
    public boolean call(Object o, Path p, Report r);                                                
}                                                                                                   
