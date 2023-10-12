CFLAGS = -Wall
LDFLAGS = -lm

main: lab1.c funciones.o
	gcc $(CFLAGS) -o lab1 lab1.c funciones.o $(LDFLAGS)

funciones.o: funciones.c funciones.h
	gcc -c $(CFLAGS) funciones.c

clear:
	rm -f lab1 *.o

