#include <noxs.h>
#include <tap.h>

int
main(int argc, char **argv, char **env)
{
    int perl_argc = 2;
    char *perl_argv[2] = { argv[0], "t/c/basic.pl" };

    plan(1);

    noxs_interp *myperl = noxs_interp_new(perl_argc, perl_argv);
    noxs_interp_call_sub_0(myperl, "foo");
    noxs_interp_free(myperl);

    exit(EXIT_SUCCESS);
}
