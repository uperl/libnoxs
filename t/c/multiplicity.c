#include <noxs.h>
#include <tap.h>

int
main(int argc, char **argv, char **env)
{
    int test_count;
    noxs_interp *interp1 = NULL;

    plan(4);

    {
        int perl_argc = 3;
        char *perl_argv[3] = { argv[0], "t/c/multiplicity.pl", "3" };
        interp1 = noxs_interp_new(perl_argc, perl_argv);
        ok(interp1 != NULL, "created first interp");
    }

    if(noxs_config_multiplicity()) {

        noxs_interp *interp2 = NULL;

        {
            int perl_argc = 3;
            char *perl_argv[3] = { argv[0], "t/c/multiplicity.pl", "4" };

            interp2 = noxs_interp_new(perl_argc, perl_argv);
            ok(interp2 != NULL, "created second interp");
        }

        noxs_interp_run(interp1);
        bump();
        noxs_interp_run(interp2);
        bump();

        noxs_interp_free(interp2);

    } else {

        ok(noxs_interp_new(0, NULL) == NULL, "second interp returns NULL");
        noxs_interp_run(interp1);
        bump();

        is(noxs_error(), "Perl does not have multiplicity", "expected error");
    }

    noxs_interp_free(interp1);

    exit(EXIT_SUCCESS);
}
