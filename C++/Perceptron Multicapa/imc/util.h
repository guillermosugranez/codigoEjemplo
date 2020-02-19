/*
 * util.h
 *
 *  Created on: 06/03/2015
 *      Author: pedroa
 */

#ifndef UTIL_H_
#define UTIL_H_

using namespace std;

#include <string> // strings
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <iostream> // cout cerr
#include <fstream> // fopen
#include <sstream>
#include <cstdio> // fprintf
#include <unistd.h> // getopt
#include <cstring>
#include <math.h>

namespace util
{
	typedef struct _Configuracion
	{
		// PRACTICA 1

		// Variables
		char * tvalue; // nombre de fichero de entrenamiento
		char * Tvalue; // nombre de fichero de Test

		int iteraciones; // Numero de iteraciones del bucle externo a realizar (por defecto 1000)
		int l; // Numero de capas ocultas (por defecto 1)
		int h; // Numero de neuronas a introducir en cada una de las capas ocultas (por defecto 5)

		float dEta; // Valor del parametro eta (por defecto 0.1)
		float dMu; // Valor del parametro mu (por defecto 0.9)
		float dValidacion; // Ratio de patrones de test a utilizar como patrones de validacion (por defecto 0.0) ; v
		float dDecremento; // Factor de decremento a usar para cada una de las capas (F=1)

		// Flags
		bool tflag; // Flag de nombre de fichero de ENTRENAMIENTO correcto
		bool Tflag; // Flag de nombre de fichero de TEST correcto
		bool iflag; // iteraciones bucle externo
		bool lflag; // nº capas ocultas
		bool hflag; // nº neuronas
		bool eflag; // eta
		bool mflag; // mu
		bool vflag; // ratio
		bool dflag; // F

		// Kaggle
		char * wvalue; // Pesos
		bool wflag; // weights
		bool pflag; // Modo prediccion o kaggle

		// PRACTICA 2

		bool oflag; // Indica la versión del algoritmo, off-line (0) u on-line (1). Por defecto off-line.
		bool fflag; // Indica la funcion de error. 0 para MSE y 1 para entropía cruzada.
		bool sflag; // Indica si vamos a usar la función Softmax (1) o si usaremos la función sigmoide (0).

	} Configuracion;

	typedef struct _Datos {
		int nNumEntradas;     /* Número de entradas */
		int nNumSalidas;      /* Número de salidas */
		int nNumPatrones;     /* Número de patrones */
		double** entradas;    /* Matriz con las entradas del problema */
		double** salidas;     /* Matriz con las salidas del problema */
	} Datos;

	// DATOS

	// Antes descrita
	bool leerBaseDeDatos(const char * nombreFichero, Datos &data);

	// Permite liberar la memoria dinámica asociada a la estructura configuración
	bool borrarBaseDeDatos(Datos * data);

	// Guarda en la estructura configuración el valor de cada parámetro y controla que todo esté correcto
	bool procesarLineaComandos(int &argc, char **argv, Configuracion * parametros);

	// Devuelve el puntero con la dirección de memoria dinámica dónde está alojada una matriz
	double ** reservarMemoria(int filas, int columnas);

	// Permite copiar el patrón de un conjunto de datos origen a otro destino
	void copiarPatron(Datos * origen, Datos * destino, int indicePatron, int posicion);

	// Muestra los datos almacenados en la estructura data
	void escribirDatos(const Datos * data);

	// Comprueba que los archivos de datos de entrenamiento y test son .dat
	bool comprobarExtensionFichero(string nombreFichero);

	// CONFIGURACION

	// Comprueba que el parámetro recivido en la linea de comandos sea un entero válido para el problema
	bool comprobarInt(char * cadena, int &n);

	// Lo mismo para los parámetros float
	bool comprobarFloat(char * cadena, float min, float max, float &n);

	// Inicializa la estructura configuración con los parámetros por defecto
	void configuracionPorDefecto(Configuracion * parametros);

	// Muestra el valor de los campos de la estructura configuración
	void mostrarConfiguracion(const Configuracion * parametros);

	// AUXILIARES

	// Esta función permite crear un nombre para el fichero de salida en funcion de la configuracion establecida
	string crearNombreFichero(char * nombreFichero, const Configuracion * parametros);

	// Devuelve un valor aleatorio entre un minimo y un máximo (usada para los pesos aleatorios)
	double fRand(double fMin, double fMax);

	// Función previamente implementada que devulve un vector de enteros aleatorios
	int * vectorAleatoriosEnterosSinRepeticion(int minimo, int maximo, int cuantos);

	// devuelve la sigmoide una vez pasada la suma ponderada de las entradas de la neurona j en la capa h (net^h_j)
	double sigmoide(double net);

	// Recive un vector y devuelve la posicion del elemento máximo del vector
	int argmax(double * v, int tam);
};


#endif /* UTIL_H_ */
