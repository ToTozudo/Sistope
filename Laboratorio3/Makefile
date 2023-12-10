# Makefile

CC=gcc
CFLAGS=-pthread -Wall

# Compila el programa principal
all: particulas

# Regla para compilar el programa principal
particulas: particulas.c funciones.c particula.c
	$(CC) $(CFLAGS) -o particulas particulas.c funciones.c particula.c

# Regla para limpiar archivos compilados
clean:
	rm -f particulas
