libraries = individual.c
objects   = *.o

.DEFAULT_GOAL := install

library: $(libraries)
	gcc -c $(libraries)

install: library
	gcc -o main.out main.c $(objects)