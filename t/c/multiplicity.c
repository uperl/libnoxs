#include <noxs.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int
main(int argc, char **argv, char **env)
{
    int test_count;
    noxs_interp *interp1 = NULL;

    if(noxs_config_multiplicity()) {
        test_count = 4;
    } else {
        test_count = 4;
    }

    printf("1..%d\n", test_count);
    fflush(stdout);

    {
        int perl_argc = 3;
        char *perl_argv[3] = { argv[0], "t/c/multiplicity.pl", "3" };

        interp1 = noxs_interp_new(perl_argc, perl_argv);

        if(interp1 != NULL) {
            printf("ok 1\n");
            fflush(stdout);
        } else {
            printf("not ok 1\n");
            fflush(stdout);
        }
    }

    if(noxs_config_multiplicity()) {

        noxs_interp *interp2 = NULL;

        {
            int perl_argc = 3;
            char *perl_argv[3] = { argv[0], "t/c/multiplicity.pl", "4" };

            interp2 = noxs_interp_new(perl_argc, perl_argv);

            if(interp2 != NULL) {
                printf("ok 2\n");
                fflush(stdout);
            } else {
                printf("not ok 2\n");
                fflush(stdout);
            }
        }

        noxs_interp_run(interp1);
        noxs_interp_run(interp2);

        noxs_interp_free(interp2);

    } else {

        int perl_argc = 3;
        char *perl_argv[3] = { argv[0], "t/c/multiplicity.pl", "4" };

        if(noxs_interp_new(perl_argc, perl_argv) == NULL) {
                printf("ok 2\n");
                fflush(stdout);
            } else {
                printf("not ok 2\n");
                fflush(stdout);
        }

        noxs_interp_run(interp1);

        const char *got = noxs_error();
        const char *expected = "Perl does not have multiplicity";

        if(strcmp(got, expected)) {
            printf("not ok 4\n");
            fflush(stdout);
            fprintf(stderr, "# error did not match, got \"%s\" expected \"%s\"\n", got, expected);
            fflush(stderr);
        } else {
            printf("ok 4\n");
            fflush(stdout);
        }

    }

    noxs_interp_free(interp1);

    exit(EXIT_SUCCESS);
}
