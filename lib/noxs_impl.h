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

#endif
