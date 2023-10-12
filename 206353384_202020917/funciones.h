#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/**/
typedef struct celdas
{
    int celda;
    double energia;
}celdas;

int** lectura_particulas(char* filename);
void archivo_salida(celdas* resultadosCeldas, celdas mostEnergy, int cantidadCeldas, char* filename);
celdas* energia_celdas(int** datos, int cantidadCeldas);
celdas mayor_energia(celdas* celdasRegistradas, int cantidadCeldas);
int* normalizacion(celdas* resultadoCeldas, celdas mostEnergy, int N, int MAX_CHAR);
void liberar(celdas* datosRegistrados, int** particulas);