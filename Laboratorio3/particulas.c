// particulas.c
// Punto de entrada principal del programa para la simulación de distribución de energía de partículas

#include "funciones.h"
#include <pthread.h>
#include <stdio.h>

// Función principal del programa
// Descripción: Inicializa el programa, procesa los argumentos de entrada, crea hebras para cada partícula y gestiona la distribución de su energía.
// Tipo de Dato: int
// Entrada: argc (int) - número de argumentos de línea de comandos,
//          argv (char*[]) - arreglo de argumentos de línea de comandos.
// Salida: int - estado de salida del programa (0 para éxito).
int main(int argc, char *argv[])
{
    // Verifica el número correcto de argumentos
    if (argc != 3)
    {
        fprintf(stderr, "Uso: %s <archivo_entrada> <archivo_salida>\n", argv[0]);
        exit(1);
    }

    // Arreglo para hebras y particulas
    pthread_t threads[MAX_PARTICULAS];
    Particula particulas[MAX_PARTICULAS];
    int numParticulas, numCeldas;

    // Lee el archivo de entrada y llena el arreglo de particulas
    leerArchivoEntrada(argv[1], particulas, &numParticulas, &numCeldas);

    // Inicializa el mutex para la sincronización
    pthread_mutex_init(&mutex, NULL);

    // Crea hebras para procesar cada partícula
    for (int i = 0; i < numParticulas; ++i)
    {
        pthread_create(&threads[i], NULL, (void *(*)(void *))procesarParticula, (void *)&particulas[i]);
    }

    // Espera a que todas las hebras terminen
    for (int i = 0; i < numParticulas; ++i)
    {
        pthread_join(threads[i], NULL);
    }

    // Escribe los resultados en el archivo de salida
    escribirArchivoSalida(argv[2], celdas, numCeldas);

    // Libera los recursos del mutex
    pthread_mutex_destroy(&mutex);

    return 0;
}
