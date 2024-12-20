include config

.PHONY: all clean

all:
	make -C lib
	make -C t/c

clean:
	make -C lib clean
	make -C t/c clean

test: all
	$(PROVE) -r

vt: all
	$(PROVE) -rvm
