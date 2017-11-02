CC = gcc
CFLAGS = -g
OBJECTS = main.o recorder.o menu.o

flightRecorder: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o flightRecorder

%.o: %.c
	$(CC) $(CFLAGS) -c $<