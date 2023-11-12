#include "funciones.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main (int argc, char *argv[]){

    
    // Leer datos de partículas desde el archivo de entrada
    int** datos = lectura_particulas(inputFilename);

    // Calcular la energía de las celdas
    celdas* registroDatos = energia_celdas(datos, N);

    // Encontrar la celda con mayor energía
    celdas celdaEnergizada = mayor_energia(registroDatos, N);

    // Escribir los resultados en un archivo de salida
    archivo_salida(registroDatos, celdaEnergizada, N, outputFilename);

    // Si la bandera D está habilitada, generar y mostrar una representación gráfica
    if (D_flag)
    {
        int* grafico = normalizacion(registroDatos, celdaEnergizada, N, MAX_CHAR);
        for (int i = 0; i < N; i++)
        {
            printf("%d\t%.4lf  |", i, registroDatos[i].energia);
            for (int j = 0; j < grafico[i]; j++)
            {
                printf("o");
            }
            printf("\n");
        }
        free(grafico);
    }

    // Liberar memoria asignada dinámicamente
    liberar(registroDatos, datos);
}