sub CHECK_FUNCTION_NAME($$$)
{
    my ($json, $name, $rep) = @_;
    die "unexpected model name \"$name\"" unless exists $CHECK_FUNCTION_NAME_map{$name};
    my $path = defined $rep ? [] : undef;
    return $CHECK_FUNCTION_NAME_map{$name}($json, $path, $rep);
}
