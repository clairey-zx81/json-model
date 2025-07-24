#
# Perl Runtime for JSON Model
#
 
package JsonModel;

use strict;
use warnings;

# replace regex engine
# apt install libre-engine-re2-perl
use re::engine::RE2;

use Exporter 'import';
our @ISA = qw( Exporter );

our @EXPORT = qw(
    jm_is_null
    jm_is_boolean
    jm_is_numeric
    jm_is_integer
    jm_is_string
    jm_is_scalar
    jm_is_array
    jm_is_object
    jm_is_valid_url
    jm_is_valid_email
    jm_is_valid_date
    jm_is_valid_time
    jm_is_valid_datetime
    jm_is_valid_regex
    jm_is_valid_exreg
    jm_is_valid_uuid
    jm_obj_size
    jm_any_len
    jm_is_unique_array
    jm_starts_with
    jm_ends_with
);

# WTF
sub jm_raw_is_numeric($)
{
    my ($n) = @_;
    return length(do { no warnings "numeric"; $n & "" }) > 0;
}

# return "guessed" type for JSON value
sub jm_type($)
{
    my ($v) = @_;
    return "null" unless defined $v;
    my $r = ref $v;
    if ($r eq "") {
        # scalar uses some guessing
        return "string" unless jm_raw_is_numeric($v);
        # numeric values may be boolean, integer or number
        return "boolean" if $v == 0 || $v == 1;
        return "integer" if int($v) == $v;
        return "number";  # float
    }
    elsif ($r eq "ARRAY") {
        return "array";
    }
    else {
        return "object";
    }
}

sub jm_is_numeric($)
{
    my ($n) = @_;
    return defined $n && jm_raw_is_numeric($n); 
}

sub jm_is_integer($)
{
    my ($i) = @_;
    return defined $i && (jm_is_numeric($i) && (int($i) == $i)); 
}

sub jm_is_null($)
{
    my ($n) = @_;
    return not defined $n;
}

sub jm_is_boolean($)
{
    my ($b) = @_;
    return defined $b && (jm_is_integer($b) && ($b == 0 || $b == 1));
}

sub jm_is_scalar($)
{
    my ($x) = @_;
    return defined $x && ref $x eq "";
}

sub jm_is_string($)
{
    my ($s) = @_;
    return defined $s && jm_is_scalar($s) && !jm_is_numeric($s);
}

sub jm_is_array($)
{
    my ($a) = @_;
    return defined $a && ref $a eq "ARRAY";
}

sub jm_is_object($)
{
    my ($o) = @_;
    return defined $a && ref $o eq "HASH";
}

#
# PREDEFS
#

