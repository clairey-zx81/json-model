#
# Perl Runtime for JSON Model
#
# ubuntu apt install:
# - libre-engine-re2-perl
# - libjson-maybexs-perl
# - libcpanel-json-xs-perl
# - libdatetime-hires-perl
#
# TODO add minimal pod
#

package JsonModel;

use strict;
use warnings;

# replace regex engine
use re::engine::RE2;
use List::Util qw( min );
use JSON::MaybeXS qw( decode_json is_bool );
use Getopt::Long qw(:config no_ignore_case);
use Time::HiRes 'time';

# automatic export
use Exporter 'import';
our @ISA = qw( Exporter );
our @EXPORT = qw(
    TRUE
    FALSE
    jm_type
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
    jm_check_constraint
    jm_starts_with
    jm_ends_with
    jm_main
);

# TODO remove if unused
use constant TRUE => decode_json("true", 1);
use constant FALSE => decode_json("false", 1);

# WTF
sub jm_raw_is_numeric($)
{
    my ($n) = @_;
    return do {
        no if $] >= 5.022, "feature", "bitwise";
        no warnings "numeric";
        eval 'length($n & "") > 0'
    }
}

# return "guessed" json type for JSON value
sub jm_type($)
{
    my ($v) = @_;
    return "null" unless defined $v;
    my $r = ref $v;
    if ($r eq "") {
        return "string" unless jm_raw_is_numeric($v);
        return "integer" if int($v) == $v;
        return "number";  # float
    }
    elsif ($r eq "ARRAY") {
        return "array";
    }
    elsif ($r eq "HASH") {
        return "object";
    }
    elsif (is_bool $v) {
        return "boolean";
    }
    else {
        die "unexpected ref: $r";
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
    return defined $b && is_bool($b);
}

sub jm_is_scalar($)
{
    my ($x) = @_;
    return ref $x eq "";
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
    return defined $o && ref $o eq "HASH";
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
    return $t =~ /^T?([01]\d|2[0-3]):?[0-5]\d:?[0-5]\d(\.\d+)?(Z|[-+]\d{2}(:?[0-5]\d)?)?$/;
}

# $DATETIME
# FIXME TT is accepted
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
    my ($x) = @_;
    my $t = jm_type($x);
    return jm_obj_size($x) if $t eq "object";
    return scalar @$x if $t eq "array";
    return length $x if $t eq "string";
    return $x if $t eq "integer";
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
    # same size, try sorted key lists
    my @ka = sort keys %$a;
    my @kb = sort keys %$b;
    my $cmp = jm_cmp_array(\@ka, \@kb);
    return $cmp if $cmp;
    # same keys, compare sorted keys values
    for my $k (sort @ka) {
        $cmp = jm_cmp($$a{$k}, $$b{$k});
        return $cmp if $cmp;
    }
    return 0;
}

our %NUM_TYPE = ("integer" => 1, "number" => 1);

# JSON value comparison
sub jm_cmp($$)
{
    my ($a, $b) = @_;
    my $ta = jm_type($a);
    my $tb = jm_type($b);
    my $cmp = $ta cmp $tb;
    return $cmp if $cmp;  # sort by type
    # else same type, sort by value
    return 0 if $ta eq "null";
    return $a <=> $b if exists $NUM_TYPE{$ta};
    return $a cmp $b if $ta eq "string";
    return jm_cmp_array($a, $b) if $ta eq "array";
    return $b == $a ? 0 : $b ? 1 : -1 if $ta eq "boolean";
    return jm_cmp_object($a, $b) if $ta eq "object";
    die "unexpected type for comparison: $ta";
}

