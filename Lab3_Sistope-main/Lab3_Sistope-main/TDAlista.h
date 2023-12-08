#ifndef TDA_LISTA_H //Se realiza esta comprobación para evitar errores de compilación por redefinición de funciones
#define TDA_LISTA_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Archivo que contiene la estructura base de una lista enlazada
/*------------------------------------------*/
/* -----Definicion de estructura del TDA----*/
/*------------------------------------------*/

//Entradas: Ninguna
//Salida: Nodo para una Lista
//Descripción: Estructura de un nodo de una lista

typedef struct nodoGenerico
{
	char* datoString;
	int verificador;
	struct nodoGenerico* siguiente;
} nodo;


//Entradas: Ninguna
//Salida: Lista
//Descripción: Estructura de una lista

typedef struct listaGenerica
{
	nodo* inicio;
} TDAlista;

TDAlista* crearListaVacia();
int esListaVacia(TDAlista* lista);
void insertarNodoFinal(TDAlista* lista, char* datoString, int verificador);

#endif
