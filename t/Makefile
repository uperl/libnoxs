include ../config
LDFLAGS=-L../lib -lnoxs

.PHONY: all
all: basic.t xs.t

%.t: %.c ../lib/libnoxs.a
	$(LD) -o $@ $(PERL_CFLAGS) $(CFLAGS) $*.c $(LDFLAGS) $(PERL_LDFLAGS)

.PHONY: clean
clean:
	rm -rf *.o *.t
