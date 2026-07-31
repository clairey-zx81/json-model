#! /usr/bin/perl
use utf8;
use strict;
use warnings;
no warnings "uninitialized";
use re::engine::RE2;
use JSON::JsonModel;
use constant JMC_VERSION => "2";


sub json_model_2($$$);
sub _jm_f_0($$$);
my %json_model_1_map;
sub json_model_1($$$);
my %check_model_map;

sub json_model_2($$$)
{
    my ($val, $path, $rep) = @_;
    my $res = jm_is_array($val);
    if ($res)
    {
        for my $arr_0_idx (0 .. $#$val)
        {
            my $arr_0_item = $$val[$arr_0_idx];
            $res = jm_is_integer($arr_0_item) && $arr_0_item >= 0;
            last unless $res;
        }
    }
    $res = jm_is_unique_array($val, undef, undef) if $res;
    return $res;
}

sub _jm_f_0($$$)
{
    my ($val, $path, $rep) = @_;
    return jm_is_boolean($val);
}


sub json_model_1($$$)
{
    my ($val, $path, $rep) = @_;
    return 0 unless jm_is_object($val);
    my $res;
    my $pfun;
    scalar keys %$val;
    while (my ($prop, $pval) = each %$val)
    {
        if (($pfun = $json_model_1_map{$prop}))
        {
            return 0 if defined($pfun) && ! &$pfun($pval, undef, undef);
            next;
        }
        if (jm_starts_with($prop, "#"))
        {
            $res = jm_is_string($pval);
            return 0 unless $res;
        }
        else
        {
            return 0;
        }
    }
    return 1;
}


# initialization of global variables

our $initialized = 0;

sub check_model_init()
{
    if (!$initialized)
    {
        $initialized = 1;
        %json_model_1_map = (
            "c" => \&json_model_2,
            "dynpy" => \&json_model_2,
            "java" => \&json_model_2,
            "js" => \&json_model_2,
            "pl" => \&json_model_2,
            "py" => \&json_model_2,
            "schema" => \&json_model_2,
            "sql" => \&json_model_2,
            "ts" => \&_jm_f_0,
        );
        %check_model_map = (
            "" => \&json_model_1,
            "ErrorIndex" => \&json_model_2,
        );
    }
}

sub check_model_free()
{
    if ($initialized)
    {
        $initialized = 0;
        %json_model_1_map = ();
        %check_model_map = ();
    }
}

sub check_model_mapper($)
{
    my ($name) = @_;
    die "unexpected model name \"$name\"" unless exists $check_model_map{$name};
    return $check_model_map{$name};
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
