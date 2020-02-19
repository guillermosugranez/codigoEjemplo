/*
 * util.cpp
 *
 *  Created on: 21 sept. 2018
 *      Author: guillermo
 */

#include "util.h"

using namespace std;
using namespace util;

/*
	Comprueba la extension
	Si no es correcta manda un error
	Si es correcta manda true
*/
bool util::comprobarExtensionFichero(string nombreFichero)
{
	string extension;
	int tamNombre = nombreFichero.size(); // Calculo el tamaño de la cadena

	if(tamNombre > 4)
		extension = nombreFichero.substr(tamNombre-4, tamNombre); // Extraigo las ultimas 4 letras del nombre del fichero

	// cout<<"La extension es: \""<< extension <<"\""<<endl;

	if(extension == ".dat")
	{
		return 1; // Extension correcta
	}
	else
	{
		cerr<<" ERROR: La extension de \""<<nombreFichero<<"\" no es valida. (solo archivos .dat)"<<endl;
		return 0;
	}
}

/*
	Comprueba la cadena optarg
	Se asegura que es un entero mayor que 0
	Si es así cambia el valor del entero
*/
bool util::comprobarInt(char * cadena, int &n)
{
	int aux = atoi(cadena);
	if(aux > 0)
	{
		n = aux;
		return 1;
	}
	else
	{
		cerr<<" ERROR: El valor "<<aux<<" no es valido. Restaurando valor por defecto..."<<endl;
		return 0;
	}
}

/*
	Comprueba la cadena optarg, y se asegura que es un float mayor que min y menor que max
*/
bool util::comprobarFloat(char * cadena, float min, float max, float &n)
{
	string cadenaAux = cadena;
	float aux = strtof((cadenaAux).c_str(), 0); // string to float
	if(aux >= min && aux <= max)
	{
		// cout<<"float = "<<aux<<endl;
		n = aux;
		return 1;
	}
	else
	{
		cerr<<" ERROR: El valor "<<aux<<" no es valido. Restaurando valor por defecto..."<<endl;
		return 0;
	}
}

void util::configuracionPorDefecto(Configuracion * parametros)
{
	// cout<<"Configuracion por defecto"<<endl;

	// PRACTICA 1

	parametros->tvalue = NULL; // Nombre de fichero de Test
	parametros->Tvalue = NULL;

	parametros->iteraciones = 1000; // Numero de iteraciones del bucle externo a realizar (por defecto 1000)
	parametros->l = 1; // Numero de capas ocultas (por defecto 1)
	parametros->h = 5; // Numero de neuronas a introducir en cada una de las capas ocultas (por defecto 5)

	parametros->dEta = 0.7; // Valor del parametro eta (por defecto 0.7)
	parametros->dMu = 1.0; // Valor del parametro Mu (por defecto 1.0)
	parametros->dValidacion = 0.1; // Ratio de patrones de test a utilizar como patrones de validacion (por defecto 0.1)
	parametros->dDecremento = 1.0; // Factor de decremento a usar para cada una de las capas (F=1)

	// Flags
	parametros->tflag = false; // Flag de nombre de fichero de ENTRENAMIENTO correcto
	parametros->Tflag = false; // Flag de nombre de fichero de TEST correcto

	parametros->iflag = false;
	parametros->lflag = false;
	parametros->hflag = false;
	parametros->eflag = false; // eta
	parametros->mflag = false; // mu
	parametros->vflag = false;
	parametros->dflag = false; // F

	parametros->wflag = false;
	parametros->pflag = false;

	parametros->wvalue = NULL;

	// PRACTICA 2

	parametros->oflag = false;
	parametros->fflag = false;
	parametros->sflag = false;

	// cout<<"Fin configuracion por defecto"<<endl;

	return;
}

