CC = gcc
CFLAGS = -g
OBJECTS = main.o creates.o browses.o invertIndex.o mystrtok.o Record.o sortedList.o


indexer: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o indexer

%.o: %.c
	$(CC) $(CFLAGS) -c $<