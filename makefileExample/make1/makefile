.SUFFIXES: .c .o
CC = gcc

CFLAGS = -g

.c.o:
	$(CC) $(CFLAGS) -c $<

sample: main.o funct.o
	gcc main.o funct.o -o sample
	
main.o: globals.h

funct.o: externs.h

clean:
	rm -f *.o core
