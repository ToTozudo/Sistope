#include "./funciones.h"
#include <math.h>
#include <stdlib.h>

extern FILE *inputFile;
extern int chunk, nHebras, cParticulas, cCeldas;
extern int* particulasEmitidas;
extern pthread_mutex_t mutex;
extern celdas* celdasEnergizadas;
/*
Función de lectura de archivo de entrada
Entrada: Nombre del archivo de entrada
Salida: Matriz con las partículas y su respectiva energía
Lógica: Se busca el archivo con el nombre proporcionado, se analiza el primer número en el archivo
        que representa la cantidad de partículas a leer. Luego, se inicializa una matriz con el 
        número recién leído, se reserva memoria para almacenar la posición de la partícula y su energía.
*/
void* particulas(void* args){
    
    while(1){
        pthread_mutex_lock(&mutex);
        if (feof(archivoEntrada)) {  // Verificar si ya se llegó al final del archivo
            pthread_mutex_unlock(&mutex);// Se sale de la sección crítica
            break;
        }
        int particula;
        float energia;
        for(int i = 0; i < chunk ; i++){
            fscanf(file, "%d %d", &particula, &energia);
            energia_celdas(particula,energia);
        }
    }
    
    return NULL;
};

/*
Función para escribir resultados en un archivo de salida
Entrada: Arreglo de celdas de resultados, celda con mayor energía, cantidad de celdas, nombre del archivo de salida
Salida: Ninguna, los resultados se escriben en un archivo
Lógica: Abre el archivo de salida, escribe la celda con la mayor energía y luego las demás celdas con sus respectivas energías.
*/
void archivo_salida(celdas* resultadosCeldas, celdas mostEnergy, int cantidadCeldas, char* filename){
    FILE* file = fopen(filename, "w");
    if (file == NULL){
        fprintf(stderr, "No se pudo abrir el archivo.");
        fclose(file);
    }
    fprintf(file, "%d %.6lf\n", mostEnergy.celda, mostEnergy.energia);
    for (int i = 0; i < cantidadCeldas; i++)
    {
        fprintf(file, "%d %.6lf\n", resultadosCeldas[i].celda, resultadosCeldas[i].energia);
    }
    fclose(file);
};

/*
Función para calcular la energía entre dos celdas
Entrada: Índices de dos celdas, número de celdas, y energía EJ
Salida: Valor de energía calculado
Lógica: Calcula la energía entre dos celdas según la fórmula proporcionada y la devuelve como resultado.
*/
float energia_j_i(int i, int j, int n, int eJ){
    float resultado = (pow(10, 3) * eJ) / (n * (sqrt(abs(j - i) + 1)));
    // printf("\t%d :: %.4lf\n", i, resultado);
    return resultado;
}

/*
Función para calcular las energías de las celdas
Entrada: Matriz de datos con partículas y sus energías, cantidad de celdas
Salida: Arreglo de celdas con energías calculadas
Lógica: Calcula la energía de todas las celdas según la posición de las partículas y las energías de las partículas.
*/
float energia_celdas(int particula, float energia){
    float MIN_ENERGY = pow(10, -3) / cCeldas;

    for (int i = 0; i < cCeldas; i++)
    {
        celdasEnergizadas[i].celda = i;
        celdasEnergizadas[i].energia = 0;
        for (int j = 1; j <= cantidadParticulas; j++)
        {
            float energiaParcial = energia_j_i(i, datos[j][0], cantidadCeldas, datos[j][1]);
            if (energiaParcial >= MIN_ENERGY){
                celdasResultantes[i].energia += energiaParcial;
            }
        }
    }
    return celdasResultantes;
}

/*
Función para encontrar la celda con mayor energía
Entrada: Arreglo de celdas registradas, cantidad de celdas
Salida: Celda con la mayor energía
Lógica: Recorre el arreglo de celdas registradas y encuentra la celda con la mayor energía.
*/
celdas mayor_energia(celdas* celdasRegistradas, int cantidadCeldas){
    celdas mayorEnergia;
    mayorEnergia.energia = 0;
    for (int i = 0; i < cantidadCeldas; i++){
        if (celdasRegistradas[i].energia > mayorEnergia.energia){
            mayorEnergia.celda = i;
            mayorEnergia.energia = celdasRegistradas[i].energia;
        }
    }
    return mayorEnergia;
}

/*
Función para normalizar los valores de energía
Entrada: Arreglo de celdas con energías, celda con mayor energía, N (número máximo de caracteres), y MAX_CHAR (máximo valor de caracteres)
Salida: Arreglo de valores normalizados
Lógica: Normaliza los valores de energía en el rango [0, MAX_CHAR] en función de la celda con mayor energía.
*/
int* normalizacion(celdas* resultadoCeldas, celdas mostEnergy, int N, int MAX_CHAR){
    int* normalizado = (int*) malloc(N * sizeof(int));
    for (int i = 0; i < N; i++){
        normalizado[i] = round((resultadoCeldas[i].energia / mostEnergy.energia) * MAX_CHAR);
    }
    return normalizado;
}

/*
Función para liberar la memoria asignada dinámicamente
Entrada: Arreglo de celdas de datos registrados y matriz de partículas
Salida: Ninguna, libera la memoria
Lógica: Libera la memoria asignada para las celdas de datos registrados y la matriz de partículas.
*/
void liberar(celdas* datosRegistrados, int** particulas){
    int cParticulas = particulas[0][0];
    free(datosRegistrados);

    for (int i = 1; i <= cParticulas; i++)
    {
        free(particulas[i]);
    }
    free(particulas);
}