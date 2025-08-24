#! /bin/env perl
use strict;
use warnings;
use Person;
use JSON::MaybeXS;

check_model_init();
my $hobbes = decode_json('{"name": "Hobbes", "birth": "2020-07-29"}');
print "hobbes is a person: ", check_model($hobbes, "", undef), "\n";
check_model_free();
