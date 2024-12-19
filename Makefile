PERL=perl
CC=gcc
LD=gcc
PERL_CFLAGS=$(shell perl -MExtUtils::Embed -e ccopts)
CFLAGS=-I. -fPIC
PERL_LDFLAGS=$(shell perl -MExtUtils::Embed -e ldopts)
LDFLAGS=

main: main.o interp.o
	$(CC) -o main $(PERL_CFLAGS) $(CFLAGS) main.c interp.c $(PERL_LDFLAGS) $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $(PERL_CFLAGS) $(CFLAGS) $*.c

.PHONY: clean
clean:
	rm -rf *.o main
