P = run_test 
LIBS = 
CFLAGS = -Wall -g --coverage -O0
INCLUDE = -I ./src/ -I ./test
OBJECTS = ./src/flub.o ./src/buffer.o \
					./src/line.o ./src/doc.o \
					./src/cursor.o

# build and run tests
t: b
	./$(P)

# build the object deps and the $(P)
b: $(OBJECTS) 
	clang $(CFLAGS) ${INCLUDE} test.c $(OBJECTS) ${LIBS} -o $(P)

watch:
	find . -name '*.[c|h]' | entr -c make t

cover: t
	coveralls -t ${COVERALLS_REPO_TOKEN}


clean: 
	- rm ./src/*.o  
	- rm ./src/*.gc* 
	- rm ./*.gc* 
	- rm ./test/*.gc* 
	- rm test/test 
	- rm lul 
	- rm run_test
