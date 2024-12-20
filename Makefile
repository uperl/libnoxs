.PHONY: all clean

all:
	make -C lib
	make -C t

clean:
	make -C lib clean
	make -C t clean

test: all
	prove
