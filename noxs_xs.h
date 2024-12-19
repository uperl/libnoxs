#ifndef NOXS_XS_H
#define NOXS_XS_H

#ifdef MULTIPLICITY
#define noxs_xs_call_argv(perl, subname, flags, args) Perl_call_argv(perl, subname, flags, args)
#else
#define noxs_xs_call_argv(perl, subname, flags, args) Perl_call_argv(subname, flags, args)
#endif

#endif
