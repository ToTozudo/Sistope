# Makefile

CC=gcc
CFLAGS=-pthread -Wall

all: lab3

lab3: lab3.c funciones.c particula.c
	$(CC) $(CFLAGS) -o lab3 lab3.c funciones.c particula.c

clean:
	rm -f lab3
