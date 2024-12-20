include ../../config

all: libtap.a

LIBOBJ=tap.o
libtap.a: $(LIBOBJ)
	$(AR) rc libtap.a $(LIBOBJ)
	$(RANLIB) libtap.a

%.o: %.c tap.h
	$(CC) -c -o $@ $(PERL_CFLAGS) $(CFLAGS) $*.c

.PHONY: clean
clean:
	rm -rf *.o libtap.a
