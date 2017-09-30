CC = gcc
CFLAGS = -g
OBJECTS = main.o insert.o print.o

sample: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o sample
main.o: main.c
	$(CC) $(CFLAGS) -c main.c
insert.o: insert.c
	$(CC) $(CFLAGS) -c insert.c
print.c: print.o
	$(CC) $(CFLAGS) -c print.c