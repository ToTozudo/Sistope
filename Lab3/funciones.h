#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
Definición de la estructura "celdas" que representa una celda con su número (celda) y su energía.
*/
typedef struct celdas
{
    int celda;
    float energia = 0;
} celdas;

/*
Declaración de la función "lectura_particulas" que lee datos de un archivo de entrada.
Entrada: Nombre del archivo de entrada (filename).
Salida: Matriz dinámica de enteros que contiene información sobre partículas y su energía.
*/
void *particulas(void *hebra);

/*
Declaración de la función "archivo_salida" que escribe resultados en un archivo de salida.
Entrada: Arreglo de celdas de resultados, celda con mayor energía, cantidad de celdas, nombre del archivo de salida.
Salida: Ninguna, los resultados se escriben en un archivo.
*/
void archivo_salida(char* filename);

/*
Declaración de la función "energia_celdas" que calcula la energía de cada celda en función de los datos de las partículas.
Entrada: Matriz de datos con partículas y sus energías, cantidad de celdas.
Salida: Arreglo de celdas con energías calculadas.
*/
void energia_celdas(int particula, float energia);

/*
Declaración de la función "mayor_energia" que encuentra la celda con la mayor energía en un arreglo de celdas registradas.
Entrada: Arreglo de celdas registradas, cantidad de celdas.
Salida: Celda con la mayor energía.
*/
celdas mayor_energia();

/*
Declaración de la función "normalizacion" que normaliza valores de energía en función de una celda con mayor energía.
Entrada: Arreglo de celdas con energías, celda con mayor energía, N (número máximo de caracteres), MAX_CHAR (máximo valor de caracteres).
Salida: Arreglo de valores normalizados.
*/
int* normalizacion(int MAX_CHAR);

/*
Declaración de la función "liberar" que libera la memoria asignada dinámicamente para celdas de datos registrados y la matriz de partículas.
Entrada: Arreglo de celdas de datos registrados y matriz de partículas.
Salida: Ninguna, libera la memoria.
*/
void liberar();
