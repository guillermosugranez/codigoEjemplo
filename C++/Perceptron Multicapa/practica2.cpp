//============================================================================
// Introducción a los Modelos Computacionales
// Name        : practica1.cpp
// Author      : Pedro A. Gutiérrez
// Version     :
// Copyright   : Universidad de Córdoba
//============================================================================

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <iostream>
#include <ctime>    // Para coger la hora time()
#include <cstdlib>  // Para establecer la semilla srand() y generar números aleatorios rand()
#include <string.h>
#include <math.h>

#include "imc/PerceptronMulticapa.h"
#include "imc/util.h"

using namespace imc;
using namespace std;
using namespace util;

int main(int argc, char **argv)
{
	Configuracion * parametros = new Configuracion; // Guarda la configuracion de los parametros de getopt()

	// Procesar los argumentos de la línea de comandos
	if(!procesarLineaComandos(argc, argv, parametros))
	{
		cerr<<"\n Error al procesar la linea de comandos. Saliendo..."<<endl;
		exit(1);
	}

	// Objeto perceptrón multicapa
	PerceptronMulticapa mlp;

	// Establecer parámetros del mlp. Por ejemplo, mlp.dEta = valorQueSea;
	mlp.establecerConfiguracion(parametros);
	//mostrarConfiguracion(parametros);


	Datos * pDatosTest = new Datos; // Datos de Test
	
	if(parametros->Tflag) // Solo si se ha introducido un nombre de fichero de Test valido
	{
		if(not leerBaseDeDatos(parametros->Tvalue, (*pDatosTest))) // Guardo resultados
		{
			cerr<<" ERROR: Hubo un problema al leer la base de datos de test. Saliendo..."<<endl;
			return 0;
		}
	}

	// escribirDatos(pDatosTest);
	
	// Inicializar red
	mlp.inicializar(pDatosTest->nNumEntradas, pDatosTest->nNumSalidas);

	// cout<<"El número de patrones de la base de datos de Test es: "<<pDatosTest->nNumPatrones<<endl;
	// cout<<"El número de entradas de la red es: "<<pDatosTest->nNumEntradas<<endl;
	// cout<<"El número de salidas de la red es: "<<pDatosTest->nNumSalidas<<endl;

	if(!parametros->pflag)
	{
		////////////////////////////////////////
		// MODO DE ENTRENAMIENTO Y EVALUACIÓN //
		///////////////////////////////////////

		// Datos de entrenamiento
		Datos * pDatostrain = new Datos;
		double iteracionesRealizadas = 0;

		// Lectura de datos de entrenamiento
		if(not leerBaseDeDatos(parametros->tvalue, (*pDatostrain)))
		{
			cerr<<" ERROR: Hubo un problema al leer la base de datos de entrenamiento. Saliendo..."<<endl;
			return 0;
		}

		int semillas[] = {100,200,300,400,500};

		double *erroresTest = new double[5];
		double *erroresTrain = new double[5];

		double *ccrs = new double[5];
		double *ccrsTrain = new double[5];

		double mejorErrorTest = 1.0;

		for(int i = 0; i < 5; i++)
		{
			cout << "**********" << endl;
			cout << "SEMILLA " << semillas[i] << endl;
			cout << "**********" << endl;
			srand(semillas[i]);

			/* EJECUCION DEL ALGORITMO ONLINE */
			mlp.ejecutarAlgoritmo(pDatostrain, pDatosTest, parametros, &(erroresTrain[i]), &(erroresTest[i]), &(ccrsTrain[i]), &(ccrs[i]), iteracionesRealizadas, semillas[i]);

			cout << "Finalizamos => CCR de test final: " << ccrs[i] << endl;
			cout << "Finalizamos => CCR de train final: " << ccrsTrain[i] << endl;
			cout << "Finalizamos => Error de test final: " << erroresTest[i] << endl;

			// (Opcional - Kaggle) Guardamos los pesos cada vez que encontremos un modelo mejor.
			if(parametros->wflag && erroresTest[i] <= mejorErrorTest)
			{
				mlp.guardarPesos(parametros->wvalue);
				mejorErrorTest = erroresTest[i];
			}
		}

		double mediaErrorTest = 0, desviacionTipicaErrorTest = 0;
		double mediaErrorTrain = 0, desviacionTipicaErrorTrain = 0;
		double mediaCCR = 0, desviacionTipicaCCR = 0;
		double mediaCCRTrain = 0, desviacionTipicaCCRTrain = 0;

		cout << "HEMOS TERMINADO TODAS LAS SEMILLAS" << endl;
		
		// Calcular medias y desviaciones típicas de entrenamiento y test

		int mejorSemilla = 0;
		mejorErrorTest = 0.0;

		for(int i = 0; i < 5; i++)
		{
			// Determinar si esta semilla da la mejor puntuacion de CCR y apuntarlo
			if(ccrs[i] > mejorErrorTest)
			{
				mejorErrorTest = ccrs[i];
				mejorSemilla = semillas[i];
			}

			mediaErrorTest += erroresTest[i];
			mediaErrorTrain += erroresTrain[i];
			mediaCCR += ccrs[i];
			mediaCCRTrain +=ccrsTrain[i];
		}

		mediaErrorTest /= 5;
		mediaErrorTrain /= 5;
		mediaCCR /= 5;
		mediaCCRTrain /= 5;

		// varianzas
		for(int i = 0; i < 5; i++)
		{
			desviacionTipicaErrorTest += pow((erroresTest[i] - mediaErrorTest), 2);
			desviacionTipicaErrorTrain += pow((erroresTrain[i] - mediaErrorTrain), 2);
			desviacionTipicaCCR += pow((ccrs[i] - mediaCCR), 2);
			desviacionTipicaCCRTrain += pow((ccrsTrain[i] - mediaCCRTrain), 2);
		}

		desviacionTipicaErrorTest /= 5;
		desviacionTipicaErrorTrain /= 5;
		desviacionTipicaCCR /= 5;
		desviacionTipicaCCRTrain /= 5;

		desviacionTipicaErrorTest = sqrt(desviacionTipicaErrorTest);
		desviacionTipicaErrorTrain = sqrt(desviacionTipicaErrorTrain);
		desviacionTipicaCCR = sqrt(desviacionTipicaCCR);
		desviacionTipicaCCRTrain = sqrt(desviacionTipicaCCRTrain);

		// Informe de resultados
		cout << "INFORME FINAL" << endl;
		cout << "*************" << endl;
		cout << "Error de entrenamiento (Media +- DT): " << mediaErrorTrain << " +- " << desviacionTipicaErrorTrain << endl;
		cout << "Error de test (Media +- DT):          " << mediaErrorTest << " +- " << desviacionTipicaErrorTest << endl;
		cout << "CCR de entrenamiento (Media +- DT): " << mediaCCRTrain << " +- " << desviacionTipicaCCRTrain << endl;
		cout << "CCR de test (Media +- DT): " << mediaCCR << " +- " << desviacionTipicaCCR << endl;
		cout << "Numero de iteraciones media por semilla = " << iteracionesRealizadas/5 << endl;

		
		// Creacion del archivo de salida con los resultados
		string str = crearNombreFichero(parametros->Tvalue, parametros);

		//cout<<"El nombre del archivo es: "<<str<<endl;
		ofstream archivo_salida(str.c_str());

		archivo_salida << str << ";";
		archivo_salida << mediaErrorTrain <<";"<< desviacionTipicaErrorTrain <<";";
		archivo_salida << mediaErrorTest <<";"<< desviacionTipicaErrorTest <<";";
		archivo_salida << mediaCCRTrain <<";"<< desviacionTipicaCCRTrain <<";";
		archivo_salida << mediaCCR <<";"<< desviacionTipicaCCR <<";";
		archivo_salida << iteracionesRealizadas/5 <<endl;

		archivo_salida.close();
		

		cout<<"La mejor semilla es: "<< mejorSemilla <<endl;

		delete erroresTest;
		delete erroresTrain;
		delete pDatostrain;

		return EXIT_SUCCESS;
	}
	else
	{
		/////////////////////////////////
		// MODO DE PREDICCIÓN (KAGGLE) //
		////////////////////////////////

		// Desde aquí hasta el final del fichero no es necesario modificar nada.

		if(!parametros->wflag || !mlp.cargarPesos(parametros->wvalue))
		{
			cerr << "Error al cargar los pesos. No se puede continuar." << endl;
			exit(-1);
		}

		if(pDatosTest == NULL)
		{
			cerr << "El conjunto de datos de test no es válido. No se puede continuar." << endl;
			exit(-1);
		}

		mlp.predecir(pDatosTest);

		return EXIT_SUCCESS;
	}

	delete parametros;
	delete pDatosTest;

	cout<<"Fin de ejecución\n"<<endl;
	return 0;
}

