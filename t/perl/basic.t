use Test2::V0;
use experimental qw( signatures );
use FFI::Platypus 2.00;

skip_all 'borked';

my $lib = './lib/noxs.so';
my $ffi = FFI::Platypus->new( api => 2, lib => $lib );
$ffi->mangler(sub ($sym) { "noxs_$sym" });

$ffi->function( SET_EMBEDED => [] => 'void' )->call;

our $x = 1;

sub callback { $x = 2; };

my $interp = $ffi->function( interp_new_from_perl => ['opaque'] => 'opaque' )->call(undef);
$ffi->function( interp_call_sub_0 => ['opaque', 'string'] => 'void' )->call($interp, "callback");

$ffi->function( DONE => [] => 'void' )->call;

is $x, 2;

done_testing;
