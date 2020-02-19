/*********************************************************************
 * File  : PerceptronMulticapa.cpp
 * Date  : 2017
 *********************************************************************/

#include "PerceptronMulticapa.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <limits>
#include <math.h>

#define mejorSemilla 400

using namespace std;
using namespace imc;
using namespace util;

// ------------------------------
// CONSTRUCTOR: Dar valor por defecto a todos los parámetros
PerceptronMulticapa::PerceptronMulticapa()
{
	nNumCapas = 3;		/* Número de capas total en la red (0,1,2)*/
	pCapas = NULL;		/* Vector con cada una de las capas */
	dEta = 0.1;			// Tasa de aprendizaje
	dMu = 0.9;			// Factor de momento
	dValidacion = 0.2;	// Ratio de patrones de entrenamiento usados para validación
	dDecremento = 1;	// Factor de decremento por capas para eta
	nNumNeuronasCapaOculta = 0;

	// PRACTICA 2
	nNumPatronesTrain = 0; /* Para la versión offline */
	bOnline = false; // ¿El aprendizaje va a ser online? (true->online,false->offline)
	funcionErrorEntropia = false; // Entropía cruzada (1) o MSE (0)
	funcionSalidaSoftmax = false; // Funcion sofmax (1) o sigmoide (0) en la capa de salida
}

// ------------------------------
// Reservar memoria para las estructuras de datos
int PerceptronMulticapa::inicializar(int nl, int npl[])
{
	/*
		// Inicializar vector topología
		topologia[0] = pDatostrain.nNumEntradas;
		for(int i=1; i<(parametros->l+2-1); i++)
			topologia[i] = parametros->h;
		topologia[parametros->l+2-1] = pDatostrain.nNumSalidas;

		// Inicializar red con vector de topología
		mlp.inicializar(parametros->l+2, topologia);
	*/

	// Te llegan el numero de capa
	return 1;
}

// Reservar memoria para las estructuras de datos
int PerceptronMulticapa::inicializar(int numEntradas, int numSalidas)
{
	pCapas = new Capa *[nNumCapas];
	
	// CAPA DE ENTRADA

	Capa * capaEntrada = new Capa;
	capaEntrada->nNumNeuronas = numEntradas; // El nº de neuronas de la capa de entrada equivale al nº de entradas en la bd

	// Reserva de memoria para las neuronas de esta capa
	capaEntrada->pNeuronas = new Neurona*[numEntradas];
	for(int i = 0; i < numEntradas; i++)
		capaEntrada->pNeuronas[i] = new Neurona;
	pCapas[0] = capaEntrada;
	
	// CAPAS OCULTAS

	for(int i = 1; i < nNumCapas-2+1; i++)
	{
		pCapas[i] = new Capa;
		pCapas[i]->nNumNeuronas = nNumNeuronasCapaOculta;

		pCapas[i]->pNeuronas = new Neurona *[nNumNeuronasCapaOculta]; // Reserva espacio para los punteros a neuronas
		for(int j = 0; j < nNumNeuronasCapaOculta; j++)
			pCapas[i]->pNeuronas[j] = new Neurona; // Reserva espacio para cada neurona
	}

	// CAPA DE SALIDA
	
	Capa * capaSalida = new Capa;
	capaSalida->nNumNeuronas = numSalidas;

	capaSalida->pNeuronas = new Neurona *[numSalidas]; // Reserva espacio para los punteros a neuronas
	for(int i = 0; i < numSalidas; i++)
		capaSalida->pNeuronas[i] = new Neurona;
	pCapas[nNumCapas-1] = capaSalida;

	// VECTORES

	for(int i = 1; i < nNumCapas; i++) // Por cada capa empezando por la primera oculta
		for(int j = 0; j < pCapas[i]->nNumNeuronas; j++) // Por cada neurona de esa capa
		{
			// +1 por el sesgo
			pCapas[i]->pNeuronas[j]->w = new double[(pCapas[i-1]->nNumNeuronas)+1];
			pCapas[i]->pNeuronas[j]->deltaW = new double[(pCapas[i-1]->nNumNeuronas)+1];
			pCapas[i]->pNeuronas[j]->ultimoDeltaW = new double[(pCapas[i-1]->nNumNeuronas)+1];
			pCapas[i]->pNeuronas[j]->wCopia = new double[(pCapas[i-1]->nNumNeuronas)+1];
		}

	return 1;
}


// ------------------------------
// DESTRUCTOR: liberar memoria
PerceptronMulticapa::~PerceptronMulticapa() {
	liberarMemoria();

}


// ------------------------------
// Liberar memoria para las estructuras de datos
void PerceptronMulticapa::liberarMemoria()
{
	for(int i = 1; i < nNumCapas; i++) // Por cada capa empezando por la primera oculta
	{
		for(int j = 0; j < pCapas[i]->nNumNeuronas; j++) // Por cada neurona de esa capa
		{
			delete [] pCapas[i]->pNeuronas[j]->w;
			delete [] pCapas[i]->pNeuronas[j]->deltaW;
			delete [] pCapas[i]->pNeuronas[j]->ultimoDeltaW;
			delete [] pCapas[i]->pNeuronas[j]->wCopia;

			delete pCapas[i]->pNeuronas[j]; // Libero la neurona i
		}

		delete [] pCapas[i]->pNeuronas; // libero el vector de neuronas
		delete pCapas[i]; // Libero la capa
	}

	delete[] pCapas; // libero el vector de capas
	pCapas = NULL;

	return;
}

