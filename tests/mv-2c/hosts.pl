#! /usr/bin/perl
use strict;
use warnings;
no warnings "uninitialized";
use re::engine::RE2;
use JSON::JsonModel;
use constant JMC_VERSION => '2';


sub json_model_1($$$);
my %check_model_map;

sub json_model_1($$$)
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
        if ($prop eq 'host')
        {
            $res = jm_is_string($pval) && jm_is_host($pval, undef, undef) && length $pval <= 255;
            if (! $res)
            {
                return 0;
            }
            next;
        }
        elsif ($prop eq 'ipv4')
        {
            $res = jm_is_string($pval) && jm_is_ip4($pval, undef, undef);
            if (! $res)
            {
                return 0;
            }
            next;
        }
        elsif ($prop eq 'ipv6')
        {
            $res = jm_is_string($pval) && jm_is_ip6($pval, undef, undef);
            if (! $res)
            {
                return 0;
            }
            next;
        }
        return 0;
    }
    return 1;
}


sub jm_is_host($$$)
{
    my ($val, $path, $rep) = @_;
    my $res = $val =~ /^([a-z0-9][-a-z0-9]{0,62})(\.([a-z0-9][-a-z0-9]{0,62}))*$/i;
    return $res;
}

sub jm_is_ip4($$$)
{
    my ($val, $path, $rep) = @_;
    my $res = $val =~ /^(([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])\.){3}([0-9]|[1-9][0-9]|1[0-9][0-9]|2[0-4][0-9]|25[0-5])$/;
    return $res;
}

sub jm_is_ip6($$$)
{
    my ($val, $path, $rep) = @_;
    my $res = $val =~ /^(([0-9a-f]{1,4}:){7}[0-9a-f]{1,4}|([0-9a-f]{1,4}:){1,7}:|([0-9a-f]{1,4}:){1,6}(:[0-9a-f]{1,4}){1}|([0-9a-f]{1,4}:){1,5}(:[0-9a-f]{1,4}){1,2}|([0-9a-f]{1,4}:){1,4}(:[0-9a-f]{1,4}){1,3}|([0-9a-f]{1,4}:){1,3}(:[0-9a-f]{1,4}){1,4}|([0-9a-f]{1,4}:){1,2}(:[0-9a-f]{1,4}){1,5}|[0-9a-f]{1,4}:(:[0-9a-f]{1,4}){1,6}|:(:[0-9a-f]{1,4}){1,7}|::)$/i;
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
