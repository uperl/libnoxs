use warnings;
use 5.020;
use experimental qw( signatures );
use true;

package TestNOXS {

    use Exporter qw( import );
    use FFI::Platypus 2.00;

    our @EXPORT = qw( $ffi );

    my $lib = './lib/noxs.so';
    our $ffi = FFI::Platypus->new( api => 2, lib => $lib );
    $ffi->mangler(sub ($sym) { "noxs_$sym" });

    $ffi->function( SET_EMBEDED => [] => 'void' )->call;

}