// ------------------------------
// Rellenar todos los pesos (w) aleatoriamente entre -1 y 1
void PerceptronMulticapa::pesosAleatorios()
{
	// cout<<"pesosAleatorios"<<endl;

	int contador = 0;

	/*
	double v[9];

	// Ejemplo de las diapositivas
	v[0] = 1;
	v[1] = 1;
	v[2] = 2;

	v[3] = 2;
	v[4] = 2;
	v[5] = 1;

	v[6] = 1;
	v[7] = 1;
	v[8] = 1;
	*/

	for(int i = 1; i < nNumCapas; i++) // Por cada capa empezando por la primera oculta
		for(int j = 0; j < pCapas[i]->nNumNeuronas; j++) // Por cada neurona de esa capa
		{
			for(int k = 0; k < (pCapas[i-1]->nNumNeuronas)+1; k++) // Por cada neurona de la capa anterior (+1 por el sesgo)
			{
				pCapas[i]->pNeuronas[j]->w[k] = fRand(-1,1); // fRand(-1,1) v[contador]
				contador++;
			}
		}

		return;
}

// Inicializa el vector deltaW a 0
void PerceptronMulticapa::inicializarDeltaW()
{
	// cout<<"inicializarDeltaW"<<endl;

	for(int i = 1; i < nNumCapas; i++) // Por cada capa empezando por la primera oculta
		for(int j = 0; j < pCapas[i]->nNumNeuronas; j++) // Por cada neurona de esa capa
			for(int k = 0; k < (pCapas[i-1]->nNumNeuronas)+1; k++) // Por cada neurona de la capa anterior (+1 por el sesgo)
				pCapas[i]->pNeuronas[j]->deltaW[k] = 0.0;

	// cout<<"fin inicializarDeltaW"<<endl;
}

Datos * PerceptronMulticapa::generarDatosValidacion(Datos * &pDatostrain, Datos * &pDatostrain_nuevo, Datos * &aux)
{
	//cout<<" LOS DATOS DE TRAIN SON: "<<endl;
	//escribirDatos(pDatostrain);

	Datos * pDatosValidacion = NULL;

	// Crear dos conjuntos nuevos a partir del conjunto de entramiento
	int numPatronesTotales = pDatostrain->nNumPatrones;
	int numEntradas = pDatostrain->nNumEntradas;
	int numSalidas = pDatostrain->nNumSalidas;

	// Obtener numero total de patrones de cada conjunto y reservar memoria
	int numPatronesValidacion = numPatronesTotales * dValidacion;

	//cout<<"El numero de patrones de validacion es: "<<numPatronesValidacion<<endl;

	int numPatronesEntranamiento = numPatronesTotales - numPatronesValidacion;

	//cout<<"El numero de patrones de entramiento es: "<<numPatronesEntranamiento<<endl;

	pDatosValidacion = new Datos[numPatronesValidacion];
	pDatostrain_nuevo = new Datos[numPatronesEntranamiento];

	// Array que determinará qué patrones van en cada conjunto
	int * vectorAleatorios = vectorAleatoriosEnterosSinRepeticion(0, numPatronesTotales-1, numPatronesTotales);

	/*for(int i = 0; i < numPatronesTotales; i++)
		cout<<"Elemento i = "<<i<<" del vector de aleatorios = "<<vectorAleatorios[i]<<endl;*/

	// Rellenar estructuras
	pDatosValidacion->nNumEntradas = numEntradas;
	pDatosValidacion->nNumSalidas = numSalidas;
	pDatosValidacion->nNumPatrones = numPatronesValidacion;
	pDatosValidacion->entradas = reservarMemoria(numPatronesValidacion, numEntradas);
	pDatosValidacion->salidas = reservarMemoria(numPatronesValidacion, numSalidas);

	for(int i = 0; i < numPatronesValidacion; i++)
		copiarPatron(pDatostrain, pDatosValidacion, vectorAleatorios[i], i);

	pDatostrain_nuevo->nNumEntradas = numEntradas;
	pDatostrain_nuevo->nNumSalidas = numSalidas;
	pDatostrain_nuevo->nNumPatrones = numPatronesEntranamiento;
	pDatostrain_nuevo->entradas = reservarMemoria(numPatronesEntranamiento, numEntradas);
	pDatostrain_nuevo->salidas = reservarMemoria(numPatronesEntranamiento, numSalidas);

	for(int i = 0; i < numPatronesEntranamiento; i++)
		copiarPatron(pDatostrain, pDatostrain_nuevo, vectorAleatorios[i+numPatronesValidacion], i);

	// Durante la ejecucion del algoritmo, se usaran estos datos como los datos de entrenamiento

	aux = pDatostrain; // Guardo la direccion de los datos de Entrenamiento anteior
	pDatostrain = pDatostrain_nuevo; // Uso la nueva

	// cout<<" LOS DATOS DE TRAIN AHORA SON: "<<endl;
	// escribirDatos(pDatostrain);

	// cout<<" LOS DATOS DE VALIDACION SON: "<<endl;
	// escribirDatos(pDatosValidacion);

	// delete [] vectorAleatorios;

	return pDatosValidacion;
}

