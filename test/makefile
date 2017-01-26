CFLAGS = -Wall
INCLUDE = -I ../src/ -I ./
SOURCE = ./flub_test.c ../src/flub.c ../src/buffer.c ../src/line.c
LIBS = -lgc

run: build 
	./tests
	rm ./tests
	
build: 
	clang ${CFLAGS} ${INCLUDE} test.c ${SOURCE} ${LIBS} -o tests
