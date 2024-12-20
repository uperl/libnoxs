use Test2::V0;
use lib 't/lib';
use TestNOXS;
use Config;
use Path::Tiny ();
use Data::Section::Pluggable;
use File::chdir;

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

subtest 'another interp' => sub {

    skip_all 'requires multiplicity' unless $Config{usemultiplicity};

    my $temp = Path::Tiny->tempdir;

    Data::Section::Pluggable->new->extract("$temp");

    {
        local $CWD = $temp;
        my @args = ($0, "another.pl");

        my $interp = $ffi->function( interp_new => ['int','string[]'] => 'opaque' )->call(scalar(@args), \@args);

        is($ffi->function( interp_is_valid => ['opaque'] => 'int' )->call($interp), 1);
        is($ffi->function( interp_is_embeded => ['opaque'] => 'int' )->call($interp), 0);

        $ffi->function( interp_run => ['opaque'] => 'void' )->call($interp);
        $ffi->function( interp_call_sub_0 => ['opaque', 'string'] => 'void' )->call($interp, "callback");
        #$ffi->function( interp_free => ['opaque'] => 'void' )->call($interp);

    }

    is $x, 3;

};

#$ffi->function( DONE => [] => 'void' )->call;

done_testing;

__DATA__

@@ another.pl
use strict;
use warnings;

our $x=1;
sub callback { $x++ }