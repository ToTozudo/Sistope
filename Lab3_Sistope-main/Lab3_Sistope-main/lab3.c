#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <unistd.h>
#include "funciones.h"

//Declaración de variables globales
int chunk; 
int numHebras;
TDAlista* listaPrincipal;
FILE *archivoEntrada;
pthread_mutex_t mutex; // Declaración del mutex global



//Entradas: argc, argv
//Salida: 0 si se ejecuta correctamente
//Descripción: Función principal del programa, se encarga de leer los argumentos de entrada,
// y llamar a las funciones necesarias para realizar el programa
int main(int argc, char *argv[]){
	char* entrada = NULL;
	char* salida = NULL;
	int auxEntrada = 0, auxSalida = 0, auxHebra = 0, auxChunk = 0;
	int option, b = 0;
	while((option = getopt(argc, argv, "i:o:n:c:b")) != -1){
		switch(option){
			case 'i':
				entrada = optarg;
				auxEntrada = 1;
				break;
			case 'o':
				salida = optarg;
				auxSalida = 1;
				break;
			case 'n':
				numHebras = atoi(optarg);
				auxHebra = 1;
				break;
			case 'c':
				chunk = atoi(optarg);
				auxChunk = 1;
				break;
			case 'b':
				b = 1;
				break;
		}
	}
	if (auxEntrada == 0 || auxSalida == 0 || auxHebra == 0 || auxChunk == 0){
		printf("No se ingreso alguno de los campos obligatorios\n");
		return 0;
	}
	if (numHebras <= 0){
		printf("cantidad de hebras invalidas\n");
		return 0;
	}
	if (chunk <= 0){
		printf("tamaño de chunk invalido\n");
		return 0;
	}
	//Se crea la lista global que contendrá los datos.
	listaPrincipal = crearListaVacia();
	archivoEntrada = fopen(entrada, "r");  // Se abre el archivo de entrada en modo lectura

 	if (archivoEntrada == NULL){  // Si el archivo no existe.
    	printf("No se pudo abrir archivo\n"); // Se imprime un mensaje de error
    	exit(0);  // Se termina la ejecución
	}
	
	pthread_t arrayHebras[numHebras];  // Se reserva memoria para el arreglo de hebras
	pthread_mutex_init(&mutex, NULL); // Se inicializa el mutex

	for (int tid = 0; tid < numHebras; tid++){ // Se crean las hebras
		pthread_create(&arrayHebras[tid], NULL, hebras, NULL);
	}

	for(int tid = 0; tid < numHebras;tid++){  // Se espera que cada hebra termine de ejecutarse
		pthread_join(arrayHebras[tid], NULL);
	}
	//Se cierra el archivo de entrada, ya que no se volverá a ocupar
	fclose(archivoEntrada);
	//Se escribe en el archivo de salida, los datos resultantes
	escribirArchivoSalida(listaPrincipal, salida);
	//Si se entrega el flag "-b", se imprimen los calculos de la evaluación
	if(b)
	{
		imprimirCalculos(listaPrincipal);
	}
	//Se destruye el mutex inicializado anteriormente
	pthread_mutex_destroy(&mutex);
	return 0;
}
