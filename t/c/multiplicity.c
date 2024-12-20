#include <noxs.h>
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char **argv, char **env)
{
    if(noxs_config_multiplicity()) {
        noxs_interp *interp1 = NULL;
        noxs_interp *interp2 = NULL;

        printf("1..4\n");
        fflush(stdout);

        {
            int perl_argc = 3;
            char *perl_argv[3] = { argv[0], "t/c/multiplicity.pl", "3" };

            interp1 = noxs_interp_new(perl_argc, perl_argv);

            if(interp1 != NULL) {
                printf("ok 1\n");
                fflush(stdout);
            }
        }

        {
            int perl_argc = 3;
            char *perl_argv[3] = { argv[0], "t/c/multiplicity.pl", "4" };

            interp2 = noxs_interp_new(perl_argc, perl_argv);

            if(interp2 != NULL) {
                printf("ok 2\n");
                fflush(stdout);
            }
        }

        noxs_interp_run(interp1);
        noxs_interp_run(interp2);

        noxs_interp_free(interp2);
        noxs_interp_free(interp1);

    } else {
        // TODO: test handling of trying to create a second interp
        // when no multiplicity.
        printf("1..0 # SKIP Perl not built with multiplicity\n");
    }

    exit(EXIT_SUCCESS);
}
