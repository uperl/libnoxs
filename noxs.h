#ifndef NOXS_H
#define NOXS_H

#ifdef __cplusplus
extern "C" {
#endif

typedef struct noxs_interp noxs_interp;

noxs_interp *noxs_interp_new(int argc, char **argv);
noxs_interp *noxs_interp_new_from_perl(void *perl);
void         noxs_interp_parse(noxs_interp *self);
void         noxs_interp_run(noxs_interp *self);
void         noxs_interp_call_sub_0(noxs_interp *self, const char *subname);
int          noxs_interp_is_valid(noxs_interp *self);
int          noxs_interp_is_embeded(noxs_interp *self);
void         noxs_interp_destruct(noxs_interp *self);
void         noxs_interp_free(noxs_interp *self);

#ifdef __cplusplus
}
#endif

#endif