# shortened comparison if two items are equal
sub jm_cmp_unique($$)
{
    my ($a, $b) = @_;
    my $cmp = jm_cmp($a, $b);
    return $cmp if $cmp;
    # trigger exception to shorten sort on equal items
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

sub jm_check_constraint($$$$$)
{
    my ($val, $op, $cst, $path, $rep) = @_;

    my ($tc, $tv) = (jm_type($cst), jm_type($val));
    my $cval;

    # depending on 
    if ($tc eq "null") {
        return jm_is_null($val);
    }
    elsif ($tc eq "boolean") {
        # DEAD CODE
        return 0;
    }
    elsif ($tc eq "integer") {
        $cval = jm_any_len($val);            
    }
    elsif ($tc eq "number") {
        return 0 unless $tv eq "integer" || $tv eq "number";
        $cval = $val;
    }
    elsif ($tc eq "string") {
        return 0 unless $tv eq "string";
        # string comparisons
        return $val eq $cst if $op eq "=";
        return $val ne $cst if $op eq "!=";
        return $val le $cst if $op eq "<=";
        return $val lt $cst if $op eq "<";
        return $val ge $cst if $op eq ">=";
        return $val gt $cst if $op eq ">";
        die "unexpected string comparison operator $op";
    }
    else {
        die "unexpected constant type $tc";
    }

    # number comparisons
    return $cval == $cst if $op eq "=";
    return $cval != $cst if $op eq "!=";
    return $cval <= $cst if $op eq "<=";
    return $cval < $cst if $op eq "<";
    return $cval >= $cst if $op eq ">=";
    return $cval > $cst if $op eq ">";
    die "unexpected number comparison operator $op";
}

#
# STRING
#
sub jm_starts_with($$)
{
    my ($s, $prefix) = @_;
    return substr($s, 0, length $prefix) eq $prefix;
}

sub jm_ends_with($$)
{
    my ($s, $suffix) = @_;
    my $ls = length $suffix;
    return substr($s, length($s) - $ls, $ls) eq $suffix;
}

#
# RUNNING AND BENCHMARKING
#

# see https://github.com/sourcemeta-research/jsonschema-benchmark
sub jsonschema_benchmark($$$$)
{
    my ($checker, $jsons, $display, $time) = @_;
    my $errors = 0;

    $time = 1 unless defined $time and $time > 0;

    # cold run, once, check results
    my $cold_start = time;
    for my $j (@$jsons) {
        $errors++ unless &$checker($j, '', undef);
    }
    my $cold_stop = time;
    my $cold_delay = $cold_stop - $cold_start;  # seconds

    # warmup, at most 10 seconds
    my $max = int(10.0 / $cold_delay);
    my $n = min($time, $max);

    while ($n--)
    {
        for my $j (@$jsons) {
            &$checker($j, '', undef);
        }
    }

    # warm run
    my ($sum, $sum2) = (0.0, 0.0);
    $n = $time;
    while ($n--)
    {
        my $start = time;
        for my $j (@$jsons) {
            &$checker($j, '', undef);
        }
        my $stop = time;
        my $delay = 1_000_000 * ($stop - $start);  # µs
        $sum += $delay;
        $sum2 += $delay * $delay;
    }
    my $avg = $sum / $time;
    my $stdev = sqrt($sum2 / $time - $avg * $avg);

    # show rounded results
    printf STDERR "$display: %.03f ± %.03f µs\n", $avg, $stdev;
    my ($ns_cold, $ns_warm) = (int($cold_delay * 1E9 + 0.5), int($avg * 1E3 + 0.5));
    print "$ns_cold,$ns_warm\n";

    return $errors;
}

sub jm_process($$$$$$$)
{
    my ($checker, $name, $json, $display, $report, $expect, $time) = @_;
    my $rep = $report ? [] : undef;
    my $valid = &$checker($json, $name, $rep) ? 1 : 0;

    my $ok;
    if (defined $expect) {
        if ($valid == $expect) {
            print "$display: ", $valid? "PASS": "FAIL", "\n";
            $ok = 1;
        }
        else {
            print "$display: ERROR, unexpected ", $valid? "PASS": "FAIL", "\n";
            $ok = 0;
        }
    }
    else {
        print "$display: ", $valid? "PASS": "FAIL", "\n";
        $ok = 1;
    }

    # performance
    if ($time)
    {
        # empty loop measure overhead
        my $n = $time;
        my $empty = 0.0;
        my ($start, $stop);
        while ($n--) {
            $start = time;
            $stop = time;
            $empty += 1_000_000 * ($stop - $start);  # µs
        }
        $empty /= $time;

        # performance loop
        my $ok;
        $n = $time;
        my ($sum, $sum2) = (0.0, 0.0);
        while ($n--) {
            $start = time;
            $ok = &$checker($json, $name, $rep);
            $stop = time;
            my $delay = 1_000_000 * ($stop - $start) - $empty;  # µs
            $sum += $delay;
            $sum2 += $delay * $delay;
        }

        # perforlance display
        my $avg = $sum / $time;
        my $stdev = sqrt( $sum2 / $time - $avg * $avg );
        printf "$display: %.03f ± %.03f µs [%.03f]\n", $avg, $stdev, $empty;
    }

    return $ok;
}

sub decode_json_nonref($)
{
    my ($j) = @_;
    return decode_json($j, 1);
}

sub jm_main($$$)
{
    my ($checker, $map, $version) = @_;
    my $errors = 0;

    # options
    my ($name, $test, $jsonl, $time, $report, $js_bench) = ("", 0, 0, 0, 0, 0);
    GetOptions(
        "version" => sub { print "version: $version\n"; exit 0 },
        "help" => sub { print "$0 help: https://json-model.org\n"; exit 0 },
        "list|l" => sub { print "names: ", (sort keys %$map), "\n"; exit 0 },
        "report|r" => \$report,
        "name=s" => \$name,
        "test|t" => \$test,
        "time|T=i" => \$time,
        "jsonl|L" => \$jsonl,
        "jsonschema-benchmark" => \$js_bench,
    );

    # loop over value files
    for my $file (@ARGV)
    {
        my $contents;

        # read raw file contents
        if ($file ne "-") {
            open my $fh, "<", $file or die "cannot open file $file: $!";
            $contents = do { local $/ = undef; <$fh> };
            close $fh;
        }
        else {
            $contents = do { local $/ = undef; <STDIN> };
        }

        # read and parse contents
        my $json;
        eval {
            if ($jsonl) {
                $json = [ map decode_json_nonref split /\n/, $contents ];
            }
            else {
                $json = decode_json_nonref $contents;
                $json = [[ undef, $json ]] unless $test;
            }
        };
        if ($@) {
            my $message = $@;
            $message =~ tr/\n\r\f/ /;
            $message =~ s/\s+$//;
            $message =~ s/ at \/.*? line \d+\.//;
            print "$file: ERROR (JSON error: $message)\n";
            if ($test) {
                warn "skipping non-json file: $file\n";
                $errors++;
            }
            next;
        }

        # jsonschema benchmark code
        if ($js_bench)
        {
            # adjust list to match benchmarking function expectations
            $json = [map { $$_[-1] } @$json] unless $jsonl;
            # and run on list
            $errors += jsonschema_benchmark($checker, $json, $file, $time);
            next;
        }

        # else standard value/values processing
        die "expecting a list" unless jm_type($json) eq "array";
        my $index = 0;
        for my $item (@$json) {
            next if jm_type($item) eq "string";

            # extract test case
            die "expecting a tuple" unless jm_type($item) eq "array";
            die "bad tuple length" unless 2 <= @$item <= 3;
            my ($e, $n, $j);
            if (@$item == 3) {
                ($e, $n, $j) = @$item;
            }
            else {
                $n = $name;
                ($e, $j) = @$item;
            }
            my $display = $test ? "$file\[$index\]" : $file;

            $errors++ unless jm_process($checker, $n, $j, $display, $report, $e, $time);
            $index++;
        }
    }

    exit $errors ? 2 : 0;
}

1;