// ------------------------------
// Alimentar las neuronas de entrada de la red con un patrón pasado como argumento
void PerceptronMulticapa::alimentarEntradas(double* input)
{
	for(int i = 0; i < pCapas[0]->nNumNeuronas; i++) // Por cada neurona de la primera capa
	{
		// La salida será igual a la entrada correspondiente
		pCapas[0]->pNeuronas[i]->x = input[i];
		// cout<<"La entrada de la neurona "<<i<<" de la capa de entrada es: "<<pCapas[0]->pNeuronas[i]->x <<endl;
	}

	//cout<<endl;

	return;
}

// ------------------------------
/*
	Recoger los valores predichos por la red (out de la capa de salida) y almacenarlos en el vector pasado como argumento
	- Esto sirve para cuando queremos predecir con un patron predeterminado
	- No se usa en el entrenamiento
*/
void PerceptronMulticapa::recogerSalidas(double* output)
{
	for(int i = 0; i < pCapas[nNumCapas-1]->nNumNeuronas; i++) // Por cada neurona de la capa de salida
		output[i] = pCapas[nNumCapas-1]->pNeuronas[i]->x;

	return;
}

// ------------------------------
// Hacer una copia de todos los pesos (copiar w en copiaW)
void PerceptronMulticapa::copiarPesos()
{
	for(int i = 1; i < nNumCapas; i++) // Por cada capa empezando por la primera oculta
		for(int j = 0; j < pCapas[i]->nNumNeuronas; j++) // Por cada neurona de esa capa
			for(int k = 0; k < (pCapas[i-1]->nNumNeuronas)+1; k++) // Por cada peso de la neurona (neurona de la capa anterior)
				pCapas[i]->pNeuronas[j]->wCopia[k] = pCapas[i]->pNeuronas[j]->w[k];

	return;
}

// ------------------------------
// Restaurar una copia de todos los pesos (copiar copiaW en w)
void PerceptronMulticapa::restaurarPesos()
{
	for(int i = 1; i < nNumCapas; i++) // Por cada capa empezando por la primera oculta
		for(int j = 0; j < pCapas[i]->nNumNeuronas; j++) // Por cada neurona de esa capa
			for(int k = 0; k < (pCapas[i-1]->nNumNeuronas)+1; k++)
				pCapas[i]->pNeuronas[j]->w[k] = pCapas[i]->pNeuronas[j]->wCopia[k];

	return;
}

// ------------------------------
/*
	Calcular y propagar las salidas de las neuronas, desde la primera capa hasta la última
*/
void PerceptronMulticapa::propagarEntradas()
{
	double net;

	int i = 0;

	// CAPAS OCULTAS

	for(i = 1; i < nNumCapas-1; i++) // Por cada capa empezando por la primera oculta y exceptuando la última
	{
		for(int j = 0; j < pCapas[i]->nNumNeuronas; j++) // Por cada neurona
		{
			net = 0.0;

			// suma ponderada de las entradas de la neurona j en la capa h (net^h_j)
			for(int k = 1; k <= pCapas[i-1]->nNumNeuronas; k++) // Por cada neurona de la capa anterior
			{
				// salida de la neurona anterior por el peso correspondiente en la capa actual (sumatatorio)
				//cout<<"peso: "<<pCapas[i]->pNeuronas[j]->w[k]<<endl;
				//cout<<"entrada: "<< pCapas[i-1]->pNeuronas[k-1]->x<<endl;
				net += pCapas[i-1]->pNeuronas[k-1]->x * pCapas[i]->pNeuronas[j]->w[k];
				//cout<<endl;
			}

			net += pCapas[i]->pNeuronas[j]->w[0]; // añado el sego

			pCapas[i]->pNeuronas[j]->x = sigmoide(net); // calculo sigmoide

			//cout<<"La salida de la capa "<< i <<" y neourna "<< j << " es "<< pCapas[i]->pNeuronas[j]->x <<endl;
		}
	}

	// CAPA DE SALIDA

	double sumatorioNet = 0.0;

	for(int j = 0; j < pCapas[i]->nNumNeuronas; j++) // Por cada neurona
	{
		net = 0.0;

		for(int k = 1; k <= pCapas[i-1]->nNumNeuronas; k++) // Por cada neurona de la capa anterior
			net += pCapas[i-1]->pNeuronas[k-1]->x * pCapas[i]->pNeuronas[j]->w[k];

		net += pCapas[i]->pNeuronas[j]->w[0]; // añado el sego

		if(funcionSalidaSoftmax)
		{
			net = exp(net);
			sumatorioNet += net;
			pCapas[i]->pNeuronas[j]->x = net; // Asigno temporalmente el valor de net para aplicar luego softmax
		}
		else
			pCapas[i]->pNeuronas[j]->x = sigmoide(net); // calculo sigmoide en la salida

		//cout<<"La salida de la capa "<< i <<" y neourna "<< j << " es "<< pCapas[i]->pNeuronas[j]->x <<endl;
	}

	// Aplico la funcion softmax a la salida de cada neurona
	if(funcionSalidaSoftmax)
		for(int j = 0; j < pCapas[i]->nNumNeuronas; j++) // Por cada neurona de la capa de salida
			pCapas[i]->pNeuronas[j]->x = pCapas[i]->pNeuronas[j]->x / sumatorioNet;

	return;
}

