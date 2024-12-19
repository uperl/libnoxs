#include <EXTERN.h>
#include <perl.h>
#include <noxs.h>
#include <noxs_xs.h>
#include <stdlib.h>
#include <string.h>

// see environ(7)
extern char **environ;

struct noxs_interp {
    PerlInterpreter *perl;
    int is_valid;
    int is_embeded;
    int argc;
    char **argv;
    noxs_interp *next;
};

typedef enum {
    INIT_REQUIRED,
    EMBEDED,
    TERM_REQUIRED,
    DONE
} status_t;

status_t status = INIT_REQUIRED;

noxs_interp *top = NULL;
void noxs_DONE()
{
    while(top != NULL) {
        noxs_interp *self = top;
        top = self->next;
        noxs_interp_free(self);
        free(self);
    }
    if(status == TERM_REQUIRED) {
        PERL_SYS_TERM();
    }
    status = DONE;
}

/*
 * This should be called from Perl, if interpreters
 * are being created FROM another Perl, and will
 * prevent libnoxs from calling PERL_SYS_INIT
 * or PERL_SYS_TERM
 */
void
noxs_SET_EMBEDED()
{
    if(status == INIT_REQUIRED)
    {
        status = EMBEDED;
    }
}

noxs_interp *
noxs_interp_new(int argc, char **argv)
{
    if(status == DONE) {
        return NULL;
    }

    noxs_interp *self = malloc(sizeof(noxs_interp));

    self->is_embeded = 0;
    self->argc = argc;
    self->argv = calloc(sizeof(char*), self->argc);
    for(int i=0; i<argc; i++) {
        self->argv[i] = strdup(argv[i]);
    }
    self->next = top;
    top = self;

    if(status == INIT_REQUIRED) {
        PERL_SYS_INIT3(&self->argc, &self->argv, &environ);
        status = TERM_REQUIRED;
        atexit(noxs_DONE);
    }

    /*
     * NOTE: PL_exit_flags needs the perl interpreter
     * to be called my_perl, so we create a duplicate
     * pointer with that name here
     */
    PerlInterpreter *my_perl = self->perl = perl_alloc();
    perl_construct(self->perl);

    PL_exit_flags |= PERL_EXIT_DESTRUCT_END;

    self->is_valid = 1;

    return self;
}

noxs_interp*
noxs_interp_new_from_perl(void *perl)
{
    noxs_interp *self = malloc(sizeof(noxs_interp));

    self->is_embeded = 1;
    self->argc = 0;
    self->argv = NULL;
    self->perl = (PerlInterpreter*)perl;
    self->is_valid = 1;

    return 0;
}

void
noxs_interp_parse(noxs_interp *self)
{
    if(self->is_valid) {
        perl_parse(self->perl, NULL, self->argc, self->argv, (char **)NULL);
    }
}

void
noxs_interp_call_sub_0(noxs_interp *self, const char *subname)
{
    if(self->is_valid) {
        static char *args[] = { NULL };
        noxs_xs_call_argv(self->perl, subname, G_DISCARD | G_NOARGS, args);
    }
}

void
noxs_interp_run(noxs_interp *self)
{
    if(self->is_valid && !self->is_embeded) {
        int ret = perl_run(self->perl);
        if(ret != 0) {
            noxs_interp_destruct(self);
        }
    }
}

int
noxs_interp_is_valid(noxs_interp *self)
{
    return self->is_valid;
}

int
noxs_interp_is_embeded(noxs_interp *self)
{
    return self->is_embeded;
}

void
noxs_interp_destruct(noxs_interp *self)
{
    if(self->is_embeded) {
        return;
    }
    if(self->is_valid) {
        perl_destruct(self->perl);
        self->is_valid = 0;
    }
}

void
noxs_interp_free(noxs_interp *self)
{
    if(self->is_embeded) {
        free(self);
        return;
    }
    if(self->perl != NULL) {
        noxs_interp_destruct(self);
        perl_free(self->perl);
        PERL_SYS_TERM();
        self->perl = NULL;
    }
    if(self->argv != NULL) {
        for(int i=0; i<self->argc; i++) {
            free(self->argv[i]);
        }
        free(self->argv);
        self->argv = NULL;
    }
}
