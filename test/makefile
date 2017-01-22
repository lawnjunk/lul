CFLAGS = -Wall
INCLUDE = -I ../src/ -I ./
SOURCE = ../src/lerr.c ../src/buffer.c
LIBS = -lgc

run: build 
	./tests
	rm ./tests
	
build: 
	clang ${CFLAGS} ${INCLUDE} test.c ${SOURCE} ${LIBS} -o tests
