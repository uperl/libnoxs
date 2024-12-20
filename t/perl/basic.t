use Test2::V0;
use lib 't/lib';
use TestNOXS;

our $x = 1;

sub callback { $x++; };

subtest 'same interp' => sub {

    my $interp = $ffi->function( interp_new_from_perl => ['opaque'] => 'opaque' )->call(undef);
    $ffi->function( interp_call_sub_0 => ['opaque', 'string'] => 'void' )->call($interp, "callback");

    is($ffi->function( interp_is_valid => ['opaque'] => 'int' )->call($interp), 1);
    is($ffi->function( interp_is_embeded => ['opaque'] => 'int' )->call($interp), 1);

    $ffi->function( interp_free => ['opaque'] => 'void' )->call($interp);

    is $x, 2;

    $interp = $ffi->function( interp_new_from_perl => ['opaque'] => 'opaque' )->call(undef);
    $ffi->function( interp_call_sub_0 => ['opaque', 'string'] => 'void' )->call($interp, "callback");
    $ffi->function( interp_free => ['opaque'] => 'void' )->call($interp);

    is $x, 3;

};

$ffi->function( DONE => [] => 'void' )->call;

done_testing;
