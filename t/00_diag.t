use Test2::V0;
use lib 't/lib';
use TestNOXS;

diag '';
diag '';
diag '';

foreach my $config (qw( multiplicity )) {
    diag "$config = ", $ffi->function( "config_$config" => [] => 'int' )->call;
}

diag '';
diag '';

ok 1;

done_testing;
