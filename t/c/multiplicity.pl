use 5.020;
use warnings;
use FFI::Platypus 2.00;

FFI::Platypus->new(api => 2, lib => [undef])
  ->function( ok4 => ['int', 'string', 'string', 'int'] => 'int' )
  ->call(1, "from inside perl", __FILE__, __LINE__);
