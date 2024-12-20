include ../config

LIBOBJ=interp.o
libnoxs.a: $(LIBOBJ)
	$(AR) rc libnoxs.a $(LIBOBJ)
	$(RANLIB) libnoxs.a

libnoxs.so: $(LIBOBJ)
	$(LD) -shared -o libnoxs.so $(PERL_LDFLAGS) $(LDFLAGS)

%.o: %.c noxs_xs.h noxs_impl.h ../include/noxs.h
	$(CC) -c -o $@ $(PERL_CFLAGS) $(CFLAGS) $*.c

.PHONY: clean
clean:
	rm -rf *.o libnoxs.a libnoxs.so*
