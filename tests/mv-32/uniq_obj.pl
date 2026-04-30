#! /usr/bin/perl
use strict;
use warnings;
no warnings "uninitialized";
use re::engine::RE2;
use JSON::JsonModel;
use constant JMC_VERSION => '2';


sub json_model_2($$$);
sub json_model_1($$$);
my %check_model_map;

sub json_model_2($$$)
{
    my ($val, $path, $rep) = @_;
    if (! jm_is_object($val))
    {
        return 0;
    }
    if (jm_obj_size($val) != 2)
    {
        return 0;
    }
    my $pval;
    if (! exists $$val{'x'})
    {
        return 0;
    }
    $pval = $$val{'x'};
    my $res = jm_is_string($pval);
    if (! $res)
    {
        return 0;
    }
    if (! exists $$val{'y'})
    {
        return 0;
    }
    $pval = $$val{'y'};
    return jm_is_string($pval);
}

sub json_model_1($$$)
{
    my ($val, $path, $rep) = @_;
    my $res = jm_is_array($val);
    if ($res)
    {
        for my $arr_0_idx (0 .. $#$val)
        {
            my $arr_0_item = $$val[$arr_0_idx];
            $res = json_model_2($arr_0_item, undef, undef);
            if (! $res)
            {
                last;
            }
        }
    }
    if ($res)
    {
        $res = jm_is_unique_array($val, undef, undef);
    }
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
            'XY' => \&json_model_2,
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