bool util::procesarLineaComandos(int &argc, char **argv, Configuracion * parametros)
{
	configuracionPorDefecto(parametros);

	// Parametros para getopt
	int index;
	int c;
	opterr = 0;
	// char *dvalue = NULL; // Resto de argumentos que no han podido ser procesados

	/*
		- Las variables optind, optarg y optopt las declara y actualiza implíticamente getopt()
		- ':' indica que 'c' tiene un argumento obligatorio, si pusiéramos '::' indicaría que el argumento de 'c' es opcional
	*/
	while ((c = getopt (argc, argv, "T:i:l:h:e:m:v:d:t:w:p::o::f::s::")) != -1)
	{
		/*
			Podemos observar qué pasa con las variables externas que va gestionando getopt() durante las sucesivas llamadas
			printf("\noptind: %d, optarg: %s, optopt: %c\n", optind, optarg, optopt);
		*/

		switch (c)
		{
		case 't':
			parametros->tvalue = new char[strlen(optarg) + 1];
			strcpy(parametros->tvalue, optarg);
			parametros->tflag = true;
			break;
		case 'T':
			parametros->Tvalue = new char[strlen(optarg) + 1];
			strcpy(parametros->Tvalue, optarg);
			parametros->Tflag = true;
			break;
		case 'w':
			parametros->wvalue = new char[strlen(optarg) + 1];
			strcpy(parametros->wvalue, optarg);
			parametros->wflag = true;
			break;
		case 'p':
			parametros->pflag = true;
			break;
		case 'o':
			parametros->oflag = true;
			break;
		case 'f':
			parametros->fflag = true;
			break;
		case 's':
			parametros->sflag = true;
			break;
		case 'i':
			parametros->iflag = comprobarInt(optarg, parametros->iteraciones);
			break;
		case 'l':
			parametros->lflag = comprobarInt(optarg, parametros->l);
			break;
		case 'h':
			parametros->hflag = comprobarInt(optarg, parametros->h);
			break;
		case 'e':
			parametros->eflag = comprobarFloat(optarg, 0, 1, parametros->dEta);
			break;
		case 'm':
			parametros->mflag = comprobarFloat(optarg, 0, 1, parametros->dMu);
			break;
		case 'v':
			parametros->vflag = comprobarFloat(optarg, 0, 1, parametros->dValidacion);
			break;
		case 'd':
			parametros->dflag = comprobarFloat(optarg, 0, 5, parametros->dDecremento);
			break;
		case '?':
			if (optopt == 't' || optopt == 'T' || optopt == 'i' || optopt == 'l' || optopt == 'h' || optopt == 'e' || optopt == 'm' || optopt == 'v' || optopt == 'd' || optopt == 'w' || optopt == 'p')
				fprintf (stderr, " ERROR: La opcion -%c requiere un argumento.\n", optopt);
			else if (isprint (optopt))
				fprintf (stderr, " ERROR: Opcion desconocida `-%c'.\n", optopt);
			else
				fprintf (stderr, " ERROR: Caracter de opcion desconocido `\\x%x'.\n", optopt);
			return 0;
		default:
			abort ();
		}

		// cout<<"\n Linea de comandos procesada con éxito\n"<<endl;
	}

	if(!parametros->pflag)
	{
		// Fichero de entrenamiento correcto
		if(parametros->tflag) // Debe haberse procesado -t correctamente
		{
			// Comprueba que sea un fichero valido
			if(not comprobarExtensionFichero(parametros->tvalue))
			{
				cerr<<"\n\t -> Debe especificarse un nombre de fichero de Entrenamiento correcto."<<endl;
				return 0; // Salir del programa
			}
		}
		else
		{
			cerr<<"\n\t -> Debe especificarse un nombre de fichero de Entrenamiento correcto."<<endl;
			return 0; // Salir del programa
		}
	}

	// Fichero de Test
	if(parametros->Tflag)
	{
		if(not comprobarExtensionFichero(parametros->Tvalue))
		{
			cout<<"\n\t -> El nombre del fichero de Test es incorrecto (Se usara el conjunto de Entrenamiento como Test)."<<endl;
			parametros->Tvalue = parametros->tvalue;
		}
	}

	// printf ("Tvalue = %s, iflag = %d, lflag = %d, hflag = %d, eflag = %d, mflag = %d, vflag = %d, dflag = %d, tvalue = %s, dvalue = %s\n", Tvalue, iflag, lflag, hflag, eflag, mflag, vflag, dflag, tvalue, dvalue);

	/*
		Esta secuencia controla opciones introducidas por el usuario/a que no hayan sido procesadas.
		Compara el número de argumentos recibidos con el número de opciones reconocidas.
		Como getop() internamente reordena los valores de argv
			las primeras posiciones de argv corresponden a opciones conocidas
			las últimas, a partir de optind, a opciones no reconocidas
	*/
	for (index = optind; index < argc; index++)
		printf ("Non-option argument %s\n", argv[index]);

	return 1;
}

