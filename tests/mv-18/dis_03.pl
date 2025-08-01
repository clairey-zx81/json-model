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


my %_jm_map_0;
my %check_model_map;

# object .'|'.0
sub _jm_obj_0($$$)
{
    my ($val, $path, $rep) = @_;
    if (! jm_is_object($val))
    {
        return 0;
    }
    my $res;
    my $must_count = 0;
    scalar keys %$val;
    while (my ($prop, $pval) = each %$val)
    {
        if ($prop eq 'discriminator')
        {
            # handle must discriminator property
            $must_count++;
            # .'|'.0.discriminator
            $res = jm_is_boolean($pval) && $pval == 1;
            if (! $res)
            {
                return 0;
            }
        }
        elsif ($prop eq 'x')
        {
            # handle must x property
            $must_count++;
            # .'|'.0.x
            $res = jm_is_string($pval);
            if (! $res)
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    if ($must_count != 2)
    {
        return 0;
    }
    return 1;
}

# object .'|'.1
sub _jm_obj_1($$$)
{
    my ($val, $path, $rep) = @_;
    if (! jm_is_object($val))
    {
        return 0;
    }
    my $res;
    my $must_count = 0;
    scalar keys %$val;
    while (my ($prop, $pval) = each %$val)
    {
        if ($prop eq 'discriminator')
        {
            # handle must discriminator property
            $must_count++;
            # .'|'.1.discriminator
            $res = jm_is_boolean($pval) && $pval == 0;
            if (! $res)
            {
                return 0;
            }
        }
        elsif ($prop eq 'y')
        {
            # handle must y property
            $must_count++;
            # .'|'.1.y
            $res = jm_is_string($pval);
            if (! $res)
            {
                return 0;
            }
        }
        else
        {
            return 0;
        }
    }
    if ($must_count != 2)
    {
        return 0;
    }
    return 1;
}


# check $ (.)
sub json_model_1($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # boolean tag
    # .
    $res = jm_is_object($val);
    if ($res)
    {
        my $tag_0 = $$val{'discriminator'};
        if (defined($tag_0))
        {
            my $fun_0 = $_jm_map_0{$tag_0};
            if (defined($fun_0))
            {
                $res = &$fun_0($val, $path, $rep);
            }
            else
            {
                $res = 0;
            }
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
            1 => \&_jm_obj_0,
            0 => \&_jm_obj_1,
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
