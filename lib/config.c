#include <EXTERN.h>
#include <perl.h>
#include <noxs.h>

int
noxs_config_multiplicity()
{
#ifdef MULTIPLICITY
    return 1;
#else
    return 0;
#endif
}
