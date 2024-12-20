include ../config

all: libnoxs.a noxs.so

LIBOBJ=interp.o config.o
libnoxs.a: $(LIBOBJ)
	$(AR) rc libnoxs.a $(LIBOBJ)
	$(RANLIB) libnoxs.a

noxs.so: $(LIBOBJ)
	$(LD) -shared -o noxs.so $(LIBOBJ)

%.o: %.c noxs_xs.h noxs_impl.h ../include/noxs.h
	$(CC) -c -o $@ $(PERL_CFLAGS) $(CFLAGS) $*.c

.PHONY: clean
clean:
	rm -rf *.o libnoxs.a noxs.so*
