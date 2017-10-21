CC = gcc
CFLAGS = -g
OBJECTS = main.o archFunct.o handler.o computeSize.o

archiver: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o archiver

%.o: %.c
	$(CC) $(CFLAGS) -c $<