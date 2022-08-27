CC = gcc
CFLAGS = -g -D DEBUG

libraries = individual.c population.c
objects   = *.o

.DEFAULT_GOAL := install

library: $(libraries)
	$(CC) $(CFLAGS) -c $(libraries)

install: library
	$(CC) $(CFLAGS) main.c $(objects) -o main.out 