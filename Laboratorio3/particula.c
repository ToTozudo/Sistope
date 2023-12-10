// particula.c
// Implementación de operaciones para el TDA Particula

#include "particula.h"
#include <pthread.h>
#include <stdio.h>

extern pthread_mutex_t mutex;

// Crea y retorna una nueva partícula con la posición y energía especificadas
// Descripción: Inicializa una estructura de Partícula con los valores dados para posición y energía.
// Tipo de Dato: Particula
// Entrada: posicion (int) - posición de impacto de la partícula,
//          energia (float) - cantidad de energía de la partícula.
// Salida: Particula - una nueva instancia de Particula con los valores especificados.
Particula crearParticula(int posicion, float energia)
{
    Particula p;
    p.posicion = posicion;
    p.energia = energia;
    return p;
}

// Distribuye la energía de una partícula en el arreglo de celdas
// Descripción: Distribuye la energía de una partícula entre su celda de impacto y las celdas adyacentes.
// Tipo de Dato: void
// Entrada: particula (Particula) - la partícula cuya energía se va a distribuir,
//          celdas (float[]) - arreglo que representa las celdas del material,
//          numCeldas (int) - número total de celdas en el arreglo.
// Salida: None (void)
void distribuirEnergia(Particula particula, float celdas[], int numCeldas)
{
    if (particula.posicion < 0 || particula.posicion >= numCeldas)
    {
        return; // Posición fuera de los límites del material
    }

    pthread_mutex_lock(&mutex);
    // Distribución de energía: igualmente entre la celda de impacto y las adyacentes
    int inicio = particula.posicion > 0 ? particula.posicion - 1 : particula.posicion;
    int fin = particula.posicion < numCeldas - 1 ? particula.posicion + 1 : particula.posicion;
    int celdas_afectadas = fin - inicio + 1;
    float energia_distribuida = particula.energia / celdas_afectadas;

    for (int i = inicio; i <= fin; i++)
    {
        celdas[i] += energia_distribuida;
    }
    pthread_mutex_unlock(&mutex);
}
