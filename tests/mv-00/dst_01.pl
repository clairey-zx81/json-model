#! /usr/bin/perl
use strict;
use warnings;
no warnings "uninitialized";
use JSON::JsonModel;
use constant JMC_VERSION => '2';


sub _jm_obj_0($$$);
sub _jm_obj_1($$$);
sub _jm_obj_2($$$);
sub _jm_obj_3($$$);
sub _jm_obj_4($$$);
sub _jm_obj_5($$$);
sub json_model_1($$$);
my %check_model_map;

sub _jm_obj_0($$$)
{
    my ($val, $path, $rep) = @_;
    if (jm_obj_size($val) != 3)
    {
        return 0;
    }
    my $pval;
    if (! exists $$val{'a'})
    {
        return 0;
    }
    $pval = $$val{'a'};
    my $res = jm_is_integer($pval) && $pval >= 0;
    if (! $res)
    {
        return 0;
    }
    if (! exists $$val{'c'})
    {
        return 0;
    }
    $pval = $$val{'c'};
    $res = jm_is_integer($pval) && $pval >= 1;
    if (! $res)
    {
        return 0;
    }
    if (! exists $$val{'f'})
    {
        return 0;
    }
    $pval = $$val{'f'};
    return jm_is_string($pval);
}

sub _jm_obj_1($$$)
{
    my ($val, $path, $rep) = @_;
    if (jm_obj_size($val) != 3)
    {
        return 0;
    }
    my $pval;
    if (! exists $$val{'a'})
    {
        return 0;
    }
    $pval = $$val{'a'};
    my $res = jm_is_integer($pval) && $pval >= 0;
    if (! $res)
    {
        return 0;
    }
    if (! exists $$val{'c'})
    {
        return 0;
    }
    $pval = $$val{'c'};
    $res = jm_is_integer($pval) && $pval >= 1;
    if (! $res)
    {
        return 0;
    }
    if (! exists $$val{'e'})
    {
        return 0;
    }
    $pval = $$val{'e'};
    return jm_is_string($pval);
}

sub _jm_obj_2($$$)
{
    my ($val, $path, $rep) = @_;
    if (jm_obj_size($val) != 3)
    {
        return 0;
    }
    my $pval;
    if (! exists $$val{'a'})
    {
        return 0;
    }
    $pval = $$val{'a'};
    my $res = jm_is_integer($pval) && $pval >= 0;
    if (! $res)
    {
        return 0;
    }
    if (! exists $$val{'c'})
    {
        return 0;
    }
    $pval = $$val{'c'};
    $res = jm_is_integer($pval) && $pval >= 1;
    if (! $res)
    {
        return 0;
    }
    if (! exists $$val{'d'})
    {
        return 0;
    }
    $pval = $$val{'d'};
    return jm_is_string($pval);
}

sub _jm_obj_3($$$)
{
    my ($val, $path, $rep) = @_;
    if (jm_obj_size($val) != 3)
    {
        return 0;
    }
    my $pval;
    if (! exists $$val{'a'})
    {
        return 0;
    }
    $pval = $$val{'a'};
    my $res = jm_is_integer($pval) && $pval >= 0;
    if (! $res)
    {
        return 0;
    }
    if (! exists $$val{'b'})
    {
        return 0;
    }
    $pval = $$val{'b'};
    $res = jm_is_integer($pval) && $pval >= 1;
    if (! $res)
    {
        return 0;
    }
    if (! exists $$val{'f'})
    {
        return 0;
    }
    $pval = $$val{'f'};
    return jm_is_string($pval);
}

sub _jm_obj_4($$$)
{
    my ($val, $path, $rep) = @_;
    if (jm_obj_size($val) != 3)
    {
        return 0;
    }
    my $pval;
    if (! exists $$val{'a'})
    {
        return 0;
    }
    $pval = $$val{'a'};
    my $res = jm_is_integer($pval) && $pval >= 0;
    if (! $res)
    {
        return 0;
    }
    if (! exists $$val{'b'})
    {
        return 0;
    }
    $pval = $$val{'b'};
    $res = jm_is_integer($pval) && $pval >= 1;
    if (! $res)
    {
        return 0;
    }
    if (! exists $$val{'e'})
    {
        return 0;
    }
    $pval = $$val{'e'};
    return jm_is_string($pval);
}

sub _jm_obj_5($$$)
{
    my ($val, $path, $rep) = @_;
    if (jm_obj_size($val) != 3)
    {
        return 0;
    }
    my $pval;
    if (! exists $$val{'a'})
    {
        return 0;
    }
    $pval = $$val{'a'};
    my $res = jm_is_integer($pval) && $pval >= 0;
    if (! $res)
    {
        return 0;
    }
    if (! exists $$val{'b'})
    {
        return 0;
    }
    $pval = $$val{'b'};
    $res = jm_is_integer($pval) && $pval >= 1;
    if (! $res)
    {
        return 0;
    }
    if (! exists $$val{'d'})
    {
        return 0;
    }
    $pval = $$val{'d'};
    return jm_is_string($pval);
}

sub json_model_1($$$)
{
    my ($val, $path, $rep) = @_;
    return jm_is_object($val) && (exists $$val{'d'} && _jm_obj_5($val, undef, undef) || exists $$val{'e'} && _jm_obj_4($val, undef, undef) || exists $$val{'f'} && _jm_obj_3($val, undef, undef) || exists $$val{'d'} && _jm_obj_2($val, undef, undef) || exists $$val{'e'} && _jm_obj_1($val, undef, undef) || exists $$val{'f'} && _jm_obj_0($val, undef, undef));
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
