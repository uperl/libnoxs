PERL=perl
CC=gcc
LD=gcc
PERL_CFLAGS=$(shell perl -MExtUtils::Embed -e ccopts)
CFLAGS=-I../include -I. -fPIC
PERL_LDFLAGS=$(shell perl -MExtUtils::Embed -e ldopts)
LDFLAGS=
AR=ar
RANLIB=ranlib

LIBOBJ=interp.o
libnoxs.a: $(LIBOBJ)
	$(AR) rc libnoxs.a $(LIBOBJ)
	$(RANLIB) libnoxs.a

libnoxs.so: $(LIBOBJ)
	$(LD) -shared -o libnoxs.so $(PERL_LDFLAGS) $(LDFLAGS)

%.o: %.c
	$(CC) -c -o $@ $(PERL_CFLAGS) $(CFLAGS) $*.c

.PHONY: clean
clean:
	rm -rf *.o libnoxs.a libnoxs.so*
