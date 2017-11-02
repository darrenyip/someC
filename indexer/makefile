CC = gcc
CFLAGS = -g
OBJECTS = main.o creates.o browses.o list.o


indexer: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o indexer

%.o: %.c
	$(CC) $(CFLAGS) -c $<