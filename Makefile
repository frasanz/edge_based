CXX=g++
CC=gcc
DEFS=-Wall -g
LIBS=-lm
                      
all: edged_based
edged_based: edged_based.c memory.o initialize.o 
	$(CC) $(DEFS) initialize.o memory.o edged_based.c -o edged_based  $(LIBS)                                 

memory.o: memory.c
	$(CC) $(DEFS) -c memory.c -o memory.o $(LIBS)

initialize.o: initialize.c
	$(CC) $(DEFS) -c initialize.c -o initialize.o $(LIBS)
                                                                                     
clean:                                                                               
	rm -f *.o edged_based
