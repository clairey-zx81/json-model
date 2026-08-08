#! /usr/bin/perl
use utf8;
use strict;
use warnings;
no warnings "uninitialized";
use re::engine::RE2;
use JSON::JsonModel;
use constant JMC_VERSION => "2";


sub json_model_2($$$);
sub json_model_3($$$);
sub json_model_4($$$);
sub json_model_5($$$);
sub json_model_1($$$);
my %check_model_map;

sub json_model_2($$$)
{
    my ($val, $path, $rep) = @_;
    return jm_is_string($val) && jm_starts_with($val, "#");
}

sub json_model_3($$$)
{
    my ($val, $path, $rep) = @_;
    my $res = jm_is_array($val) && scalar @$val == 2;
    if ($res)
    {
        $res = jm_is_boolean($$val[0]);
        $res = 1 if $res;
    }
    return $res;
}

sub _jm_re_0($$$)
{
    my ($val, $path, $rep) = @_;
    my $res = $val =~ /^[-\w]*$/s;
    return $res;
}

sub json_model_4($$$)
{
    my ($val, $path, $rep) = @_;
    my $res = jm_is_array($val) && scalar @$val == 3;
    if ($res)
    {
        $res = jm_is_boolean($$val[0]);
        if ($res)
        {
            $res = jm_is_string($$val[1]) && _jm_re_0($$val[1], undef, undef);
            $res = 1 if $res;
        }
    }
    return $res;
}

sub json_model_5($$$)
{
    my ($val, $path, $rep) = @_;
    return json_model_2($val, undef, undef) || json_model_3($val, undef, undef) || json_model_4($val, undef, undef);
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
            $res = json_model_5($arr_0_item, undef, undef);
            last unless $res;
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
        %check_model_map = (
            "" => \&json_model_1,
            "Comment" => \&json_model_2,
            "Test2" => \&json_model_3,
            "Test3" => \&json_model_4,
            "Test" => \&json_model_5,
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
