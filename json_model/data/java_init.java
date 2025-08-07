public void init(JSON json)
{
    if (!initialized)
    {
        try {
CODE_BLOCK
            super.init(json);
        }
        catch (Exception e) {
            throw new Error("cannot initialized model checker: " + e);
        }
    }
}
