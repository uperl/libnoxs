use 5.020;
use warnings;
use FFI::Platypus 2.00;

sub foo {
    FFI::Platypus->new(api => 2, lib => [undef])
        ->function( ok4 => ['int', 'string', 'string', 'int'] => 'int' )
        ->call(1, "from inside perl", __FILE__, __LINE__);
}

FFI::Platypus->new(api => 2, lib => [undef])
    ->function( ok4 => ['int', 'string', 'string', 'int'] => 'int' )
    ->call(0, "from inside perl", __FILE__, __LINE__);
