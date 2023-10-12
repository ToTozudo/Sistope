#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <getopt.h>
#include "funciones.h"

int MAX_CHAR= 35;

int main(int argc, char *argv[])
{
    /*Ejemplo ejecucion: 
    ./lab1 -N 5 -i input.txt -o output.txt -D
    */
    int opt;
    int N = 1;
    char* inputFilename = NULL;
    char* outputFilename = NULL;
    int D_flag = 0;

    while ((opt = getopt(argc, argv, "N:i:o:D")) != -1) {
        switch (opt) {
            case 'N':
                N = atoi(optarg);
                break;
            case 'i':
                inputFilename = optarg;
                break;
            case 'o':
                outputFilename = optarg;
                break;
            case 'D':
                D_flag = 1;
                break;
            case '?':
                // Manejar opciones desconocidas o faltantes
                fprintf(stderr, "Opcion desconocida o argumento faltante: -%c\n", optopt);
                return 1;
            default:
                // Esto no debería suceder
                fprintf(stderr, "Error inesperado\n");
                return 1;
        }
    }

    //Verificacion de parametros
    if (N <= 0 || inputFilename == NULL || outputFilename == NULL) {
        fprintf(stderr, "Faltan opciones requeridas, o el numero de celdas es invalido.\n");
        return 1;
    }

    int** datos = lectura_particulas(inputFilename);
    celdas* registroDatos = energia_celdas(datos, N);
    celdas celdaEnergizada = mayor_energia(registroDatos, N);
    archivo_salida(registroDatos, celdaEnergizada, N, outputFilename);
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
    }
    
    return 0;
}
