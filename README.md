# libnoxs ![linux](https://github.com/uperl/libnoxs/workflows/linux/badge.svg)

> [!WARNING]
> This is a work in progress, mostly incomplete (it does work on my machine though lol)

This library "libnoxs" (pronounced nock-sis) is a wrapper around the Perl API.
Why not just use the Perl API directly?  Well that is a great option if you
happen to be working in C where the C pre-processor is available, and you have
the ten thousand hours or flight XS training required for safety, but a lot of
people don't have this.

This will allow languages like [Rust](https://www.rust-lang.org/) when called
from Perl ([see](https://metacpan.org/pod/FFI::Platypus::Lang::Rust)) to more
efficiently work with native Perl data structures.  There are probably other
applications as well.
