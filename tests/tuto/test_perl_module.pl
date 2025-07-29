#! /usr/bin/perl -w

use JSON::MaybeXS;
use person;

my $susie = '{"name": "Susie", "birth": "1990-10-14"}';
my $su = decode_json($susie);

check_model_init();
print "Susie is a person: ", check_model($su, "", undef), "\n";
check_model_free();
