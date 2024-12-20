#ifndef TAP_H
#define TAP_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void plan(unsigned int total);
int ok4(int pass, const char *name, const char *file, unsigned int line);
int is5(const char *got, const char *expected, const char *name, const char *file, unsigned int line);
void diag(const char *format, ...);
void note(const char *format, ...);
void tap_bump();
int tap_count();

#define ok(pass, name)            ok4(pass, name,          __FILE__, __LINE__)
#define is(got, expected, name)   is5(got, expected, name, __FILE__, __LINE__)

#endif
