FLAGS = -Wall -lm

main: lab1.c funciones.o
		gcc $(FLAGS) -o main lab1.c funciones.o

funciones.o: funciones.c
		gcc -c $(FLAGS) funciones.c

clear:
		rm -f main *.o