# $URL
sub jm_is_valid_url($$$)
{
    my ($u) = @_;
    return $u =~ m,^((https?|file)://.*|\./|\.\./).*$,;
}

# $EMAIL
sub jm_is_valid_email($$$)
{
    my ($e) = @_;
    return $e =~ /^[-a-z0-9_.]+\@[-a-z0-9_.]+$/i;
}

# $DATE
my %MONTH_DAYS = (
    '01' => 31,
    '02' => 29,
    '03' => 31,
    '04' => 30,
    '05' => 31,
    '06' => 30,
    '07' => 31,
    '08' => 31,
    '09' => 30,
    '10' => 31,
    '11' => 30,
    '12' => 31,
);

sub jm_is_valid_date($$$)
{
    my ($d) = @_;
    return 0 if $d !~ /^(\d\d\d\d)-(\d\d)-(\d\d)$/;
    return 0 if $2 == 0 || $2 > 12;
    return 0 if $3 == 0 || $3 > $MONTH_DAYS{$2};
    return 0 if $2 == 2 && $3 == 29 && ! (($1 % 4 == 0 && $1 % 100 != 0) || ($1 % 400 == 0));
    return 1;
}

# $TIME
sub jm_is_valid_time($$$)
{
    my ($t) = @_;
    return $t =~ /^([01]\d|2[0-3]):?[0-5]\d:?[0-5]\d(\.\d+)?(Z|[-+]\d{2}(:?[0-5]\d)?)?$/;
}

# $DATETIME
sub jm_is_valid_datetime($$$)
{
    my ($dt, $p, $r) = @_;
    my ($d, $t, @remainder) = split /[ T]/, $dt;
    return (jm_is_valid_date($d, $p, $r) && jm_is_valid_time($t, $p, $r) && ! @remainder);
}

# $UUID
sub jm_is_valid_uuid($$$)
{
    my ($u) = @_;
    return $u =~ /^[0-9a-f]{8}(-[0-9a-f]{4}){3}-[0-9a-f]{12}$/i;
}

# $REGEX
sub jm_is_valid_regex($$$)
{
    my ($r) = @_;
    eval {
        '' =~ /$r/;
    };
    return $@ eq "";
}

# FIXME $EXTREG
sub jm_is_valid_exreg($$$)
{
    my ($e, $p, $r) = @_;
    return jm_is_valid_regex($e, $p, $r);
}

#
# LENGTH
#

sub jm_obj_size($)
{
    my ($o) = @_;
    return scalar keys %$o;
}

sub jm_any_len($)
{
    my ($x) = $@;
    my $t = jm_type($x);
    return jm_obj_size($x) if $t eq "object";
    return length @$x if $t eq "array";
    return length $x if $t eq "string";
    die "unexpected type $t for length";
}

#
# COMPARISONS
#

# comparison of arrays for sorting
sub jm_cmp_array($$)
{
    my ($a, $b) = @_;
    # array length
    my $d = @$b - @$a;
    return $d if $d;
    # same length
    for my $i (0 ... @$a) {
        my $cmp = jm_cmp($$a[$i], $$b[$i]);
        return $cmp if $cmp;
    }
    return 0;
}

# comparison of objects for sorting
sub jm_cmp_object($$)
{
    my ($a, $b) = @_;
    # object size
    my $sa = keys %$a;
    my $sb = keys %$b;
    my $d = $sb - $sa;
    return $d if $d;
    # same size, try key lists
    my @ka = keys %$a;
    my @kb = keys %$b;
    my $cmp = jm_cmp_array(\@ka, \@kb);
    return $cmp if $cmp;
    # same keys, compare sorted keys values
    for my $k (sort @ka) {
        $cmp = jm_cmp($$a{$k}, $$b{$k});
        return $cmp if $cmp;
    }
    return 0;
}

# JSON value comparison
sub jm_cmp($$)
{
    my ($a, $b) = @_;
    my $ta = jm_type($a);
    my $tb = jm_type($b);
    my $cmp = $ta cmp $tb;
    return $cmp if $cmp;  # distinct types
    return 0 if $ta eq "null";
    return $a <=> $b if $ta ~~ ["boolean", "integer", "number"];
    return $a cmp $b if $ta eq "string";
    return jm_cmp_array($a, $b) if $ta eq "array";
    return jm_cmp_object($a, $b);
}

# shortened comparison if two items are equal
sub jm_cmp_unique($$)
{
    my ($a, $b) = @_;
    my $cmp = jm_cmp($a, $b);
    return $cmp if $cmp;
    die "equal items";
}

# check whether array is unique
sub jm_is_unique_array($$$)
{
    my ($a) = @_;
    return 1 unless jm_is_array($a) && @$a > 1;
    eval {
        () = sort jm_cmp_unique @$a;
    };
    return $@ eq "";  # no exceptions means no equal items where found
}

#
# STRING
#
sub jm_starts_with($$)
{
    my ($s, $prefix) = @_;
    return substr($s, length $prefix) eq $prefix;
}

sub jm_ends_with($$)
{
    my ($s, $suffix) = @_;
    my $ls = length $suffix;
    return substr($s, length $s - $ls, $ls) eq $suffix;
}

1;
