

lab3: lab3.c funciones.o
	gcc lab3.c funciones.o -o lab3 -lm -pthread -Wall

funciones.o: funciones.c funciones.h TDAlista.h
	gcc -c funciones.c
	

clean:	# Elimina ejecutable, archivo de salida y .o's
	rm -f *.o lab3 salida.txt

