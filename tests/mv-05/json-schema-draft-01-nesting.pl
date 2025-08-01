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


my %_jm_obj_0_map;
my %_jm_cst_0;
my %check_model_map;

# check _jm_obj_0_map_$schema (.'$schema'.'$schema')
sub _jm_f_0($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.'$schema'
    $res = jm_is_string($val);
    return $res;
}

# check _jm_obj_0_map_additionalProperties (.'$schema'.additionalProperties)
sub _jm_f_1($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.additionalProperties
    # .'$schema'.additionalProperties.'|'.0
    $res = jm_is_boolean($val);
    if (! $res)
    {
        # .'$schema'.additionalProperties.'|'.1
        $res = json_model_3($val, $path, $rep);
    }
    return $res;
}

# check _jm_obj_0_map_contentEncoding (.'$schema'.contentEncoding)
sub _jm_f_2($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.contentEncoding
    $res = jm_is_string($val);
    return $res;
}

# check _jm_obj_0_map_default (.'$schema'.default)
sub _jm_f_3($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.default
    $res = 1;
    return $res;
}

# check _jm_obj_0_map_description (.'$schema'.description)
sub _jm_f_4($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.description
    $res = jm_is_string($val);
    return $res;
}

# check _jm_obj_0_map_disallow (.'$schema'.disallow)
sub _jm_f_5($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.disallow
    # .'$schema'.disallow.'|'.0
    $res = jm_is_string($val);
    if (! $res)
    {
        # .'$schema'.disallow.'|'.1
        $res = jm_is_array($val);
        if ($res)
        {
            for my $arr_0_idx (0 .. $#$val)
            {
                my $arr_0_item = $$val[$arr_0_idx];
                # .'$schema'.disallow.'|'.1.0
                $res = jm_is_string($arr_0_item);
                if (! $res)
                {
                    last;
                }
            }
        }
    }
    return $res;
}

# check _jm_obj_0_map_enum (.'$schema'.enum)
sub _jm_f_6($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.enum
    # .'$schema'.enum.'@'
    $res = jm_is_array($val);
    if ($res)
    {
        # accept any array
        ;
    }
    if ($res)
    {
        my $ival_0 = scalar @$val;
        $res = $ival_0 >= 1;
    }
    return $res;
}

# check _jm_obj_0_map_extends (.'$schema'.extends)
sub _jm_f_7($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.extends
    # .'$schema'.extends.'|'.0
    $res = json_model_3($val, $path, $rep);
    if (! $res)
    {
        # .'$schema'.extends.'|'.1
        $res = jm_is_array($val);
        if ($res)
        {
            for my $arr_1_idx (0 .. $#$val)
            {
                my $arr_1_item = $$val[$arr_1_idx];
                # .'$schema'.extends.'|'.1.0
                $res = json_model_3($arr_1_item, undef, $rep);
                if (! $res)
                {
                    last;
                }
            }
        }
    }
    return $res;
}

# check _jm_obj_0_map_format (.'$schema'.format)
sub _jm_f_8($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.format
    $res = jm_is_string($val);
    return $res;
}

# check _jm_obj_0_map_id (.'$schema'.id)
sub _jm_f_9($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.id
    $res = jm_is_string($val);
    return $res;
}

# check _jm_obj_0_map_items (.'$schema'.items)
sub _jm_f_10($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.items
    # .'$schema'.items.'|'.0
    $res = json_model_3($val, $path, $rep);
    if (! $res)
    {
        # .'$schema'.items.'|'.1
        $res = jm_is_array($val);
        if ($res)
        {
            for my $arr_2_idx (0 .. $#$val)
            {
                my $arr_2_item = $$val[$arr_2_idx];
                # .'$schema'.items.'|'.1.0
                $res = json_model_3($arr_2_item, undef, $rep);
                if (! $res)
                {
                    last;
                }
            }
        }
    }
    return $res;
}

# check _jm_obj_0_map_maxDecimal (.'$schema'.maxDecimal)
sub _jm_f_11($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.maxDecimal
    $res = jm_is_integer($val) && $val >= 0;
    return $res;
}

# check _jm_obj_0_map_maxItems (.'$schema'.maxItems)
sub _jm_f_12($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.maxItems
    $res = jm_is_integer($val) && $val >= 0;
    return $res;
}

# check _jm_obj_0_map_maxLength (.'$schema'.maxLength)
sub _jm_f_13($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.maxLength
    $res = jm_is_integer($val) && $val >= 0;
    return $res;
}

# check _jm_obj_0_map_maximum (.'$schema'.maximum)
sub _jm_f_14($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.maximum
    $res = jm_is_numeric($val);
    return $res;
}

# check _jm_obj_0_map_maximumCanEqual (.'$schema'.maximumCanEqual)
sub _jm_f_15($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.maximumCanEqual
    $res = jm_is_boolean($val);
    return $res;
}

# check _jm_obj_0_map_minItems (.'$schema'.minItems)
sub _jm_f_16($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.minItems
    $res = jm_is_integer($val) && $val >= 0;
    return $res;
}

# check _jm_obj_0_map_minLength (.'$schema'.minLength)
sub _jm_f_17($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.minLength
    $res = jm_is_integer($val) && $val >= 0;
    return $res;
}

# check _jm_obj_0_map_minimum (.'$schema'.minimum)
sub _jm_f_18($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.minimum
    $res = jm_is_numeric($val);
    return $res;
}

# check _jm_obj_0_map_minimumCanEqual (.'$schema'.minimumCanEqual)
sub _jm_f_19($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.minimumCanEqual
    $res = jm_is_boolean($val);
    return $res;
}

# check _jm_obj_0_map_optional (.'$schema'.optional)
sub _jm_f_20($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.optional
    $res = jm_is_boolean($val);
    return $res;
}

# check _jm_obj_0_map_pattern (.'$schema'.pattern)
sub _jm_f_21($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.pattern
    $res = jm_is_string($val) && jm_is_valid_regex($val, $path, $rep);
    return $res;
}

# object .'$schema'.properties
sub _jm_obj_1($$$)
{
    my ($val, $path, $rep) = @_;
    if (! jm_is_object($val))
    {
        return 0;
    }
    my $res;
    scalar keys %$val;
    while (my ($prop, $pval) = each %$val)
    {
        # handle other props
        # .'$schema'.properties.''
        $res = json_model_3($pval, undef, $rep);
        if (! $res)
        {
            return 0;
        }
    }
    return 1;
}

# check _jm_obj_0_map_properties (.'$schema'.properties)
sub _jm_f_22($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.properties
    $res = _jm_obj_1($val, $path, $rep);
    return $res;
}

# check _jm_obj_0_map_requires (.'$schema'.requires)
sub _jm_f_23($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.requires
    # .'$schema'.requires.'|'.0
    $res = jm_is_string($val);
    if (! $res)
    {
        # .'$schema'.requires.'|'.1
        $res = json_model_3($val, $path, $rep);
    }
    return $res;
}

# check _jm_obj_0_map_title (.'$schema'.title)
sub _jm_f_24($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.title
    $res = jm_is_string($val);
    return $res;
}

# check _jm_obj_0_map_type (.'$schema'.type)
sub _jm_f_25($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.type
    # .'$schema'.type.'|'.0
    $res = json_model_4($val, $path, $rep);
    if (! $res)
    {
        # .'$schema'.type.'|'.1
        $res = jm_is_array($val);
        if ($res)
        {
            for my $arr_3_idx (0 .. $#$val)
            {
                my $arr_3_item = $$val[$arr_3_idx];
                # .'$schema'.type.'|'.1.0
                # .'$schema'.type.'|'.1.0.'|'.0
                $res = jm_is_string($arr_3_item);
                if (! $res)
                {
                    # .'$schema'.type.'|'.1.0.'|'.1
                    $res = json_model_3($arr_3_item, undef, $rep);
                }
                if (! $res)
                {
                    last;
                }
            }
        }
    }
    return $res;
}


# object .'$schema'
sub _jm_obj_0($$$)
{
    my ($val, $path, $rep) = @_;
    if (! jm_is_object($val))
    {
        return 0;
    }
    my $res;
    my $pfun;
    scalar keys %$val;
    while (my ($prop, $pval) = each %$val)
    {
        if (($pfun = $_jm_obj_0_map{$prop}))
        {
            # handle 26 may props
            if (defined($pfun) && ! &$pfun($pval, undef, $rep))
            {
                return 0;
            }
        }
        else
        {
            # handle other props
            # .'$schema'.''
            $res = json_model_3($pval, undef, $rep);
            if (! $res)
            {
                return 0;
            }
        }
    }
    return 1;
}

# check $schema (.'$schema')
sub json_model_3($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # JSON Model for JSON Schema Draft 01 [JSON_MODEL_STRICT_INT, JSON_MODEL_LOOSE_FLOAT]
    # .'$schema'
    $res = _jm_obj_0($val, $path, $rep);
    return $res;
}

# check $ (.)
sub json_model_1($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .
    $res = json_model_3($val, $path, $rep);
    return $res;
}


# check $schema#allTypes (.'$schema#allTypes')
sub json_model_4($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema#allTypes'
    $res = jm_is_scalar($val) && jm_is_string($val) && exists $_jm_cst_0{$val};
    return $res;
}


# initialization of global variables

our $initialized = 0;

sub check_model_init()
{
    if (!$initialized)
    {
        $initialized = 1;
        %_jm_obj_0_map = (
            '$schema' => \&_jm_f_0,
            'additionalProperties' => \&_jm_f_1,
            'contentEncoding' => \&_jm_f_2,
            'default' => \&_jm_f_3,
            'description' => \&_jm_f_4,
            'disallow' => \&_jm_f_5,
            'enum' => \&_jm_f_6,
            'extends' => \&_jm_f_7,
            'format' => \&_jm_f_8,
            'id' => \&_jm_f_9,
            'items' => \&_jm_f_10,
            'maxDecimal' => \&_jm_f_11,
            'maxItems' => \&_jm_f_12,
            'maxLength' => \&_jm_f_13,
            'maximum' => \&_jm_f_14,
            'maximumCanEqual' => \&_jm_f_15,
            'minItems' => \&_jm_f_16,
            'minLength' => \&_jm_f_17,
            'minimum' => \&_jm_f_18,
            'minimumCanEqual' => \&_jm_f_19,
            'optional' => \&_jm_f_20,
            'pattern' => \&_jm_f_21,
            'properties' => \&_jm_f_22,
            'requires' => \&_jm_f_23,
            'title' => \&_jm_f_24,
            'type' => \&_jm_f_25,
        );
        %_jm_cst_0 = (
            'null' => 1,
            'boolean' => 1,
            'integer' => 1,
            'number' => 1,
            'string' => 1,
            'array' => 1,
            'object' => 1,
            'any' => 1,
        );
        %check_model_map = (
            '' => \&json_model_1,
            'schema' => \&json_model_3,
        );
    }
}

sub check_model_free()
{
    if ($initialized)
    {
        $initialized = 0;
        %_jm_obj_0_map = ();
        %_jm_cst_0 = ();
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
