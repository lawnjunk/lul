P = test
LIBS = 
CFLAGS = -Wall -g -ftest-coverage -fprofile-arcs
INCLUDE = -I ../src/ -I ./
OBJECTS = ../src/flub.o ../src/buffer.o \
					../src/line.o ../src/doc.o \
					../src/cursor.o

# build and run tests
t: b
	./$(P)

# build the object deps and the $(P)
b: $(OBJECTS) 
	clang $(CFLAGS) ${INCLUDE} test.c $(OBJECTS) ${LIBS} -o $(P)

debug: $(OBJECTS)
	clang -D DEBUG ${CFLAGS} ${INCLUDE} test.c ${OBJECTS} ${LIBS} -o $(P)
	./$(P)

quiet: $(OBJECTS)
	clang -D NO_TEST_LOG ${CFLAGS} ${INCLUDE} test.c ${OBJECTS} ${LIBS} -o $(P)
	./$(P)
