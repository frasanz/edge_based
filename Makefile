CXX=g++
CC=gcc
DEFS=-Wall -g
LIBS=-lm
                      
all: edge_based
edge_based: edge_based.c memory.o initialize.o 
	$(CC) $(DEFS) initialize.o memory.o edge_based.c -o edge_based  $(LIBS)                                 

memory.o: memory.c
	$(CC) $(DEFS) -c memory.c -o memory.o $(LIBS)

initialize.o: initialize.c
	$(CC) $(DEFS) -c initialize.c -o initialize.o $(LIBS)
                                                                                     
clean:                                                                               
	rm -f *.o edge_based
