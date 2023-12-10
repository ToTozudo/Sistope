CFLAGS = -Wall
LDFLAGS = -lm

main: lab3.c funciones.o
	gcc $(CFLAGS) -o lab3 lab3.c funciones.o $(LDFLAGS)

funciones.o: funciones.c funciones.h
	gcc -c $(CFLAGS) funciones.c

clear:
	rm -f lab3 *.o

