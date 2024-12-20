include ../../config
LDFLAGS=-L../../lib -lnoxs -L../lib -ltap

C_FILES=$(wildcard *.c)
T_FILES=$(subst .c,.t, $(C_FILES))

.PHONY: all
all: $(T_FILES)

%.t: %.c ../../lib/libnoxs.a ../lib/libtap.a
	$(LD) -o $@ $(PERL_CFLAGS) $(CFLAGS) $*.c $(LDFLAGS) $(PERL_LDFLAGS)

.PHONY: clean
clean:
	rm -rf *.o *.t
