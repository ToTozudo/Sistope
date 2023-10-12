#include "./funciones.h"



/*
Funcion de lectura archivo de entrada
Entrada: Nombre del archivo de entrada
Salida: Matriz con las particulas y su respectiva energia
Lógica: Se busca el archivo con el nombre detectado, se analiza el primer numero del archivo
        que será la cantidad de particulas a leer, luego se inicializa un arreglo con el 
        numero recien leido, se aloja la memoria para recibir la posicion de la particula, y
        su energia
*/
int** lectura_particulas(char* filename){
    FILE* file = fopen(filename,"r");
    if (file==NULL){
        fprintf(stderr,"Error al abrir el archivo");
        fclose(file);
        return NULL;
    }

    int cParticulas;
    fscanf(file,"%d",&cParticulas);
    if (cParticulas < 0) {
        fclose(file);
        fprintf(stderr, "Error al leer el numero de particulas. No puede haber una cantidad negativa.\n");
        return NULL;
    }

    int** particulas= (int**) malloc((cParticulas+1)*sizeof(int*));
    if (particulas == NULL) {
        fclose(file);
        fprintf(stderr, "Error de asignacion de memoria.\n");
        return NULL;
    }

    particulas[0]    = (int*) calloc(1,sizeof(int));
    if (particulas[0] == NULL) {
        fclose(file);
        free(particulas);
        fprintf(stderr, "Error de asignacion de memoria.\n");
        return NULL;
    }
    particulas[0][0] = cParticulas;

    for(int i=1; i<cParticulas+1; i++){
        particulas[i] = (int*) malloc(sizeof(int)*2);

        if (particulas[i] == NULL) {

            fclose(file);

            for (int j = 0; j < i; j++) {
                free(particulas[j]);
            }

            free(particulas);
            fprintf(stderr, "Error de asignacion de memoria.\n");
            return NULL;
        }

        fscanf(file, "%d %d", &particulas[i][0], &particulas[i][1]);
    }
    fclose(file);
    return particulas;
};


/**/
void archivo_salida(celdas* resultadosCeldas, celdas mostEnergy, int cantidadCeldas, char* filename){
    FILE* file = fopen(filename, "w");
    if (file==NULL){
        fprintf(stderr, "No se pudo abrir el archivo.");
        fclose(file);
    }
    fprintf(file, "%d %.6lf\n", mostEnergy.celda, mostEnergy.energia);
    for (int i = 0; i < cantidadCeldas; i++)
    {
        fprintf(file, "%d %.6lf\n",resultadosCeldas[i].celda, resultadosCeldas[i].energia);
    }
    fclose(file);
};


/**/
double energia_j_i(int i, int j, int n, int eJ){
    double resultado =  (pow(10,3)+eJ)/(n*(sqrt(abs(j-i)+1)));
    return resultado;
}


/**/
celdas* energia_celdas(int** datos, int cantidadCeldas){
    double MIN_ENERGY=pow(10,-3)/cantidadCeldas;
    celdas* celdasResultantes = (celdas*) malloc (sizeof(celdas)*cantidadCeldas);
    for (int i = 0; i < cantidadCeldas; i++)
    {
        celdasResultantes[i].celda = i;
        celdasResultantes[i].energia = 0;
        int cantidadParticulas = datos[0][0];
        for (int j = 1; j < cantidadParticulas; j++)
        {
            double energiaParcial = energia_j_i(i,datos[j][0],cantidadCeldas, datos[j][1]);
            if (energiaParcial >= MIN_ENERGY){
            celdasResultantes[i].energia += energiaParcial;
            }
        }
    }
    return celdasResultantes;
}


/**/
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


/**/
int* normalizacion(celdas* resultadoCeldas, celdas mostEnergy, int N, int MAX_CHAR){
    int* normalizado= (int*) malloc(N*sizeof(int));
    for (int i = 0; i < N; i++){
        normalizado[i] = round(resultadoCeldas[i] / (mostEnergy.energia * MAX_CHAR));
    }
    return normalizado;
}