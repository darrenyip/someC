CC = gcc
CFLAGS = -g
OBJECTS = main.o functionA.o functionB.o

mylogger: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o mylogger

%.o: %.c
	$(CC) $(CFLAGS) -c $<