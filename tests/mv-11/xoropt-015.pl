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

# check $V (.'$V')
sub json_model_2($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$V'
    # .'$V'.'|'.0
    $res = jm_is_integer($val);
    if (! $res)
    {
        # .'$V'.'|'.1
        $res = jm_is_string($val);
    }
    return $res;
}

# object .'$X'
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
        if ($prop eq 'X')
        {
            # handle must X property
            $must_count++;
            # .'$X'.X
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
    if ($must_count != 1)
    {
        return 0;
    }
    return 1;
}

# check $X (.'$X')
sub json_model_3($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$X'
    $res = _jm_obj_0($val, $path, $rep);
    return $res;
}

# object .'$Y'
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
        if ($prop eq 'Y')
        {
            # handle must Y property
            $must_count++;
            # .'$Y'.Y
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
    if ($must_count != 1)
    {
        return 0;
    }
    return 1;
}

# check $Y (.'$Y')
sub json_model_4($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$Y'
    $res = _jm_obj_1($val, $path, $rep);
    return $res;
}

# object .'$E'.'|'.1
sub _jm_obj_2($$$)
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
        if ($prop eq 'Y')
        {
            # handle must Y property
            $must_count++;
            # .'$E'.'|'.1.Y
            $res = jm_is_string($pval);
            if (! $res)
            {
                return 0;
            }
        }
        elsif ($prop eq 'Z')
        {
            # handle may Z property
            # .'$E'.'|'.1.Z
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
    if ($must_count != 1)
    {
        return 0;
    }
    return 1;
}

# object .'$E'.'|'.0
sub _jm_obj_3($$$)
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
        if ($prop eq 'X')
        {
            # handle must X property
            $must_count++;
            # .'$E'.'|'.0.X
            $res = jm_is_string($pval);
            if (! $res)
            {
                return 0;
            }
        }
        elsif ($prop eq 'Z')
        {
            # handle may Z property
            # .'$E'.'|'.0.Z
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
    if ($must_count != 1)
    {
        return 0;
    }
    return 1;
}

# check $E (.'$E')
sub json_model_5($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$E'
    $res = jm_is_object($val);
    if ($res)
    {
        # .'$E'.'|'.0
        $res = _jm_obj_3($val, $path, $rep);
        if (! $res)
        {
            # .'$E'.'|'.1
            $res = _jm_obj_2($val, $path, $rep);
        }
    }
    return $res;
}

# check $M (.'$M')
sub json_model_6($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$M'
    # generic xor list
    my $xc_0 = 0;
    my $xr_0;
    # .'$M'.'^'.0
    $xr_0 = json_model_2($val, $path, $rep);
    if ($xr_0)
    {
        $xc_0++;
    }
    # .'$M'.'^'.1
    $xr_0 = json_model_5($val, $path, $rep);
    if ($xr_0)
    {
        $xc_0++;
    }
    $res = $xc_0 == 1;
    return $res;
}

# check $ (.)
sub json_model_1($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .
    $res = json_model_6($val, $path, $rep);
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
            'V' => \&json_model_2,
            'X' => \&json_model_3,
            'Y' => \&json_model_4,
            'E' => \&json_model_5,
            'M' => \&json_model_6,
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
