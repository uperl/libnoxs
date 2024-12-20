#include <noxs.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv, char **env)
{
    int perl_argc = 2;
    char *perl_argv[2] = { argv[0], "t/c/xs.pl" };

    noxs_interp *myperl = noxs_interp_new(perl_argc, perl_argv);
    noxs_interp_run(myperl);
    noxs_interp_free(myperl);

    exit(EXIT_SUCCESS);
}
