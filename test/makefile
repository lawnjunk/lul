CFLAGS = -Wall
INCLUDE = -I ../src -I .
SOURCE = ../src/*.c
LIBS = -lgc


run: build 
	./tests
	rm ./tests
	
build: 
	clang ${CFLAGS} ${INCLUDE} test.c ${SOURCE} ${LIBS} -o tests
