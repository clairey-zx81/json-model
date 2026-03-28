#! /usr/bin/perl
use strict;
use warnings;
no warnings "uninitialized";
use re::engine::RE2;
use JSON::JsonModel;
use constant JMC_VERSION => '2';


sub _jm_obj_0($$$);
sub _jm_obj_1($$$);
sub _jm_obj_2($$$);
sub _jm_obj_3($$$);
my %_jm_map_0;
sub json_model_1($$$);
my %check_model_map;

sub _jm_obj_0($$$)
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
    if (! exists $$val{'d'})
    {
        return 0;
    }
    $pval = $$val{'d'};
    my $res = jm_is_integer($pval) && $pval == 0;
    if (! $res)
    {
        return 0;
    }
    if (! exists $$val{'a'})
    {
        return 0;
    }
    $pval = $$val{'a'};
    return jm_is_string($pval);
}

sub _jm_obj_1($$$)
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
    if (! exists $$val{'d'})
    {
        return 0;
    }
    $pval = $$val{'d'};
    my $res = jm_is_integer($pval) && $pval == 1;
    if (! $res)
    {
        return 0;
    }
    if (! exists $$val{'a'})
    {
        return 0;
    }
    $pval = $$val{'a'};
    return jm_is_integer($pval) && $pval >= 0;
}

sub _jm_obj_2($$$)
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
    if (! exists $$val{'d'})
    {
        return 0;
    }
    $pval = $$val{'d'};
    my $res = jm_is_integer($pval) && $pval == 2;
    if (! $res)
    {
        return 0;
    }
    if (! exists $$val{'a'})
    {
        return 0;
    }
    $pval = $$val{'a'};
    return !defined($pval);
}

sub _jm_obj_3($$$)
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
    if (! exists $$val{'d'})
    {
        return 0;
    }
    $pval = $$val{'d'};
    my $res = jm_is_integer($pval) && $pval == 3;
    if (! $res)
    {
        return 0;
    }
    if (! exists $$val{'a'})
    {
        return 0;
    }
    $pval = $$val{'a'};
    return jm_is_boolean($pval);
}


sub json_model_1($$$)
{
    my ($val, $path, $rep) = @_;
    my $res = jm_is_object($val);
    if ($res)
    {
        my $tag_0;
        if (defined($tag_0 = $$val{'d'}))
        {
            my $fun_0 = $_jm_map_0{$tag_0};
            $res = defined($fun_0) && &$fun_0($val, undef, undef);
        }
        else
        {
            $res = 0;
        }
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
        %_jm_map_0 = (
            0 => \&_jm_obj_0,
            1 => \&_jm_obj_1,
            2 => \&_jm_obj_2,
            3 => \&_jm_obj_3,
        );
        %check_model_map = (
            '' => \&json_model_1,
        );
    }
}

sub check_model_free()
{
    if ($initialized)
    {
        $initialized = 0;
        %_jm_map_0 = ();
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
