#include <tap.h>

static int count = 1;

void
plan(unsigned int total)
{
    printf("1..%d\n", total);
    fflush(stdout);
}

void
done_testing()
{
    plan(count-1);
}

static
const char *format_string(const char *format)
{
    static char *f = NULL;

    if(f != NULL) {
        free(f);
    }

    if(format == NULL) {
        f = NULL;
    }

    int len = strlen(format)+4;
    f = calloc(sizeof(const char), len+1);
    snprintf(f, len, "# %s\n", format);
    return f;
}

void
diag(const char *format, ...)
{
    va_list aptr;
    va_start(aptr, format);
    vfprintf(stderr, format_string(format), aptr);
    fflush(stderr);
    va_end(aptr);
}

void
note(const char *format, ...)
{
    va_list aptr;
    va_start(aptr, format);
    vprintf(format_string(format), aptr);
    fflush(stdout);
    va_end(aptr);
}

int
ok4(int pass, const char *name, const char *file, unsigned int line)
{
    if(pass) {
        printf("ok %d - %s\n", count++, name);
        fflush(stdout);
    } else {
        printf("not ok %d - %s\n", count++, name);
        fflush(stdout);
        diag("test failure at %s line %d", file, line);
    }

    return pass;
}

int
is5(const char *got, const char *expected, const char *name, const char *file, unsigned int line)
{
    int pass = strcmp(got,expected) == 0;
    ok4(pass, name, file, line);
    if(!pass) {
        diag("got \"%s\" expected \"%s\"", got, expected);
    }
}

void
tap_bump()
{
    count++;
}

int
tap_count()
{
    return count;
}
