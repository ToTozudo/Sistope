#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>


int MAX_CHAR = 35;  // Valor máximo de caracteres en el gráfico

int main(int argc, char *argv[])
{
    int opt;
    char* N = "1";  // Número de celdas por defecto
    char* inputFilename = NULL;  // Nombre del archivo de entrada
    char* outputFilename = NULL;  // Nombre del archivo de salida
    char* workers= NULL;
    char* chunks= NULL;
    char D_flag = "0";  // Bandera para habilitar la salida gráfica

    // Procesar las opciones de la línea de comandos
    while ((opt = getopt(argc, argv, "N:P:i:o:c:D")) != -1) {
        switch (opt) {
            case 'N':
                N = optarg;  // Establecer el número de celdas
                break;
            case 'P':
                workers=optarg;
                break;
            case 'i':
                inputFilename = optarg;  // Establecer el nombre del archivo de entrada
                break;
            case 'o':
                outputFilename = optarg;  // Establecer el nombre del archivo de salida
                break;
            case 'c':
                chunks=optarg;
                break;
            case 'D':
                D_flag = '1';  // Activar la salida gráfica
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
    if (atoi(N) <= 0 || inputFilename == NULL || outputFilename == NULL || workers == NULL || chunks == NULL) {
        fprintf(stderr, "Faltan opciones requeridas o el número de celdas es inválido, asegurese de que sea positivo.\n");
        return 1;
    }
    //Creamos el pipe
    int fd[2];
    if (pipe(fd) == -1)
    {
        printf("Error al crear pipe.\n");
        return 1;
    }
    //Creamos el fork
    int id = fork();
    if (id == -1)
    {
        printf("Error en el fork.\n");
        return 2;
    }else if (id == 0)//proceso hijo
    {
        close(fd[0]);

        dup2(fd[1], STDOUT_FILENO);

        char* argvNew[] = {"./broker", N, inputFilename, outputFilename, workers, chunks, D_flag, NULL};
        execv(argvNew[0],argvNew);
    }
    
    
    
    

    return 0;
}
