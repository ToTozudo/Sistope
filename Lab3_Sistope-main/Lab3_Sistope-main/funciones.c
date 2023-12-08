
exter#include "funciones.h"
//En este archivo se encuentran todas las funciones que se ocupan en el programa
//Se incluye la librería de funciones.h, que contiene las estructuras y funciones que se ocupan

//Se incluyen las variables globales
extern int chunk; 
extern int numHebras;
extern TDAlista* listaPrincipal;
extern FILE *archivoEntrada;
extern pthread_mutex_t mutex; // Declaración del mutex global

/*---------------------------------------*/
/*---- Utilidades TDA Lista -------------*/
/*---------------------------------------*/


//Entradas: Ninguna
//Salida: Una lista vacía
//Descripción: Función que crea una lista vacía
TDAlista* crearListaVacia()
{
	TDAlista* lista = (TDAlista*)malloc(sizeof(TDAlista));
	lista->inicio = NULL;
	return lista;
}


//Entradas: Una lista
//Salida: 1 si la lista está vacía, 0 si no lo está
//Descripción: Función que verifica si una lista está vacía
int esListaVacia(TDAlista* lista)
{
	if (lista->inicio == NULL)
		return 1;
	else
		return 0;
}


//Entradas: Una lista, y un string
//Salida: Ninguna
//Descripción: Función que inserta un nodo al final de la lista
void insertarNodoFinal(TDAlista* lista, char* datoString, int verificador)
{
	//Se crea el auxiliar que va a recorrer la lista
	nodo* final = lista->inicio;
	//Se crea el nodo que se va a insertar
	nodo* nuevo = (nodo*)malloc(sizeof(nodo));
	nuevo->datoString = malloc(strlen(datoString) + 1);
	strcpy(nuevo->datoString, datoString);
	nuevo->verificador = verificador;
	nuevo->siguiente = NULL;
	if (lista->inicio == NULL)
	{
		lista->inicio = nuevo;
	}
	else
	{
		while (final->siguiente != NULL)
		{
			final = final->siguiente;
		}
		final->siguiente = nuevo;
	}
}


/*---------------------------------------*/
/*------------- operaciones -------------*/
/*---------------------------------------*/

//Funcion principal del desarrollo del programa, es a la primera función que entraran las hebras
//Entrada: Hebra
//Salida: Null
void *hebras(void *arg) {
	//Se crean dos variables que contendrán al verificador, y las lineas que se obtengan de la lectura
    int verificador;
    char buffer[500];
    while (1) {
        pthread_mutex_lock(&mutex);// Se ingresa a la sección crítica
        if (feof(archivoEntrada)) {  // Verificar si ya se llegó al final del archivo
            pthread_mutex_unlock(&mutex);// Se sale de la sección crítica
            break;
        }
        for (int i = 0; i < chunk; i++) {// Iteracion para leer las líneas de cada chunk
            if (fgets(buffer, sizeof(buffer), archivoEntrada) == NULL) { // Se almacena la línea del archivo en buffer
                break;  // Si fgets devuelve NULL, no se pudo leer una línea completa, se sale del ciclo
            }
            //Se elimina el caracter de salto de linea
            char delimitador[] = "\n";
            char *token = strtok(buffer, delimitador);
			//Se verifica si la linea leida es una expresion regular
            verificador = leerPorCaracter(token);
			//Se inserta en la lista global, la linea y su resultado respectivo
            insertarNodoFinal(listaPrincipal, token, verificador);
        }
        pthread_mutex_unlock(&mutex);// Se sale de la sección crítica
    }
    return NULL; //Se termina la ejecución de la hebra
}


//Entradas: String que contiene la expresión regular
//Salida: Numero que identifica si la expresión es válida o no, y el estado en el que se encuentra
//Descripción: Función que analiza una cadena de caracteres y verifica si cumple con un conjunto 
//específico de condiciones detalladas por el autómata. Devuelve 1 si la cadena es válida y 0 si no lo es.
int leerPorCaracter(char *cadena)
{
	//Se hace un auxiliar para recorrer el string
	int indice = 0;
	int estado = 1;
	//Se pone como termino del ciclo, el caracter final
	while (cadena[indice] != '\0')
	//se ejecuta mientras el carácter en la posición indice de la cadena no sea el carácter nulo '\0', que marca el final de la cadena
	{
		char actual = cadena[indice]; //el estado actual del análisis de la cadena.
		//Si el carácter actual está en la etapa 1
		if (estado == 1)
		{
			//Se mantiene en el estado 1
			if (actual == 'A' || actual == 'C' || actual == 'T')
			{
				estado = 1;
			}
			//Avanza al estado 2
			else if (actual == 'G')
			{
				estado = 2;
			}
			//No cumple la condición para ser una expresión regular
			else
			{
				return 0;
			}
		}
		//Si el carácter actual está en la etapa 2
		else if (estado == 2)
		{
			//Se mantiene en el estado 2
			if (actual == 'G')
			{
				estado = 2;
			}
			//Retrocede al estado 1
			else if (actual == 'A' || actual == 'C')
			{
				estado = 1;
			}
			//Avanza al estado 3
			else if (actual == 'T')
			{
				estado = 3;
			}
			//No cumple la condición para ser una expresión regular
			else
			{
				return 0;
			}
		}
		//Si el carácter actual está en la etapa 3
		else if (estado == 3)
		{
			//Se mantiene en el estado 3
			if (actual == 'T')
			{
				estado = 3;
			}
			//Retrocede al estado 2
			else if (actual == 'G')
			{
				estado = 2;
			}
			//Retrocede al estado 1
			else if (actual == 'A')
			{
				estado = 1;
			}
			//Avanza al estado 4
			else if (actual == 'C')
			{
				estado = 4;
			}
			//No cumple la condición para ser una expresión regular
			else
			{
				return 0;
			}
		}
		//Si el carácter actual está en la etapa 4
		else if (estado == 4)
		{
			//Se mantiene en el estado 4
			if (actual == 'A' || actual == 'C' || actual == 'G' || actual == 'T')
			{
				estado = 4;
			}
			//No cumple la condición para ser una expresión regular
			else
			{
				return 0;
			}
		}
		//Avanza al siguiente carácter
		indice++;
	}
	//Una vez que se completa el bucle, se realiza una comprobación adicional. 
	//Si el estado actual no es 4, se devuelve 0 para indicar que dicho string no es una expresión regular
	if (estado != 4)
	{
		return 0;
	}
	//Si terminó en la etapa 4, devuelve 1 para indicar que el string
	//cumple con todas las condiciones establecidas, y es una expresión regular
	return 1;
}


