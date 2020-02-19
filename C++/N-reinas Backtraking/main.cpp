/*
	Implementad el algoritmo del problema de las n reinas, 
	siendo n un valor introducido por el usuario. El programa podrá tener
	hasta tres opciones, en nivel creciente de dificultad.

	1) Mediante el método del Backtracking. Las soluciones serán guardadas en una estructura 
	de datos adicional que será implementada por el alumno, y después, usando dicha estructura, 
	se mostrarán todas las soluciones.

	(Nota máxima haciendo sólo la opción 1: 7,5)

	2) Mediante el algoritmo de las Vegas visto en clase. Para este caso hay que mostrar 
	obligatoriamente una solución indicando el número de intentos que se han realizado 
	para obtener esa solución La solución se guardará  igual que en la opción anterior.

	(Nota máxima haciendo opciones 1 y 2: 8,5)

	3) Como apartado adicional, el alumno podrá introducir una opción en la que después 
	de obtener todas las soluciones mediante el método del backtracking, 
	compruebe cuantas pruebas serían necesarias para obtener todas las
	soluciones del problema mediante el algoritmo las Vegas.

	((Nota máxima haciendo opciones 1, 2 y 3: 10)
*/

#include <iostream>

#include "funciones.hpp"
#include "estructuraSoluciones.hpp"

using namespace std;

int main()
{
	//====================================================================================
	
	cout<<"\n\tPRACTICA 6 : BACKTRACKING, ALGORITMOS PROBABILISTICOS"<<endl;
	cout<<"\n\t\t Enunciado a: Problema de las n reinas. Opcion 1)\n"<<endl;

	//====================================================================================

	bool prueba = true;
	unsigned int n = 0;

	while(prueba)
	{
		estructuraSoluciones soluciones;
		n = 0;

		cout<<" - Indica el valor de n: ";
		cin>>n;

		//====================================================================================

		cout<<"\n - Para "<<n<<" reinas, las souciones son las siguientes: \n"<<endl;

		nReinas(n, soluciones);
		soluciones.mostrarSoluciones();
		
		cout<<" - En total, se han conseguido "<<soluciones.getnumSoluciones()<<" soluciones. "<<endl;

		cout<<endl;

		repetir(prueba);

		cout<<"\n ===========================================================================\n"<<endl;
	}

	return 0;
}