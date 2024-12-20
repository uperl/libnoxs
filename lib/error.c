#include <EXTERN.h>
#include <perl.h>
#include <noxs.h>
#include <noxs_impl.h>

int noxs_error_needs_free = 0;
char *noxs_error_string = "";

const char *
noxs_error() {
    return noxs_error_string;
}