// ------------------------------
/*
	Calcular el error de salida (MSE o entropía cruzada) del out de la capa de salida con respecto a un vector objetivo y devolverlo
	- 
*/
double PerceptronMulticapa::calcularErrorSalida(double * salidasEsperadas)
{
	// cout<<"calcularErrorSalida"<<endl;

	if(funcionErrorEntropia) // Si es entropía cruzada
	{
		double L = 0.0;

		for(int i = 0; i < pCapas[nNumCapas-1]->nNumNeuronas; i++) // Por cada neurona de la capa de salida
			L += salidasEsperadas[i] * log(pCapas[nNumCapas-1]->pNeuronas[i]->x);

		return L;
	}
	else // Si es MSE
	{
		double MSE = 0.0;

		// La salida puede estar compuesta por una o mas variables (neuronas en la capa de salida)
		for(int i = 0; i < pCapas[nNumCapas-1]->nNumNeuronas; i++) // Por cada neurona de la capa de salida
			MSE += pow((salidasEsperadas[i] - pCapas[nNumCapas-1]->pNeuronas[i]->x), 2);

		MSE = MSE / pCapas[nNumCapas-1]->nNumNeuronas;
		// cout<<"El error cometido es: "<< MSE <<endl;

		return MSE;
	}

	// cout<<"fin calcularErrorSalida"<<endl;
}


// ------------------------------
/*
	Retropropagar el error de salida con respecto a un vector pasado como argumento, desde la última capa hasta la primera
	- Forma parte del algoritmo de retropropagacion del error
	- Previamente se han completado las salidas de cada una de las neuronas de la capa de salida
	- Calcular el error en cada caso y retropropagar
	- E = (di - oi)²
*/
void PerceptronMulticapa::retropropagarError(double * salidasEsperadas)
{
	double sumatorio = 0.0;
	double o = 0.0;
	double oi = 0.0;
	double d = 0.0;
	double di = 0.0;

	bool cond = 0;

	// CAPA DE SALIDA

	// Derivar el error en la capa de salida y apuntarlo en dX de cada neurona por cada valor de salida esperada
	for(int j = 0; j < pCapas[nNumCapas-1]->nNumNeuronas; j++) // Por cada neurona de la capa de salida
	{
		// Neurona de salida i

		o = pCapas[nNumCapas-1]->pNeuronas[j]->x;
		d = salidasEsperadas[j];

		// cout<<"La salida o es: "<< o <<endl;
		// cout<<"El valor esperado d es: "<< d <<endl;
		// Calculamos su derivada del error dX;
		/* Derivada de la salida producida por la neurona (delta_j)*/
		if(funcionSalidaSoftmax)
		{
			sumatorio = 0.0;

			for(int i = 0; i < pCapas[nNumCapas-1]->nNumNeuronas; i++) // Por cada neurona de la capa de salida de nuevo
			{
				oi = pCapas[nNumCapas-1]->pNeuronas[i]->x;
				di = salidasEsperadas[i];
				cond = i == j;

				if(funcionErrorEntropia)
				{
					sumatorio += (di/oi)*o*(cond-oi);
				}
				else // MSE => E = (di - oi)²
				{
					sumatorio += (di-oi)*o*(cond-oi);
				}
			}

			pCapas[nNumCapas-1]->pNeuronas[j]->dX = -2*sumatorio;
		}
		else // Sigmoide
		{
			if(funcionErrorEntropia)
			{
				pCapas[nNumCapas-1]->pNeuronas[j]->dX = -2*(d/o)*o*(1-o);
			}
			else // MSE => E = (di - oi)²
			{
				pCapas[nNumCapas-1]->pNeuronas[j]->dX = -2*(d-o)*o*(1-o);
			}
		}

		// cout<<"La derivada del error en la neurona i = "<< i <<" de la capa de salida es: "<< pCapas[nNumCapas-1]->pNeuronas[i]->dX <<endl;
	}
	

	// CAPAS OCULTAS (para todos los casos igual)

	for(int i = nNumCapas-1-1; i > 0; i--)
	{
		for(int j = 0; j < pCapas[i]->nNumNeuronas; j++) // Por cada neurona de la capa opculta actual
		{
			for(int k = 0; k < pCapas[i+1]->nNumNeuronas; k++) // Por cada neurona de la capa siguiente a la actual
			{
				sumatorio += pCapas[i+1]->pNeuronas[k]->w[k+1] * pCapas[i+1]->pNeuronas[k]->dX; // +1 por el sesgo
			}

			o = pCapas[i]->pNeuronas[j]->x;
			pCapas[i]->pNeuronas[j]->dX = sumatorio * o * (1-o);

			// cout<<"La derivada del error en la neurona j = "<< j <<" de la capa i = "<< i <<" es: "<< pCapas[i]->pNeuronas[j]->dX <<endl;
			sumatorio = 0;
		}
	}

	return;
}

