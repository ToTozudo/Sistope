#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "funciones.h"

int main(int argc, char const *argv[])
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
    return 0;
}
