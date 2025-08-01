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


my %_jm_cst_0;
my %_jm_obj_0_map;
my %_jm_cst_1;
my %check_model_map;

# check _jm_obj_0_map_$ref (.'$schema'.'$ref')
sub _jm_f_0($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.'$ref'
    $res = jm_is_string($val);
    return $res;
}

# check _jm_obj_0_map_$schema (.'$schema'.'$schema')
sub _jm_f_1($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.'$schema'
    $res = jm_is_string($val);
    return $res;
}

# check _jm_obj_0_map_additionalItems (.'$schema'.additionalItems)
sub _jm_f_2($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.additionalItems
    # .'$schema'.additionalItems.'|'.0
    $res = jm_is_boolean($val);
    if (! $res)
    {
        # .'$schema'.additionalItems.'|'.1
        $res = json_model_3($val, $path, $rep);
    }
    return $res;
}

# check _jm_obj_0_map_additionalProperties (.'$schema'.additionalProperties)
sub _jm_f_3($$$)
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

# check _jm_obj_0_map_default (.'$schema'.default)
sub _jm_f_4($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.default
    $res = 1;
    return $res;
}

# object .'$schema'.dependencies
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
        # .'$schema'.dependencies.''
        # .'$schema'.dependencies.''.'|'.0
        $res = jm_is_string($pval);
        if (! $res)
        {
            # .'$schema'.dependencies.''.'|'.1
            $res = jm_is_array($pval);
            if ($res)
            {
                for my $arr_0_idx (0 .. $#$pval)
                {
                    my $arr_0_item = $$pval[$arr_0_idx];
                    # .'$schema'.dependencies.''.'|'.1.0
                    $res = jm_is_string($arr_0_item);
                    if (! $res)
                    {
                        last;
                    }
                }
            }
            if (! $res)
            {
                # .'$schema'.dependencies.''.'|'.2
                $res = json_model_3($pval, undef, $rep);
            }
        }
        if (! $res)
        {
            return 0;
        }
    }
    return 1;
}

# check _jm_obj_0_map_dependencies (.'$schema'.dependencies)
sub _jm_f_5($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.dependencies
    $res = _jm_obj_1($val, $path, $rep);
    return $res;
}

# check _jm_obj_0_map_description (.'$schema'.description)
sub _jm_f_6($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.description
    $res = jm_is_string($val);
    return $res;
}

# check _jm_obj_0_map_disallow (.'$schema'.disallow)
sub _jm_f_7($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.disallow
    # .'$schema'.disallow.'|'.0
    $res = jm_is_string($val);
    if (! $res)
    {
        # .'$schema'.disallow.'|'.1
        $res = json_model_5($val, $path, $rep);
    }
    return $res;
}

# check _jm_obj_0_map_divisibleBy (.'$schema'.divisibleBy)
sub _jm_f_8($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.divisibleBy
    $res = jm_is_numeric($val) && $val > 0.0;
    return $res;
}

# check _jm_obj_0_map_enum (.'$schema'.enum)
sub _jm_f_9($$$)
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
        $res = jm_is_unique_array($val, $path, $rep) && $ival_0 >= 1;
    }
    return $res;
}

# check _jm_obj_0_map_exclusiveMaximum (.'$schema'.exclusiveMaximum)
sub _jm_f_10($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.exclusiveMaximum
    $res = jm_is_boolean($val);
    return $res;
}

# check _jm_obj_0_map_exclusiveMinimum (.'$schema'.exclusiveMinimum)
sub _jm_f_11($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.exclusiveMinimum
    $res = jm_is_boolean($val);
    return $res;
}

# check _jm_obj_0_map_extends (.'$schema'.extends)
sub _jm_f_12($$$)
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
sub _jm_f_13($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.format
    $res = jm_is_scalar($val) && jm_is_string($val) && exists $_jm_cst_0{$val};
    return $res;
}

# check _jm_obj_0_map_id (.'$schema'.id)
sub _jm_f_14($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.id
    $res = jm_is_string($val);
    return $res;
}

# check _jm_obj_0_map_items (.'$schema'.items)
sub _jm_f_15($$$)
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

# check _jm_obj_0_map_maxItems (.'$schema'.maxItems)
sub _jm_f_16($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.maxItems
    $res = jm_is_integer($val) && $val >= 0;
    return $res;
}

# check _jm_obj_0_map_maxLength (.'$schema'.maxLength)
sub _jm_f_17($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.maxLength
    $res = jm_is_integer($val) && $val >= 0;
    return $res;
}

# check _jm_obj_0_map_maximum (.'$schema'.maximum)
sub _jm_f_18($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.maximum
    $res = jm_is_numeric($val);
    return $res;
}

# check _jm_obj_0_map_minItems (.'$schema'.minItems)
sub _jm_f_19($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.minItems
    $res = jm_is_integer($val) && $val >= 0;
    return $res;
}