// ------------------------------
// Acumular los cambios producidos por un patrón en deltaW
void PerceptronMulticapa::acumularCambio()
{
	for(int i = 1; i < nNumCapas; i++) // Por cada capa (sin contar la de entrada)
	{
		for(int j = 0; j < pCapas[i]->nNumNeuronas; j++) // Por cada neurona de la capa
		{
			for(int k = 1; k <= pCapas[i-1]->nNumNeuronas; k++) // Por cada neurona de la capa anterior
			{
				// Copia deltaW actual a ultimoDeltaW
				pCapas[i]->pNeuronas[j]->ultimoDeltaW[k] = pCapas[i]->pNeuronas[j]->deltaW[k];

				// Calcular deltaW
				pCapas[i]->pNeuronas[j]->deltaW[k] += pCapas[i]->pNeuronas[j]->dX * pCapas[i-1]->pNeuronas[k-1]->x; // <- AQUI TENER CUIDADO CON EL SESGO (pNeuronas[k-1]->x)
				//cout<<"deltaW["<<k<<"], j["<< j <<"], i["<< i <<"] = "<< pCapas[i]->pNeuronas[j]->deltaW[k]<<endl;
			}
			pCapas[i]->pNeuronas[j]->deltaW[0] += pCapas[i]->pNeuronas[j]->dX * 1; // Sesgo
			//cout<<"deltaW[0] = "<< pCapas[i]->pNeuronas[j]->deltaW[0]<<" (sesgo)."<<endl;
			//cout<<endl;
		}
	}
}

// ------------------------------
// Actualizar los pesos de la red, desde la primera capa hasta la última
void PerceptronMulticapa::ajustarPesos()
{
	// Por legibilidad
	double incremento;
	double incrementoAnterior;

	double pDecremento=0;

	for(int i = 1; i < nNumCapas; i++) // Por cada capa (sin contar la de entrada)
	{
		pDecremento= pow(dDecremento, -(nNumCapas-i-1));

		for(int j = 0; j < pCapas[i]->nNumNeuronas; j++) // Por cada neurona de la capa
		{
			for(int k = 1; k <= pCapas[i-1]->nNumNeuronas; k++) // Por cada neurona de la capa anterior
			{
				//Creamos variables simplificadas para deltaW (incremento) y para ultimoDeltaw (incrementoAnterior)
				incremento = pCapas[i]->pNeuronas[j]->deltaW[k];
				incrementoAnterior = pCapas[i]->pNeuronas[j]->ultimoDeltaW[k];

				pCapas[i]->pNeuronas[j]->w[k] += -((dEta * pDecremento * incremento) + (dMu * (dEta * pDecremento * incrementoAnterior))); // AQUI TENER CUIDADO CON EL SESGO (pNeuronas[k-1]->x)
				// cout<<"ajuste de Peso i["<<i<<"], j["<< j <<"], k["<< k <<"] = "<< pCapas[i]->pNeuronas[j]->w[k]<<endl;
			}
			incremento = pCapas[i]->pNeuronas[j]->deltaW[0];
			incrementoAnterior = pCapas[i]->pNeuronas[j]->ultimoDeltaW[0];

			pCapas[i]->pNeuronas[j]->w[0] += -((dEta * pDecremento * incremento) + (dMu * (dEta * pDecremento * incrementoAnterior))); // Sesgo
			// cout<<"ajuste de Sesgo i["<< i <<"], j["<< j <<"] = "<< pCapas[i]->pNeuronas[j]->w[0];
			//cout<<endl;
		}
	}

	return;
}

void PerceptronMulticapa::ajustarPesosOffline()
{
	// Por legibilidad
	double incremento;
	double incrementoAnterior;

	double pDecremento=0;

	for(int i = 1; i < nNumCapas; i++) // Por cada capa (sin contar la de entrada)
	{
		pDecremento= pow(dDecremento, -(nNumCapas-i-1));

		for(int j = 0; j < pCapas[i]->nNumNeuronas; j++) // Por cada neurona de la capa
		{
			for(int k = 1; k <= pCapas[i-1]->nNumNeuronas; k++) // Por cada neurona de la capa anterior
			{
				//Creamos variables simplificadas para deltaW (incremento) y para ultimoDeltaw (incrementoAnterior)
				incremento = pCapas[i]->pNeuronas[j]->deltaW[k];
				incrementoAnterior = pCapas[i]->pNeuronas[j]->ultimoDeltaW[k];

				pCapas[i]->pNeuronas[j]->w[k] += -((dEta * pDecremento * incremento)/nNumPatronesTrain + (dMu * (dEta * pDecremento * incrementoAnterior))/nNumPatronesTrain); // AQUI TENER CUIDADO CON EL SESGO (pNeuronas[k-1]->x)
				// cout<<"ajuste de Peso i["<<i<<"], j["<< j <<"], k["<< k <<"] = "<< pCapas[i]->pNeuronas[j]->w[k]<<endl;
			}
			incremento = pCapas[i]->pNeuronas[j]->deltaW[0];
			incrementoAnterior = pCapas[i]->pNeuronas[j]->ultimoDeltaW[0];

			pCapas[i]->pNeuronas[j]->w[0] += -((dEta * pDecremento * incremento)/nNumPatronesTrain + (dMu * (dEta * pDecremento * incrementoAnterior))/nNumPatronesTrain); // Sesgo
			// cout<<"ajuste de Sesgo i["<< i <<"], j["<< j <<"] = "<< pCapas[i]->pNeuronas[j]->w[0];
			//cout<<endl;
		}
	}

	return;
}

