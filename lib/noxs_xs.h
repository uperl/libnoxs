#ifndef NOXS_XS_H
#define NOXS_XS_H

#ifdef MULTIPLICITY
#define noxs_xs_call_argv(perl, subname, flags, args) Perl_call_argv(perl, subname, flags, args)
#define noxs_xs_eval_pv(perl, s, croak) Perl_eval_pv(perl, s, croak);
#else
#define noxs_xs_call_argv(perl, subname, flags, args) Perl_call_argv(subname, flags, args)
#define noxs_xs_eval_pv(perl, s, croak) Perl_eval_pv(s, croak);
#endif

#endif
