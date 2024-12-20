PERL=perl
CC=gcc
LD=gcc
PERL_CFLAGS=$(shell perl -MExtUtils::Embed -e ccopts)
CFLAGS=-I../include -fPIC
PERL_LDFLAGS=$(shell perl -MExtUtils::Embed -e ldopts)
LDFLAGS=-L../lib -lnoxs
AR=ar
RANLIB=ranlib

EXEOBJ=main.o
main: $(EXEOBJ)
	$(CC) -o main $(EXEOBJ) $(LDFLAGS) $(PERL_LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $(PERL_CFLAGS) $(CFLAGS) $*.c

.PHONY: clean
clean:
	rm -rf *.o main
