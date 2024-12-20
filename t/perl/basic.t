use Test2::V0;
use lib 't/lib';
use TestNOXS;
use Config;
use Path::Tiny ();

our $x = 1;

sub callback { $x++; };

subtest 'same interp' => sub {

    my $interp = $ffi->function( interp_new_from_perl => ['opaque'] => 'opaque' )->call(undef);
    $ffi->function( interp_call_sub_0 => ['opaque', 'string'] => 'void' )->call($interp, "callback");
    $ffi->function( interp_free => ['opaque'] => 'void' )->call($interp);

    is $x, 2;

    $interp = $ffi->function( interp_new_from_perl => ['opaque'] => 'opaque' )->call(undef);
    $ffi->function( interp_call_sub_0 => ['opaque', 'string'] => 'void' )->call($interp, "callback");
    $ffi->function( interp_free => ['opaque'] => 'void' )->call($interp);

    is $x, 3;

};

subtest 'another interp' => sub {

    skip_all 'requires multiplicity' unless $Config{usemultiplicity};

    my $temp = Path::Tiny->tempfile;
    $temp->spew_utf8('sub callback { $x++; }');

    my @args = (
        $0, "$temp",
    );

    my $interp = $ffi->function( interp_new => ['int','string[]'] => 'opaque' )->call(scalar(@args), \@args);

    $ffi->function( interp_run => ['opaque'] => 'void' )->call($interp);
    $ffi->function( interp_call_sub_0 => ['opaque', 'string'] => 'void' )->call($interp, "callback");
    $ffi->function( interp_free => ['opaque'] => 'void' )->call($interp);

    is $x, 3;

};

$ffi->function( DONE => [] => 'void' )->call;

done_testing;
