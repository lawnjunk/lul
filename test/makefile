CFLAGS = -Wall
INCLUDE = -I ../src/ -I ./
SOURCE = ../src/flub.c ../src/buffer.c ../src/line.c ../src/doc.c
LIBS = -lgc

t: build 
	./tests
	rm ./tests

build: 
	clang $(CFLAGS) ${INCLUDE} test.c ${SOURCE} ${LIBS} -o tests

debug: 
	clang -D DEBUG ${CFLAGS} ${INCLUDE} test.c ${SOURCE} ${LIBS} -o tests
	./tests
	rm ./tests

quiet: 
	clang -D NO_TEST_LOG ${CFLAGS} ${INCLUDE} test.c ${SOURCE} ${LIBS} -o tests
	./tests
	rm ./tests

