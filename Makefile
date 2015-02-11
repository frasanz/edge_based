CXX=g++
CC=gcc
DEFS=-Wall -g
LIBS=-lm
                      
all: edge_based
edge_based: edge_based.c memory.o initialize.o screen.o test.o initialize_operator.o \
	module.o smoothers.o defect.o restrict.o
	$(CC) $(DEFS) edge_based.c initialize.o memory.o screen.o test.o \
		initialize_operator.o module.o smoothers.o defect.o restrict.o \
		-o edge_based  $(LIBS)

memory.o: memory.c
	$(CC) $(DEFS) -c memory.c -o memory.o $(LIBS)

initialize.o: initialize.c
	$(CC) $(DEFS) -c initialize.c -o initialize.o $(LIBS)

screen.o: screen.c
	$(CC) $(DEFS) -c screen.c -o screen.o $(LIBS)

test.o: test.c
	$(CC) $(DEFS) -c test.c -o test.o $(LIBS)

initialize_operator.o: initialize_operator.c
	$(CC) $(DEFS) -c initialize_operator.c -o initialize_operator.o $(LIBS)

module.o: module.c
	$(CC) $(DEFS) -c module.c -o module.o $(LIBS)

smoothers.o: smoothers.c
	$(CC) $(DEFS) -c smoothers.c -o smoothers.o $(LIBS)

defect.o: defect.c
	$(CC) $(DEFS) -c defect.c -o defect.o $(LIBS)

restrict.o: restrict.c
	$(CC) $(DEFS) -c restrict.c -o restrict.o $(LIBS)
                                                                                     
clean:                                                                               
	rm -f *.o edge_based
