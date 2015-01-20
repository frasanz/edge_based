CXX=g++
CC=gcc
DEFS=-Wall -g
LIBS=-lm
                      
all: edge_based
edge_based: edge_based.c memory.o initialize.o screen.o
	$(CC) $(DEFS) edge_based.c initialize.o memory.o screen.o -o edge_based  $(LIBS)

memory.o: memory.c
	$(CC) $(DEFS) -c memory.c -o memory.o $(LIBS)

initialize.o: initialize.c
	$(CC) $(DEFS) -c initialize.c -o initialize.o $(LIBS)

screen.o: screen.c
	$(CC) $(DEFS) -c screen.c -o screen.o $(LIBS)
                                                                                     
clean:                                                                               
	rm -f *.o edge_based