void util::mostrarConfiguracion(const Configuracion * parametros)
{
	cout<<"\n\t================"<<endl;
	cout<<"\tt = "<<parametros->tvalue<<endl;
	if(parametros->Tflag)
		cout<<"\tT = "<<parametros->Tvalue<<endl;
	cout<<"\ti = "<<parametros->iteraciones<<endl;
	cout<<"\tl = "<<parametros->l<<endl;
	cout<<"\th = "<<parametros->h<<endl;
	cout<<"\te = "<<parametros->dEta<<endl;
	cout<<"\tm = "<<parametros->dMu<<endl;
	cout<<"\tv = "<<parametros->dValidacion<<endl;
	cout<<"\td = "<<parametros->dDecremento<<endl;
	if(parametros->wflag)
		cout<<"\tw = "<<parametros->wvalue<<endl;
	cout<<"\t================\n"<<endl;

	return;
}

double ** util::reservarMemoria(int patrones, int columnas)
{
	// Datos de ENTRADA
	double ** v = new double*[patrones];

	for (int i = 0; i < patrones; i++)
		v[i] = new double[columnas];

	return v;
}

/*
	* Copia un patron de un conjunto origen a uno destino
		- El elemento a copiar se determina con un indice
		- Se determina tambien la posicion del vector destino donde insertar
		- Se copian tanto las entradas del patron como las salidas
*/
void util::copiarPatron(Datos * origen, Datos * destino, int indicePatron, int posicion)
{
	// cout<<"copiarPatron"<<endl;

	for(int i = 0; i < origen->nNumEntradas; i++)
		destino->entradas[posicion][i] = origen->entradas[indicePatron][i];

	for(int i = 0; i < origen->nNumSalidas; i++)
		destino->salidas[posicion][i] = origen->salidas[indicePatron][i];

	// cout<<"fin copiarPatron"<<endl;

	return;
}

bool util::leerBaseDeDatos(const char * nombreFichero, Datos &data)
{
	float aux = 0.0;

	ifstream ficheroEntrada(nombreFichero);

	// Procesar primera linea
	if (ficheroEntrada.is_open())
	{
		// Leer primera linea
		ficheroEntrada >> data.nNumEntradas >> data.nNumSalidas >> data.nNumPatrones;
		// cout<<"nNumEntradas = "<<data.nNumEntradas<<", nNumSalidas = "<<data.nNumSalidas<<", nNumPatrones = "<<data.nNumPatrones<<endl;
	}
	else
	{
		cerr<<"No se ha podido abrir el fichero"<<endl;
		return 0; // Mandamos un error
	}

	// RESERVA DE MEMORIA PARA LAS MATRICES
	data.entradas = reservarMemoria(data.nNumPatrones, data.nNumEntradas);
	data.salidas = reservarMemoria(data.nNumPatrones, data.nNumSalidas);

	// RELLENAR MATRICES

	for(int i = 0; i < data.nNumPatrones; i++) // Por cada linea
	{
		for(int j = 0; j < data.nNumEntradas + data.nNumSalidas; j++) // Proceso cada columna
		{
			ficheroEntrada >> aux;
			//cout<<aux<<" ";

			if(j < data.nNumEntradas)
				data.entradas[i][j] = aux;
			else
				data.salidas[i][j-data.nNumEntradas] = aux;
		}
		//cout<<endl; // Nueva linea
	}

	return 1; // Todo correcto
}

