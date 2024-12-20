#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void plan(unsigned int total);
void ok4(int pass, const char *name, const char *file, unsigned int line);
void bump();

static const char *tap_file;
static int tap_line;

#define ok(pass, name) ok4(pass, name, __FILE__, __LINE__)
#define is(_g, _e, name) { tap_file = __FILE__; tap_line = __LINE__;       \
    const char *got = _g;                                                  \
    const char *expected = _e;                                             \
    int pass = strcmp(got,expected) == 0;                                  \
    ok4(pass, name, tap_file, tap_line);                                   \
    if(!pass) {                                                            \
        fprintf(stderr, "# got \"%s\" expected \"%s\"\n", got, expected);  \
        fflush(stderr);                                                    \
    }                                                                      \
}

