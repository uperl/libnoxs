#include <tap.h>

void
plan(unsigned int total)
{
    printf("1..%d\n", total);
    fflush(stdout);
}

static int count = 1;

void
ok4(int pass, const char *name, const char *file, unsigned int line)
{
    if(pass) {
        printf("ok %d\n", count++);
        fflush(stdout);
    } else {
        printf("not ok %d\n", count++);
        fflush(stdout);
        fprintf(stderr, "# test failure at %s line %d\n", file, line);
    }
}

void
bump()
{
    count++;
}
