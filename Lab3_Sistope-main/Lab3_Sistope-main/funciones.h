#ifndef FUNCIONES_H //Se realiza esta comprobación para evitar errores de compilación por redefinición de funciones
#define FUNCIONES_H

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include "TDAlista.h"

//Se llaman las cabeceras de las funciones a utilizar en el programa
void *hebras(void *arg);
int leerPorCaracter(char *cadena);
int calculaSi(TDAlista* lista);
int calculaNo(TDAlista* lista);
int calculaCantidadLineas(TDAlista* lista);
void imprimirCalculos(TDAlista* lista);
void escribirArchivoSalida(TDAlista* lista, char* nombreSalida);

#endif
