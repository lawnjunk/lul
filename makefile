CFLAGS = -Wall -g
LIBS = -lncurses

all: 
	clang ${CFLAGS} main.c ${LIBS} -o lul && ./lul

debug:
	clang ${CFLAGS} main.c ${LIBS} -o lul