bool util::borrarBaseDeDatos(Datos * data)
{
	//cout<<"Borrando datos..."<<endl;
	for(int i = 0; i<data->nNumPatrones; i++)
	{
		delete[] data->salidas[i];
		delete[] data->entradas[i];
	}

	delete[] data->entradas;
	delete[] data->salidas;

	data->entradas = 0;
	data->salidas = 0;

	return true;
}

void util::escribirDatos(const Datos * data)
{
	cout<<"escribirDatos"<<endl;

	for(int i = 0; i < data->nNumPatrones; i++)
	{
		for(int j = 0; j < data->nNumEntradas; j++)
			cout<<data->entradas[i][j]<<" ";

		cout<<" | ";

		for(int k = 0; k < data->nNumSalidas; k++)
			cout<<data->salidas[i][k]<<" ";

		cout<<endl;
	}

	cout<<"fin escribirDatos"<<endl;

	return;
}

double util::fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

string util::crearNombreFichero(char * nombreFichero, const Configuracion * parametros)
{
	string str = "";

	string s(nombreFichero);

	size_t found = s.find_last_of("/\\");
	s = s.substr(found+1);

	found = s.find_last_of(".\\");
	s = s.substr(0,found);

	// Nombre del Problema
	found = s.find_last_of("_\\");
	s = s.substr(found+1);
	str += s;

	str += "  {";

	ostringstream ss; // Sirve para introducir numeros

	// Número de Capas
	ss.str("");
	ss << parametros->l;
	s = ss.str();
	str += s;

	str += " : ";

	// Numero de Neuronas
	ss.str("");
	ss << parametros->h;
	s = ss.str();
	str += s;

	str += "}  v=";

	// Ratio de patrones de validacion
	ss.str("");
	ss << parametros->dValidacion;
	s = ss.str();
	str += s;

	str += "  d=";

	// Factor de Decremento
	ss.str("");
	ss << parametros->dDecremento;
	s = ss.str();
	str += s;

	// Funcion de error
	ss.str("");
	if(parametros->fflag)
		str += ", L";
	else
		str += ", MSE";

	// Neuronas de la capa de salida
	ss.str("");
	if(parametros->sflag)
		str += ", Soft";
	else
		str += ", Sig";

	// Versión del algoritmo
	ss.str("");
	if(parametros->oflag)
		str += ", On";
	else
		str += ", Off";	

	// Extension
	//str += ".txt";

	// cout<<"El nombre del fichero es: "<< str <<endl;

	return str;
}

/*
	* Funcion para rellenar un vector de enteros sin repeticion
	 - Devuelve un puntero al un vector de enteros aleatorios
	 - 
*/
int * util::vectorAleatoriosEnterosSinRepeticion(int minimo, int maximo, int cuantos)
{
	int total = maximo-minimo+1;
	int* numerosPorElegir = new int[total];
	int* numerosElegidos = new int[cuantos];
	// Inicializar la lista de elecciones posibles
	for(int i = 0; i < total; i++)
		numerosPorElegir[i] = minimo+i;

	for(int i=0; i < cuantos; i++)
	{
		int numeroElegido = rand() % (total-i);
		// Recordar el numero elegido
		numerosElegidos[i]=numerosPorElegir[numeroElegido];
		// Ponemos en numeros por elegir, el ultimo que era valido, asi
		// son todos validos hasta data->n-i-1
		numerosPorElegir[numeroElegido]=numerosPorElegir[total-i-1];
	}

	return numerosElegidos;
};

/*
	Devuelve la sigmoide una vez pasada la suma ponderada de las entradas de la neurona j en la capa h (net^h_j)
*/
double util::sigmoide(double net)
{
	// cout<<"sigmoide"<<endl;

	return 1 / (1 + exp(-net));

	// cout<<"fin sigmoide"<<endl;
}

/*
	Recive un vector y devuelve la posicion del elemento máximo del vector
*/
int util::argmax(double * v, int tam)
{
	int posicion = 0;
	double max = 0.0;

	for(int i = 0; i < tam; i++)
	{
		if(v[i] > max)
		{
			max = v[i];
			posicion = i;
		}
	}

	return posicion;
}