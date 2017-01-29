P = test
CFLAGS = -Wall -g 
INCLUDE = -I ../src/ -I ./
OBJECTS = ../src/flub.o ../src/buffer.o ../src/line.o ../src/doc.o ../src/cursor.o
LIBS = 

# make run 
t: b
	./$(P)

b: $(OBJECTS) 
	clang $(CFLAGS) ${INCLUDE} test.c $(OBJECTS) ${LIBS} -o $(P)

$@: 
	clang $(CFLAGS) $(INCLUDE)  -o $@ $*.c $(LIBS)

debug: $(OBJECTS)
	clang -D DEBUG ${CFLAGS} ${INCLUDE} test.c ${OBJECTS} ${LIBS} -o $(P)
	./$(P)

quiet: $(OBJECTS)
	clang -D NO_TEST_LOG ${CFLAGS} ${INCLUDE} test.c ${OBJECTS} ${LIBS} -o $(P)
	./$(P)