# check _jm_obj_0_map_minLength (.'$schema'.minLength)
sub _jm_f_20($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.minLength
    $res = jm_is_integer($val) && $val >= 0;
    return $res;
}

# check _jm_obj_0_map_minimum (.'$schema'.minimum)
sub _jm_f_21($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.minimum
    $res = jm_is_numeric($val);
    return $res;
}

# check _jm_obj_0_map_pattern (.'$schema'.pattern)
sub _jm_f_22($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.pattern
    $res = jm_is_string($val) && jm_is_valid_regex($val, $path, $rep);
    return $res;
}

# object .'$schema'.patternProperties
sub _jm_obj_2($$$)
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
        # .'$schema'.patternProperties.''
        $res = json_model_3($pval, undef, $rep);
        if (! $res)
        {
            return 0;
        }
    }
    return 1;
}

# check _jm_obj_0_map_patternProperties (.'$schema'.patternProperties)
sub _jm_f_23($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.patternProperties
    $res = _jm_obj_2($val, $path, $rep);
    return $res;
}

# object .'$schema'.properties
sub _jm_obj_3($$$)
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
sub _jm_f_24($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.properties
    $res = _jm_obj_3($val, $path, $rep);
    return $res;
}

# check _jm_obj_0_map_required (.'$schema'.required)
sub _jm_f_25($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.required
    $res = jm_is_boolean($val);
    return $res;
}

# check _jm_obj_0_map_title (.'$schema'.title)
sub _jm_f_26($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.title
    $res = jm_is_string($val);
    return $res;
}

# check _jm_obj_0_map_type (.'$schema'.type)
sub _jm_f_27($$$)
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

# check _jm_obj_0_map_uniqueItems (.'$schema'.uniqueItems)
sub _jm_f_28($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema'.uniqueItems
    $res = jm_is_boolean($val);
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
            # handle 29 may props
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
    # JSON Model for JSON Schema Draft 03 [JSON_MODEL_STRICT_INT, JSON_MODEL_LOOSE_FLOAT]
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
    $res = jm_is_scalar($val) && jm_is_string($val) && exists $_jm_cst_1{$val};
    return $res;
}

# check $schema#distinctSchemaArray (.'$schema#distinctSchemaArray')
sub json_model_5($$$)
{
    my ($val, $path, $rep) = @_;
    my $res;
    # .'$schema#distinctSchemaArray'
    # .'$schema#distinctSchemaArray'.'@'
    $res = jm_is_array($val);
    if ($res)
    {
        for my $arr_4_idx (0 .. $#$val)
        {
            my $arr_4_item = $$val[$arr_4_idx];
            # .'$schema#distinctSchemaArray'.'@'.0
            # .'$schema#distinctSchemaArray'.'@'.0.'|'.0
            $res = jm_is_string($arr_4_item);
            if (! $res)
            {
                # .'$schema#distinctSchemaArray'.'@'.0.'|'.1
                $res = json_model_3($arr_4_item, undef, $rep);
            }
            if (! $res)
            {
                last;
            }
        }
    }
    if ($res)
    {
        $res = jm_is_unique_array($val, $path, $rep);
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
        %_jm_cst_0 = (
            'date-time' => 1,
            'date' => 1,
            'time' => 1,
            'utc-millisec' => 1,
            'regex' => 1,
            'color' => 1,
            'style' => 1,
            'phone' => 1,
            'uri' => 1,
            'email' => 1,
            'ip-address' => 1,
            'ipv6' => 1,
            'host-name' => 1,
        );
        %_jm_obj_0_map = (
            '$ref' => \&_jm_f_0,
            '$schema' => \&_jm_f_1,
            'additionalItems' => \&_jm_f_2,
            'additionalProperties' => \&_jm_f_3,
            'default' => \&_jm_f_4,
            'dependencies' => \&_jm_f_5,
            'description' => \&_jm_f_6,
            'disallow' => \&_jm_f_7,
            'divisibleBy' => \&_jm_f_8,
            'enum' => \&_jm_f_9,
            'exclusiveMaximum' => \&_jm_f_10,
            'exclusiveMinimum' => \&_jm_f_11,
            'extends' => \&_jm_f_12,
            'format' => \&_jm_f_13,
            'id' => \&_jm_f_14,
            'items' => \&_jm_f_15,
            'maxItems' => \&_jm_f_16,
            'maxLength' => \&_jm_f_17,
            'maximum' => \&_jm_f_18,
            'minItems' => \&_jm_f_19,
            'minLength' => \&_jm_f_20,
            'minimum' => \&_jm_f_21,
            'pattern' => \&_jm_f_22,
            'patternProperties' => \&_jm_f_23,
            'properties' => \&_jm_f_24,
            'required' => \&_jm_f_25,
            'title' => \&_jm_f_26,
            'type' => \&_jm_f_27,
            'uniqueItems' => \&_jm_f_28,
        );
        %_jm_cst_1 = (
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
        %_jm_cst_0 = ();
        %_jm_obj_0_map = ();
        %_jm_cst_1 = ();
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
