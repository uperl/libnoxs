#ifndef NOXS_IMPL_H
#define NOXS_IMPL_H

struct noxs_interp {
    PerlInterpreter *perl;
    int is_valid;
    int is_embeded;
    int argc;
    char **argv;
    noxs_interp *next;
};

extern int noxs_error_needs_free;
extern char *noxs_error_string;

#define noxs_error_set(s) if(noxs_error_needs_free) {     \
                              free(noxs_error_string);    \
                              noxs_error_string = s;      \
                              noxs_error_needs_free = 0;  \
                          } else {                        \
                              noxs_error_string = s;      \
                              noxs_error_needs_free = 0;  \
                          }

#endif
