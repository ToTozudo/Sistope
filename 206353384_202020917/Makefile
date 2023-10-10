FLAGS = -Wall -lm

main: main.c funciones.o
		gcc $(FLAGS) -o main main.c funciones.o

funciones.o: funciones.c
		gcc -c $(FLAGS) funciones.c

clear:
		rm -f main *.o