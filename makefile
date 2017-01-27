P = lul
CFLAGS = -Wall -g
INCLUDE = -I $(PWD)/src
OBJECTS = $(PWD)/src/*.c
LDFLAGS =  -L $(PWD)/src
LDLIBS = -lncurses -lgc
CC = clang

all:
	$(CC) $(CFLAGS) $(INCLUDE) $(LDFLAGS) -o lul main.c $(OBJECTS) $(LDLIBS)

dbug:
	$(CC) -D DEBUG $(CFLAGS) $(INCLUDE) $(LDFLAGS) -o lul main.c $(OBJECTS) $(LDLIBS)

t: 
	make -C test	

watch:
	find . -name '*.[c|h]' | entr -c make t
