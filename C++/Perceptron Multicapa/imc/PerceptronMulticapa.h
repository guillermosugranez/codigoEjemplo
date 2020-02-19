/*********************************************************************
 * File  : PerceptronMulticapa.cpp
 * Date  : 2017
 *********************************************************************/


#ifndef _PERCEPTRONMULTICAPA_H_
#define _PERCEPTRONMULTICAPA_H_

using namespace std;

#include "util.h"

using namespace util;

namespace imc
{
	// Estructuras sugeridas

	// ---------------------
	typedef struct _Neurona {
		double x; /* Salida producida por la neurona (out_j^h)*/
		double dX; /* Derivada de la salida producida por la neurona (delta_j)*/
		double* w; /* Vector de pesos de entrada (w_{ji}^h)*/
		double* deltaW; /* Cambio a aplicar a cada peso de entrada (\Delta_{ji}^h (t))*/
		double* ultimoDeltaW; /* Último cambio aplicada a cada peso (\Delta_{ji}^h (t-1))*/
		double* wCopia; /* Copia de los pesos de entrada */
	} Neurona;

	typedef struct _Capa {
		int nNumNeuronas; /* Número de neuronas de la capa*/
		Neurona ** pNeuronas; /* Vector con las neuronas de la capa*/
	} Capa;

	class PerceptronMulticapa
	{

	private:

		int nNumCapas;	/* Número de capas total en la red */
		Capa ** pCapas;	/* Vector con cada una de las capas. Verdadera red neuronal */

		double dEta;        // Tasa de aprendizaje
		double dMu;         // Factor de momento
		double dValidacion; // Ratio de patrones de entrenamiento usados para validación (p.ej.
							// si dValidacion=0.2, un 20% de los datos de entrenamiento,
							// se usan para valición; si dValidacion=0, no hay validación)
		int dDecremento; // Factor de decremento por capas para eta

		int nNumNeuronasCapaOculta; // Numero de neuronas a introducir en cada una de las capas ocultas (por defecto 5)

		// PRACTICA 2
		int nNumPatronesTrain; /* Para la versión offline */
		bool bOnline; // ¿El aprendizaje va a ser online? (true->online,false->offline)
		bool funcionErrorEntropia; // Entropía cruzada (1) o MSE (0)
		bool funcionSalidaSoftmax; // Funcion sofmax (1) o sigmoide (0) en la capa de salida 

		// Liberar memoria para las estructuras de datos
		void liberarMemoria();

		// Rellenar todos los pesos (w) aleatoriamente entre -1 y 1
		void pesosAleatorios();

		// Inicializa el vector deltaW a 0
		void inicializarDeltaW();

		// Generar datos de validacion
		Datos * generarDatosValidacion(Datos * &pDatostrain, Datos * &pDatostrain_nuevo, Datos * &aux);

		// Alimentar las neuronas de entrada de la red con un patrón pasado como argumento
		void alimentarEntradas(double* entrada);

		// Recoger los valores predichos por la red (out de la capa de salida) y almacenarlos en el vector pasado como argumento
		void recogerSalidas(double* salida);

		// Hacer una copia de todos los pesos (copiar w en copiaW)
		void copiarPesos();

		// Restaurar una copia de todos los pesos (copiar copiaW en w)
		void restaurarPesos();

		// Calcular y propagar las salidas de las neuronas, desde la primera capa hasta la última
		void propagarEntradas();

		// Calcular el error de salida (MSE) del out de la capa de salida con respecto a un vector objetivo y devolverlo
		double calcularErrorSalida(double* objetivo);

		// Retropropagar el error de salida con respecto a un vector pasado como argumento, desde la última capa hasta la primera
		void retropropagarError(double* objetivo);

		// Acumular los cambios producidos por un patrón en deltaW
		void acumularCambio();

		// Actualizar los pesos de la red, desde la primera capa hasta la última
		void ajustarPesos();

		// Actualizar los pesos de la red, desde la primera capa hasta la última para la version offline
		void ajustarPesosOffline();

		// Imprimir la red, es decir, todas las matrices de pesos
		void imprimirRed();

		// Simular la red: propragar las entradas hacia delante, computar el error, retropropagar el error y ajustar los pesos
		// entrada es el vector de entradas del patrón, objetivo es el vector de salidas deseadas del patrón.
		// El paso de ajustar pesos solo deberá hacerse si el algoritmo es on-line
		// Si no lo es, el ajuste de pesos hay que hacerlo en la función "entrenar"
		// funcionError=1 => EntropiaCruzada // funcionError=0 => MSE
		void simularRed(double* entrada, double* objetivo);

	public:
		
		// CONSTRUCTOR: Dar valor por defecto a todos los parámetros
		PerceptronMulticapa();

		// DESTRUCTOR: liberar memoria
		~PerceptronMulticapa();

		// Reservar memoria para las estructuras de datos
		 // nl tiene el numero de capas y npl es un vector que contiene el número de neuronas por cada una de las capas
		 // Rellenar vector Capa* pCapas
		int inicializar(int nl, int npl[]);

		// Sobrecarga de inicializar que permite incializar la red neuronal sabiendo el numero de entradas y de salidas
		int inicializar(int numEntradas, int numSalidas);

		// Leer una matriz de datos a partir de un nombre de fichero y devolverla
		Datos* leerDatos(const char *archivo);

		// Probar la red con un conjunto de datos y devolver el error MSE cometido
		double test(Datos* pDatosTest);

		double testClassification(Datos* pDatosTest);

		/*
			* Probar la red con un conjunto de datos y devolver el CCR (Versión sobrecargada)

			* guardarPatrones indica si se desea guardar los patrones mal clasificados en un archivo csv
				- Cada linea de este patron es un patron
				- El primer caracter antes de una coma es la letra que ha predicho erroneamente
				- El último caracter es el número del patrón de test
				- Los números de enmedio son las entradas del patron (o pixeles de la imágen)
		*/
		double testClassification(Datos* pDatosTest, bool guardarPatrones);

		// Obtener las salidas predichas para un conjunto de datos
		bool predecir(Datos* pDatosTest);

		// Entrenar la red para un determinado fichero de datos (pasar una vez por todos los patrones)
		void entrenar(Datos* pDatostrain);

		// Ejecutar el algoritmo de entrenamiento durante un número de iteraciones, utilizando pDatosTrain
		// Una vez terminado, probar como funciona la red en pDatosTest
		// Tanto el error MSE de entrenamiento como el error MSE de test deben calcularse y almacenarse en errorTrain y errorTest
		void ejecutarAlgoritmo(Datos * pDatostrain, Datos * pDatosTest, const Configuracion * parametros, double *errorTrain, double *errorTest, double *ccrTrain, double *ccrTest, double &iteracionesRealizadas, int semilla);

		//Guardar los pesos del modelo en un fichero de texto.
		bool guardarPesos(const char * archivo);

		//Cargar los pesos del modelo desde un fichero de texto.
		bool cargarPesos(const char * archivo);

		// Establece los parámetros de configuracion obtenidos con getopt
		void establecerConfiguracion(const Configuracion * conf);
	};
};

#endif