// ------------------------------
// Imprimir la red, es decir, todas las matrices de pesos
void PerceptronMulticapa::imprimirRed()
{
	cout<<"\nImprimir Red\n"<<endl;

	for(int i = 1; i < nNumCapas; i++) // Por cada capa empezando por la primera oculta
	{
		cout<<"\n * Capa i = "<<i<<endl;
		for(int j = 0; j < pCapas[i]->nNumNeuronas; j++) // Por cada neurona de esa capa
		{
			cout<<"\n\t+ Neurona j = "<<j<<" de capa i = "<<i<<endl;
			for(int k = 0; k < (pCapas[i-1]->nNumNeuronas)+1; k++) // Por cada neurona de la capa anterior
			{
				cout<<"\n\t\t -peso["<< k <<"] = "<<pCapas[i]->pNeuronas[j]->w[k]<<endl;
			}
			cout<<endl;
		}
		//cout<<"\nSiguiente capa"<<endl;
	}
}

// ------------------------------
/*
	* Simular la red
		- Propagar las entradas hacia delante
		- Retropropagar el error 
		- Ajustar los pesos
	- entradas es el vector de entradas del patrón
	- salidasEsperadas es el vector de salidas deseadas del patrón	
*/
void PerceptronMulticapa::simularRed(double* entradas, double* salidasEsperadas)
{
	if(bOnline)
	{
		// Inicializar vector deltaW
		inicializarDeltaW();
	}

	// Alimentar entradas
	alimentarEntradas(entradas);

	// Propagar Entradas
	propagarEntradas();

	// Retropropagar el Error
	retropropagarError(salidasEsperadas);

	// Acumular Cambio
	acumularCambio();

	if(bOnline)
	{
		// Ajustar Pesos
		ajustarPesos();
	}

	return;
}



// ------------------------------
// Leer una matriz de datos a partir de un nombre de fichero y devolverla
Datos* PerceptronMulticapa::leerDatos(const char *archivo) {


	return NULL;
}

// ------------------------------
// Entrenar la red para un determinado fichero de datos
void PerceptronMulticapa::entrenar(Datos* pDatostrain)
{
	if(!bOnline) // Si es offline
		inicializarDeltaW();

	for(int i = 0; i < pDatostrain->nNumPatrones; i++)
		simularRed(pDatostrain->entradas[i], pDatostrain->salidas[i]);

	if(!bOnline) // Si es offline
		ajustarPesosOffline();
}

// ------------------------------

/*
	Probar la red con un conjunto de datos y devolver el error cometido
*/
double PerceptronMulticapa::test(Datos* pDatosTest)
{
	double error = 0.0;

	for (int i = 0; i < pDatosTest->nNumPatrones; i++) // Por cada patron de la base de datos
	{
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		error += calcularErrorSalida(pDatosTest->salidas[i]);
	}

	if(funcionErrorEntropia)
	{
		error /= -(pDatosTest->nNumPatrones * pDatosTest->nNumSalidas);
	}
	else // MSE
	{
		error /= pDatosTest->nNumPatrones;
	}

	return error;
}


/*
	* Probar la red con un conjunto de datos y devolver el CCR
*/
double PerceptronMulticapa::testClassification(Datos* pDatosTest)
{
	double CCR = 0.0;

	int N = pDatosTest->nNumPatrones;
	double sumatorio = 0.0;
	bool iguales = 0;
	int claseObtenida = 0;
	int claseDeseada = 0;

	int numSalidas = pCapas[nNumCapas-1]->nNumNeuronas;
	double * salidasObtenidas = new double[numSalidas];

	// Se realiza el test
	
	for (int i = 0; i < pDatosTest->nNumPatrones; i++) // patron i
	{
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		recogerSalidas(salidasObtenidas);

		claseDeseada = argmax(pDatosTest->salidas[i], numSalidas); // Te devuelve la posicion de la salida
		claseObtenida = argmax(salidasObtenidas, numSalidas);

		// cout<<"Clase Deseada: "<< claseDeseada;
		// cout<<"; Clase Obtenida: "<< claseObtenida <<endl;

		iguales = claseObtenida == claseDeseada;

		sumatorio += iguales;
	}

	CCR = (sumatorio / N) * 100;

	return CCR;
}

/*
	* Probar la red con un conjunto de datos y devolver el CCR (versión sobrecargada)

	* guardarPatrones indica si se desea guardar los patrones mal clasificados en un archivo csv
		- Cada linea de este patron es un patron
		- El primer caracter antes de una coma es la letra que ha predicho erroneamente
		- El último caracter es el número del patrón de test
		- Los números de enmedio son las entradas del patron (o pixeles de la imágen)
*/
double PerceptronMulticapa::testClassification(Datos* pDatosTest, bool guardarPatrones)
{
	double CCR = 0.0;

	int N = pDatosTest->nNumPatrones;
	double sumatorio = 0.0;
	bool iguales = 0;
	int claseObtenida = 0;
	int claseDeseada = 0;

	int numSalidas = pCapas[nNumCapas-1]->nNumNeuronas;
	double * salidasObtenidas = new double[numSalidas];

	// Para los patrones mal clasificados
	char letraMalPredicha = 'A';

	// Archivo donde se guardarán los patrones mal clasificados
	char nombreArchivo[] = "patrones_mal_clasificados.csv";
	ofstream f(nombreArchivo);

	if(!f.is_open())
	{
		cerr<<"El archivo para guardar los patrones mal clasificados no ha podido abrirse"<<endl;
		return false;
	}

	// Se realiza el test
	
	for (int i = 0; i < pDatosTest->nNumPatrones; i++) // patron i
	{
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		recogerSalidas(salidasObtenidas);

		claseDeseada = argmax(pDatosTest->salidas[i], numSalidas); // Te devuelve la posicion de la salida
		claseObtenida = argmax(salidasObtenidas, numSalidas);

		// cout<<"Clase Deseada: "<< claseDeseada;
		// cout<<"; Clase Obtenida: "<< claseObtenida <<endl;

		iguales = claseObtenida == claseDeseada;

		if(!iguales) // Si no son iguales, ha habido un fallo, y se debe copiar el patron para su posterior analisis
		{
			letraMalPredicha = 'A';
			letraMalPredicha += claseObtenida;

			f << letraMalPredicha;
			f << ',';

			for(int j = 0; j < pCapas[0]->nNumNeuronas; j++) // neurona de la primera capa j
			{
				// La salida será igual a la entrada correspondiente
				f << pDatosTest->entradas[i][j];
				f << ',';
				// cout<<"La entrada de la neurona "<<i<<" de la capa de entrada es: "<<pCapas[0]->pNeuronas[i]->x <<endl;
			}

			f << i;
			f << endl;
		}

		sumatorio += iguales;
	}

	f.close();
	CCR = (sumatorio / N) * 100;

	return CCR;
}



