use 5.020;
use warnings;

my $count = shift @ARGV;

$|=1;

if(defined $count && $count =~ /^[34]\z/) {
    say "ok $count";
} else {
    say "not ok 1";
}
