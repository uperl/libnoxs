#include <noxs.h>
#include <tap.h>

int
main(int argc, char **argv, char **env)
{
    int test_count;
    noxs_interp *interp1 = NULL;

    int perl_argc = 2;
    char *perl_argv[2] = { argv[0], "t/c/multiplicity.pl" };

    interp1 = noxs_interp_new(perl_argc, perl_argv);
    ok(interp1 != NULL, "created first interp");

    ok(noxs_interp_is_valid(interp1) == 1, ".is_valid = 1");
    ok(noxs_interp_is_embeded(interp1) == 0, ".is_embeded = 0");

    if(noxs_config_multiplicity()) {

        noxs_interp *interp2 = NULL;

        interp2 = noxs_interp_new(perl_argc, perl_argv);
        ok(interp2 != NULL, "created second interp");

        noxs_interp_set_context(interp1);
        noxs_interp_run(interp1);
        noxs_interp_set_context(interp2);
        noxs_interp_run(interp2);

        noxs_interp_free(interp2);

    } else {

        ok(noxs_interp_new(perl_argc, perl_argv) == NULL, "second interp returns NULL");
        noxs_interp_run(interp1);

        is(noxs_error(), "Perl does not have multiplicity", "expected error");
    }

    noxs_interp_set_context(interp1);
    noxs_interp_free(interp1);

    done_testing();

    exit(EXIT_SUCCESS);
}