//Entradas: Una lista
//Salida: Cantidad de expresiones válidas
//Descripción: Función que recorre la lista, y verifica si cada elemento es expresión regular
int calculaSi(TDAlista* lista){
	//Se asigna un contador
	int contador = 0;
	if (!esListaVacia(lista))
	{
		nodo* auxiliar=lista->inicio;
		while (auxiliar!= NULL)
		{
			//Si verificador es 1, es una expresión regular
			if (auxiliar->verificador == 1)
			{
				contador++;
			}
			auxiliar=auxiliar->siguiente;
		}
	}
	else
	{
		printf("Reintenta por favor.\n");
	}
	return contador;
}



//Entradas: Una lista
//Salida: Cantidad de expresiones inválidas
//Descripción: Función que recorre la lista, y verifica si cada elemento no es una expresión regular

int calculaNo(TDAlista* lista){
	//Se asigna un contador
	int contador = 0;
	if (!esListaVacia(lista))
	{
		nodo* auxiliar=lista->inicio;
		while (auxiliar!= NULL)
		{
		//Si verificador es 0, no es una expresión regular
			if (auxiliar->verificador == 0)
			{
				contador++;
			}
			auxiliar=auxiliar->siguiente;
		}
	}
	else
	{
		printf("Reintenta por favor.\n");
	}
	return contador;
}


//Entradas: Una lista
//Salida: Cantidad de lineas leídas
//Descripción: Función que recorre la lista, y verifica la cantidad de líneas que tiene.
int calculaCantidadLineas(TDAlista* lista){
	int contador = 0;
	if (!esListaVacia(lista))
	{
		nodo* auxiliar=lista->inicio;
		while (auxiliar!= NULL)
		{
			contador++;
			auxiliar=auxiliar->siguiente;
		}
	}
	else
	{
		printf("Reintenta por favor.\n");
	}
	return contador;
}


//Entradas: Una lista
//Salida: Impresión de los cálculos por pantalla
//Descripción: Función que recorre la lista, y muestra por pantalla los cálculos realizados.
void imprimirCalculos(TDAlista* lista){
	int siExpresionRegular = calculaSi(lista);
	int noExpresionRegular = calculaNo(lista);
	int totalLineasLeidas = calculaCantidadLineas(lista);
	printf("Total de expresiones que Si son regulares: %d\n", siExpresionRegular);
	printf("Total de expresiones que No son regulares: %d\n", noExpresionRegular);
	printf("Total de lineas leídas: %d\n", totalLineasLeidas);
}


//Entradas: Una lista, y el nombre del archivo de salida
//Salida: Un archivo de salida con los resultados de la verificación.
//Descripción: Función que genera el archivo de salida con la información solicitada
void escribirArchivoSalida(TDAlista* lista, char* nombreSalida)
{
	//Se abre el archivo
	FILE* archivoSalida = fopen(nombreSalida,"w");
	//Se verifica que se abrió correctamente
	if(archivoSalida == NULL)
	{
		printf("\nHubo un error en la creación del archivo de salida\n");
		return;
	}
	if (!esListaVacia(lista))
	{	
		//Se hace un auxiliar que recorrerá toda la lista, para escribirla en el archivo de salida
		nodo* auxiliar=lista->inicio;
		while (auxiliar!= NULL)
		{
			fputs(auxiliar->datoString, archivoSalida);
			if (auxiliar->verificador == 1)
			{
				fputs(" Si\n", archivoSalida);
			}
			else
			{
				fputs(" No\n", archivoSalida);
			}
			auxiliar=auxiliar->siguiente;
		}
	}
	else
	{
		printf("La lista está vacia\n");
	}
	//Se obtienen todos los resultados de cantidad de lineas leidas, y cuantas son expresiones regulares y cuantas no
	int siExpresionRegular = calculaSi(lista);
	int noExpresionRegular = calculaNo(lista);
	int totalLineasLeidas = calculaCantidadLineas(lista);
	//Se escriben dichos resultados
	fprintf(archivoSalida, "Total de expresiones que Si son regulares: %d\n", siExpresionRegular);
	fprintf(archivoSalida, "Total de expresiones que No son regulares: %d\n", noExpresionRegular);
	fprintf(archivoSalida, "Total de lineas leidas: %d\n", totalLineasLeidas);
	//Se cierra el archivo, ya que no se ocupará más
	fclose(archivoSalida);
}