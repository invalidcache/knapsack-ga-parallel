CC = gcc
CFLAGS = -g3 -fopenmp

libraries = individual.c population.c knapsack.c file_util.c
objects   = *.o

.DEFAULT_GOAL := install

library: $(libraries)
	$(CC) $(CFLAGS) -c $(libraries)

install: library
	$(CC) $(CFLAGS) main.c $(objects) -o main.out

clean:
	rm *.o *.out