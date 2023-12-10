// particula.h
// Definición y operaciones para el TDA Particula

#ifndef PARTICULA_H
#define PARTICULA_H

// Estructura de Partícula
// Descripción: Define una estructura para representar una partícula, incluyendo su posición de impacto y energía.
// Tipo de Dato: struct
// Entrada: No aplica (definición de estructura)
// Salida: No aplica (definición de estructura)
typedef struct
{
    int posicion;  // Posición de impacto de la partícula
    float energia; // Energía de la partícula
} Particula;

// Crea y retorna una nueva partícula
// Descripción: Inicializa y retorna una estructura Particula con una posición y energía específicas.
// Tipo de Dato: Particula
// Entrada: posicion (int) - la posición de la partícula,
//          energia (float) - la energía de la partícula.
// Salida: Particula - una nueva instancia de Particula.
Particula crearParticula(int posicion, float energia);

// Distribuye la energía de una partícula en un arreglo de celdas
// Descripción: Distribuye la energía de una partícula dada entre su celda de impacto y las celdas adyacentes.
// Tipo de Dato: void
// Entrada: particula (Particula) - la partícula cuya energía se va a distribuir,
//          celdas (float[]) - un arreglo que representa las celdas del material,
//          numCeldas (int) - el número total de celdas en el arreglo.
// Salida: None (void)
void distribuirEnergia(Particula particula, float celdas[], int numCeldas);

#endif
