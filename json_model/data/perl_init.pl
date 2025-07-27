# initialization of global variables

our $initialized = 0;

sub CHECK_FUNCTION_NAME_init()
{
    if (!$initialized)
    {
        $initialized = 1;
CODE_BLOCK
    }
}
