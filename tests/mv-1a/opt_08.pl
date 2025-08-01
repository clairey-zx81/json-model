#! /usr/bin/perl
#
# Generated by JSON Model Compiler version 2.0b1
# see https://github.com/clairey-zx81/json-model
#
use strict;
use warnings;
use re::engine::RE2;
use JsonModel;
use constant JMC_VERSION => '2';


my %check_model_map;

# check $one (.'$one')
sub json_model_2($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$one'
    $res = jm_is_integer($val) && $val == 1;
    return $res;
}

# check $ (.)
sub json_model_1($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .
    $res = jm_is_integer($val) && $val == 1;
    return $res;
}


# initialization of global variables

our $initialized = 0;

sub check_model_init()
{
    if (!$initialized)
    {
        $initialized = 1;
        %check_model_map = (
            '' => \&json_model_1,
            'one' => \&json_model_2,
        );
    }
}

sub check_model_free()
{
    if ($initialized)
    {
        $initialized = 0;
        %check_model_map = ();
    }
}

sub check_model($$$)
{
    my ($json, $name, $rep) = @_;
    die "unexpected model name \"$name\"" unless exists $check_model_map{$name};
    my $path = defined $rep ? [] : undef;
    return $check_model_map{$name}($json, $path, $rep);
}

#
# SCRIPT EXECUTION
#
check_model_init();
jm_main(\&check_model, \%check_model_map, JMC_VERSION);
check_model_free();