// OPCIONAL - KAGGLE
// Imprime las salidas predichas para un conjunto de datos.
// Utiliza el formato de Kaggle: dos columnas (Id y Predicted)
bool PerceptronMulticapa::predecir(Datos* pDatosTest)
{
	cout<<"predecir"<<endl;

	int clasePredicha = 0;

	// Objeto de escritura de fichero
	char archivo[] = "IMC1819p92supeg.csv"; 
	ofstream f(archivo);

	if(!f.is_open())
		return false;

	int numSalidas = pCapas[nNumCapas-1]->nNumNeuronas;
	double * salidas = new double[numSalidas];
	
	f << "Id,Category" << endl;
	
	for (int i = 0; i < pDatosTest->nNumPatrones; i++)
	{
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		recogerSalidas(salidas);
		clasePredicha = argmax(salidas, numSalidas);

		f << i;
		f << "," << clasePredicha;
		f << endl;
	}

	f.close();

	cout<<"fin predecir"<<endl;

	return true;
}

// ------------------------------
// Ejecutar el algoritmo de entrenamiento durante un número de iteraciones, utilizando pDatostrain
// Una vez terminado, probar como funciona la red en pDatosTest
// Tanto el error MSE de entrenamiento como el error MSE de test debe calcularse y almacenarse en errorTrain y errorTest
void PerceptronMulticapa::ejecutarAlgoritmo(Datos * pDatostrain, Datos * pDatosTest, const Configuracion * parametros, double *errorTrain, double *errorTest, double *ccrTrain, double *ccrTest, double &iteracionesRealizadas, int semilla)
{
	int maxiter = parametros->iteraciones;

	int countTrain = 0;

	// Inicialización de pesos
	pesosAleatorios();

	int numSinMejorar = 0;

	double minTrainError = 0;
	double testError = 0;
	double CCR = 0;
	double validationError = 0;
	
	nNumPatronesTrain = pDatostrain->nNumPatrones;
	double previousValidationError = 0;

	Datos * pDatosValidacion = NULL;
	Datos * pDatostrain_nuevo = NULL;
	Datos * aux = NULL;

	bool modoValidacion = false;

	/*
	string str = "";
	string s = "";

	ostringstream ss; // Sirve para introducir numeros

	// 
	ss.str("");
	ss << semilla;
	s = ss.str();
	str += s;

	str += " _ ";
	str += crearNombreFichero(parametros->tvalue, parametros);

	ofstream convergencia(str.c_str()); // Aqui van los datos de convergencia
	*/

	// Generar datos de validación
	if(dValidacion > 0 && dValidacion < 1)
	{
		if(pDatostrain->nNumPatrones * dValidacion > 1.0) // Tiene que haber patrones suficientes para respetar la proporcion
		{
			pDatosValidacion = generarDatosValidacion(pDatostrain, pDatosValidacion, aux);
			modoValidacion = true;
		}
	}

	//cout<<"Los datos de train son: "<<endl;
	//escribirDatos(pDatostrain);

	/* INICIAR ENTRENAMIENTO DE LA RED NEURONAL */

	int numSinMejorarValidacion = 0;

	do
	{
		// Entrena la red con los datos de entrenamiento en esta iteracion
		nNumPatronesTrain = pDatostrain->nNumPatrones;
		entrenar(pDatostrain);
		double trainError = test(pDatostrain);

		if(countTrain==0 || trainError < minTrainError)
		{
			minTrainError = trainError;
			copiarPesos();
			numSinMejorar = 0;
		}
		else if( (trainError-minTrainError) < 0.00001) // 0.000005
			numSinMejorar = 0;
		else
			numSinMejorar++;

		if(numSinMejorar == 50)
		{
			cout << "Salida porque no disminuye el error de entrenamiento"<< endl;
			restaurarPesos();
			countTrain = maxiter;
		}

		// Comprobar condiciones de parada de validación y forzar
		// OJO: en este caso debemos guardar el error de validación anterior, no el mínimo
		// Por lo demás, la forma en que se debe comprobar la condición de parada es similar
		// a la que se ha aplicado más arriba para el error de entrenamiento

		// USO DEL CONJUNTO DE VALIDACION

		if(modoValidacion) // Si hay conjunto de validacion
		{
			previousValidationError = validationError;
			validationError = test(pDatosValidacion); // Calcula el error de validacion actual

			if(validationError <= previousValidationError) // El error de validacion ha disminuido respecto al anterior?
			{
				numSinMejorarValidacion = 0;
			}
			else if( (validationError-previousValidationError) < 0.00001) // 0.000005
			{
				numSinMejorarValidacion = 0;
			}
			else
				numSinMejorarValidacion++;
		}

		if(numSinMejorarValidacion == 50)
		{
			cout << "Salida por Sobreentrenamiento"<< endl;
			restaurarPesos();
			countTrain = maxiter;
		}

		countTrain++;

		testError = test(pDatosTest);
		CCR = testClassification(pDatosTest);

		cout<< "Iteración " << countTrain << "\t Error de entrenamiento: " << trainError << "\t Error de validación: " << validationError <<"\t Error de test: " << testError <<"\t CCR: " << CCR << endl;
		// convergencia << countTrain <<" "<< trainError <<" "<< validationError <<" "<< testError <<" "<< CCR <<endl;

		iteracionesRealizadas++;

	} while ( countTrain < maxiter );

	// Fin aprendizaje del algoritmo

	/*

	cout << "PESOS DE LA RED" << endl;
	cout << "===============" << endl;
	//imprimirRed();

	cout << "Salida Esperada Vs Salida Obtenida (test)" << endl;
	cout << "=========================================" << endl;
	
	// Probamos el conjunto de test
	for(int i=0; i<pDatosTest->nNumPatrones; i++)
	{
		double* prediccion = new double[pDatosTest->nNumSalidas];

		// Cargamos las entradas y propagamos el valor
		alimentarEntradas(pDatosTest->entradas[i]);
		propagarEntradas();
		recogerSalidas(prediccion);

		for(int j=0; j<pDatosTest->nNumSalidas; j++)
			cout << pDatosTest->salidas[i][j] << " -- " << prediccion[j] << " ";

		cout << endl;
		delete[] prediccion;
	}
	*/

	// Probamos el conjunto de test
	testError = test(pDatosTest);

	// Restauro los punteros en el caso de que haya conjunto de validacion y libero memoria
	if(modoValidacion)
	{
		pDatostrain_nuevo = pDatostrain;
		pDatostrain = aux;
		delete pDatostrain_nuevo;
		delete pDatosValidacion;
		
		pDatostrain_nuevo = NULL;
		pDatostrain_nuevo = NULL;
	}

	*errorTest=testError;
	*errorTrain=minTrainError;

	/*
	// Esto sirve para imprimir los patrones mal clasificados  (solo con la mejor semilla)

	if(semilla == mejorSemilla)
		*ccrTest = testClassification(pDatosTest, true);
	else
		*ccrTest = testClassification(pDatosTest);
	
	*/
	*ccrTest = testClassification(pDatosTest);
	*ccrTrain = testClassification(pDatostrain);

	// convergencia.close();
}

