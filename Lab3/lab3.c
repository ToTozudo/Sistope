#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <pthread.h>
#include "funciones.h"

//Declaración variables globales
int MAX_CHAR = 35;  // Valor máximo de caracteres en el gráfico
int chunk, nHebras, cParticulas, cCeldas;
int* lHebras;
FILE *inputFile;
pthread_mutex_t mutex;
celdas* celdasEnergizadas;

int main(int argc, char *argv[])
{
    int opt, D_flag = 0;  // banderas del opt, Número de celdas por defecto, Numero de hebras, tamaño del chunk, y bandera de salida grafica
    char* inputFilename = NULL;  // Nombre del archivo de entrada
    char* outputFilename = NULL;  // Nombre del archivo de salida

    // Procesar las opciones de la línea de comandos
    while ((opt = getopt(argc, argv, "N:H:i:o:c:D")) != -1) {
        switch (opt) {
            case 'N':
                cCeldas = atoi(optarg);  // Establecer el número de celdas
                break;
            case 'H':
                nHebras = atoi(optarg); // Establecer cantidad de hebras
                break;
            case 'i':
                inputFilename = optarg;  // Establecer el nombre del archivo de entrada
                break;
            case 'o':
                outputFilename = optarg;  // Establecer el nombre del archivo de salida
                break;
            case 'c':
                chunk = atoi(optarg); // Establecer tamaño del chunk
                break;
            case 'D':
                D_flag = 1;  // Activar la salida gráfica
                break;
            case '?':
                // Manejar opciones desconocidas o faltantes
                fprintf(stderr, "Opción desconocida o argumento faltante: -%c\n", optopt);
                return 1;
            default:
                // Esto no debería suceder
                fprintf(stderr, "Error inesperado\n");
                return 1;
        }
    }

    // Verificación de los parámetros de entrada
    if (cCeldas <= 0 || nHebras <=0 || inputFilename == NULL || outputFilename == NULL || chunk <= 0) {
        fprintf(stderr, "Faltan opciones requeridas o el numero de celdas, de hebras o el tamaño del chunk, es invalido.\nAsegurese de que ha ingresado los parametros correctamente, o que los valores ingresados para la cantidad de celdas,\nnumero de hebras, y/o el tamaño del chunk sea positivo y mayor a 0.\n");
        return 1;
    }

    celdasEnergizadas = (celdas*) malloc(sizeof(celdas)*cCeldas);
    inputFile = fopen(inputFilename, "r");

    if (inputFile == NULL)
    {
        fprintf(stderr, "No se pudo abrir el archivo\n");
        return 2;
    }

    fscanf(inputFile, "%d", &cParticulas);
    if (cParticulas < 0) {
        fprintf(stderr, "Error al leer el número de partículas. No puede haber una cantidad negativa.\n");
    }

    pthread_t arrayHebras[nHebras];  // Se reserva memoria para el arreglo de hebras
	pthread_mutex_init(&mutex, NULL); // Se inicializa el mutex

    for (int tid = 0; tid < nHebras; tid++){ // Se crean las hebras
		int * arg= malloc(sizeof(*arg));
        *arg=tid;
        pthread_create(&arrayHebras[tid], NULL, particulas, arg);
        lHebras = (int*) malloc(nHebras * sizeof(int));
        lHebras[tid] = 0; //cuantas lineas a leido
	}

	for(int tid = 0; tid < nHebras; tid++){  // Se espera que cada hebra termine de ejecutarse
		pthread_join(arrayHebras[tid], NULL);
	}
	//Se cierra el archivo de entrada, ya que no se volverá a ocupar
	fclose(inputFile);

    // Escribir los resultados en un archivo de salida
    archivo_salida(outputFilename);

    // Si la bandera D está habilitada, generar y mostrar una representación gráfica
    if (D_flag)
    {
        int* grafico = normalizacion(MAX_CHAR);
        for (int i = 0; i < cCeldas; i++)
        {
            printf("%d\t%.4lf  |", i, celdasEnergizadas[i].energia);
            for (int j = 0; j < grafico[i]; j++)
            {
                printf("o");
            }
            printf("\n");
        }
        free(grafico);
        printf("Cantidad de lineas leidas por hebra:\n");
        for(int tid = 0; tid<nHebras; tid++){
            printf("Hebra %d: %d lineas leidas correctamente\n", tid, lHebras[tid]);
        }
    }

    // Liberar memoria asignada dinámicamente
    liberar();
    pthread_mutex_destroy(&mutex);

    return 0;
}
