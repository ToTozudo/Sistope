// funciones.h
// Declaraciones de funciones auxiliares para manejo de partículas y archivos

#ifndef FUNCIONES_H
#define FUNCIONES_H

#include "particula.h"
#include <pthread.h>

#define MAX_CELDAS 1000     // Máximo número de celdas permitidas
#define MAX_PARTICULAS 1000 // Máximo número de partículas permitidas

// Arreglo global para almacenar la energía acumulada en cada celda
extern float celdas[MAX_CELDAS];

// Mutex para sincronizar el acceso al arreglo celdas
extern pthread_mutex_t mutex;

// Procesa una partícula y distribuye su energía entre las celdas correspondientes
// Descripción: Toma una referencia a una partícula y el número total de celdas y llama a la función para distribuir su energía.
// Tipo de Dato: void
// Entrada: particula (Particula*), numCeldas (int) - número total de celdas en el arreglo
// Salida: None (void)
void procesarParticula(Particula *particula, int numCeldas);

// Lee un archivo de entrada y almacena la información de partículas
// Descripción: Abre un archivo de entrada, lee y almacena la cantidad de partículas, la cantidad de celdas y los datos de cada partícula.
// Tipo de Dato: void
// Entrada: nombreArchivo (const char*) - nombre del archivo de entrada,
//          particulas (Particula[]) - arreglo de partículas para almacenar los datos,
//          numParticulas (int*) - apuntador al número total de partículas,
//          numCeldas (int*) - apuntador al número total de celdas.
// Salida: None (void)
void leerArchivoEntrada(const char *nombreArchivo, Particula particulas[], int *numParticulas, int *numCeldas);

// Escribe los resultados en un archivo de salida
// Descripción: Abre un archivo de salida y escribe la energía acumulada en cada celda.
// Tipo de Dato: void
// Entrada: nombreArchivo (const char*) - nombre del archivo de salida,
//          celdas (float[]) - arreglo con la energía acumulada en cada celda,
//          numCeldas (int) - número total de celdas en el arreglo.
// Salida: None (void)
void escribirArchivoSalida(const char *nombreArchivo, float celdas[], int numCeldas);

#endif