void PerceptronMulticapa::establecerConfiguracion(const Configuracion * parametros)
{
	// cout<<"establecerConfiguracion"<<endl;
	
	dEta = parametros->dEta;       
	dMu = parametros->dMu;
	dValidacion = parametros->dValidacion;
	dDecremento = parametros->dDecremento;
	nNumCapas = parametros->l + 2; // capa de salida, capa de entrada y capas ocultas
	nNumNeuronasCapaOculta = parametros->h;
	bOnline = parametros->oflag;
	funcionErrorEntropia = parametros->fflag;
	funcionSalidaSoftmax = parametros->sflag;

	// cout<<"fin establecerConfiguracion"<<endl;

	return;
}

// OPCIONAL - KAGGLE
//Guardar los pesos del modelo en un fichero de texto.
bool PerceptronMulticapa::guardarPesos(const char * archivo)
{
	cout<<"guardarPesos"<<endl;
	// Objeto de escritura de fichero
	ofstream f(archivo);

	if(!f.is_open())
		return false;

	// Escribir el numero de capas y el numero de neuronas en cada capa en la primera linea.
	f << nNumCapas;

	for(int i = 0; i < nNumCapas; i++)
		f << " " << pCapas[i]->nNumNeuronas;
	f << endl;

	// Escribir los pesos de cada capa
	for(int i = 1; i < nNumCapas; i++)
		for(int j = 0; j < pCapas[i]->nNumNeuronas; j++)
			for(int k = 0; k < pCapas[i-1]->nNumNeuronas + 1; k++)
				f << pCapas[i]->pNeuronas[j]->w[k] << " ";

	f.close();

	cout<<"fin guardarPesos"<<endl;

	return true;
}

// OPCIONAL - KAGGLE
//Cargar los pesos del modelo desde un fichero de texto.
bool PerceptronMulticapa::cargarPesos(const char * archivo)
{
	// Objeto de lectura de fichero
	ifstream f(archivo);

	if(!f.is_open())
		return false;

	// Leer pesos.
	for(int i = 1; i < nNumCapas; i++)
		for(int j = 0; j < pCapas[i]->nNumNeuronas; j++)
			for(int k = 0; k < pCapas[i-1]->nNumNeuronas + 1; k++)
				f >> pCapas[i]->pNeuronas[j]->w[k];

	f.close();

	return true;
}