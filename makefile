P = lul
CFLAGS = -Wall -g
INCLUDE = -I ./src
LDFLAGS =  -L ./src
LDLIBS = -lncurses -lgc
CC = clang

t: 
	make -C test	

watch:
	find . -name '*.[c|h]' | entr -c make t

clean: 
	rm ./src/*.o 
	rm test/test
	rm lul
