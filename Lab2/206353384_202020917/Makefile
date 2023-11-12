CFLAGS = -Wall
LDFLAGS = -lm

main: lab2.c funciones.o
	gcc $(CFLAGS) -o lab2 lab2.c funciones.o $(LDFLAGS)

funciones.o: funciones.c funciones.h
	gcc -c $(CFLAGS) funciones.c

clear:
	rm -f lab2 *.o

