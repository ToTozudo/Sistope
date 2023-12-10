// particulas.c
// Punto de entrada principal del programa para la simulación de distribución de energía de partículas.

#include "funciones.h"
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Función principal del programa
// Descripción: Inicializa el programa, procesa los argumentos de línea de comandos con getopt, crea hebras para cada partícula y gestiona la distribución de su energía.
// Tipo de Dato: int
// Entrada: argc (int) - número de argumentos de línea de comandos,
//          argv (char*[]) - arreglo de argumentos de línea de comandos.
// Salida: int - estado de salida del programa (0 para éxito).
int main(int argc, char *argv[])
{
    int opt;
    char *inputFile = NULL;
    char *outputFile = NULL;

    // Procesa los argumentos de línea de comandos usando getopt
    while ((opt = getopt(argc, argv, "i:o:")) != -1)
    {
        switch (opt)
        {
        case 'i':
            inputFile = optarg;
            break;
        case 'o':
            outputFile = optarg;
            break;
        default:
            fprintf(stderr, "Uso: %s -i <archivo_entrada> -o <archivo_salida>\n", argv[0]);
            exit(EXIT_FAILURE);
        }
    }

    // Verifica si se proporcionaron los archivos de entrada y salida
    if (!inputFile || !outputFile)
    {
        fprintf(stderr, "Se requieren los argumentos -i y -o.\n");
        exit(EXIT_FAILURE);
    }

    pthread_t threads[MAX_PARTICULAS];
    Particula particulas[MAX_PARTICULAS];
    int numParticulas, numCeldas;

    // Inicializa el mutex para la sincronización
    pthread_mutex_init(&mutex, NULL);

    // Abre el archivo de entrada y crea hebras para procesar cada partícula
    FILE *archivo = fopen(inputFile, "r");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo de entrada");
        exit(EXIT_FAILURE);
    }

    if (fscanf(archivo, "%d %d", &numParticulas, &numCeldas) != 2 || numCeldas > MAX_CELDAS || numParticulas > MAX_PARTICULAS)
    {
        fprintf(stderr, "Error en el formato del archivo de entrada\n");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < numParticulas; ++i)
    {
        int pos;
        float energia;
        if (fscanf(archivo, "%d %f", &pos, &energia) != 2)
        {
            fprintf(stderr, "Error en el formato del archivo de entrada en la línea %d\n", i + 2);
            exit(EXIT_FAILURE);
        }
        particulas[i] = crearParticula(pos, energia);
        pthread_create(&threads[i], NULL, (void *(*)(void *))procesarParticula, (void *)&particulas[i]);
    }

    fclose(archivo);

    // Espera a que todas las hebras terminen
    for (int i = 0; i < numParticulas; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    // Escribe los resultados en el archivo de salida
    escribirArchivoSalida(outputFile, celdas, numCeldas);

    // Libera los recursos del mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
