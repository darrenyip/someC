CC = gcc
CFLAGS = -g
OBJECTS = main.o insert.o print.o

prog: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o prog
%.o: %.c
	$(CC) $(CFLAGS) -c $<