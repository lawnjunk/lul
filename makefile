P = main
CFLAGS = -Wall -g
INCLUDE = -I $(PWD)/src
OBJECTS = $(PWD)/src/*.c
LDFLAGS =  -L $(PWD)/src
LDLIBS = -lncurses -lgc
CC = clang

$(P):
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -o $@  $@.c $(OBJECTS) $(LDLIBS)

#all: 
	#clang ${CFLAGS} ${INCLUDE} main.c  -o lul ${OBJECTS} ${LIBS} && ./lul

debug: 
	clang ${CFLAGS} ${INCLUDE} main.c  -o lul ${OBJECTS} ${LIBS} 

