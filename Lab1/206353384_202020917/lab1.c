#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "funciones.h"

int MAX_CHAR = 35;  // Valor máximo de caracteres en el gráfico

int main(int argc, char *argv[])
{
    int opt;
    int N = 1;  // Número de celdas por defecto
    char* inputFilename = NULL;  // Nombre del archivo de entrada
    char* outputFilename = NULL;  // Nombre del archivo de salida
    int D_flag = 0;  // Bandera para habilitar la salida gráfica

    // Procesar las opciones de la línea de comandos
    while ((opt = getopt(argc, argv, "N:i:o:D")) != -1) {
        switch (opt) {
            case 'N':
                N = atoi(optarg);  // Establecer el número de celdas
                break;
            case 'i':
                inputFilename = optarg;  // Establecer el nombre del archivo de entrada
                break;
            case 'o':
                outputFilename = optarg;  // Establecer el nombre del archivo de salida
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
    if (N <= 0 || inputFilename == NULL || outputFilename == NULL) {
        fprintf(stderr, "Faltan opciones requeridas o el número de celdas es inválido, asegurese de que sea positivo.\n");
        return 1;
    }

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

    return 0;
}
