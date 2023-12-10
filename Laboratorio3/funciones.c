// funciones.c
// Implementación de funciones auxiliares para procesar partículas y manejar archivos.

#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>

float celdas[MAX_CELDAS];
pthread_mutex_t mutex;

// Procesa una partícula y distribuye su energía entre las celdas correspondientes
// Descripción: Esta función toma una partícula y distribuye su energía entre las celdas del material.
// Tipo de Dato: void
// Entrada: particula (Particula*), numCeldas (int)
// Salida: None (void)
void procesarParticula(Particula *particula, int numCeldas)
{
    distribuirEnergia(*particula, celdas, numCeldas);
}

// Lee un archivo de entrada y almacena la información de las partículas
// Descripción: Abre y lee un archivo de entrada, extrayendo el número de partículas, el número de celdas y los datos de cada partícula.
// Tipo de Dato: void
// Entrada: nombreArchivo (const char*), particulas (Particula[]), numParticulas (int*), numCeldas (int*)
// Salida: None (void)
void leerArchivoEntrada(const char *nombreArchivo, Particula particulas[], int *numParticulas, int *numCeldas)
{
    FILE *archivo = fopen(nombreArchivo, "r");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo de entrada");
        exit(1);
    }

    if (fscanf(archivo, "%d %d", numParticulas, numCeldas) != 2 || *numCeldas > MAX_CELDAS || *numParticulas > MAX_PARTICULAS)
    {
        fprintf(stderr, "Error en el formato del archivo de entrada\n");
        exit(1);
    }

    for (int i = 0; i < *numParticulas; ++i)
    {
        int pos;
        float energia;
        if (fscanf(archivo, "%d %f", &pos, &energia) != 2)
        {
            fprintf(stderr, "Error en el formato del archivo de entrada en la línea %d\n", i + 2);
            exit(1);
        }
        particulas[i] = crearParticula(pos, energia);
    }
    fclose(archivo);
}

// Escribe los resultados en un archivo de salida
// Descripción: Abre y escribe en un archivo de salida, registrando la energía acumulada en cada celda.
// Tipo de Dato: void
// Entrada: nombreArchivo (const char*), celdas (float[]), numCeldas (int)
// Salida: None (void)
void escribirArchivoSalida(const char *nombreArchivo, float celdas[], int numCeldas)
{
    FILE *archivo = fopen(nombreArchivo, "w");
    if (archivo == NULL)
    {
        perror("Error al abrir el archivo de salida");
        exit(1);
    }

    for (int i = 0; i < numCeldas; ++i)
    {
        fprintf(archivo, "%d: %f\n", i, celdas[i]);
    }
    fclose(archivo);
}
