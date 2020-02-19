#include "estructuraSoluciones.hpp"

#include <iostream>

using namespace std;

/* CONSTRUCTORES  */

	estructuraSoluciones::estructuraSoluciones ()
	{
		numSoluciones = 0;
	}

/* DESTRUCTOR */

	estructuraSoluciones::~estructuraSoluciones()
	{

	}

/* SOBRECARGA DE OPERADORES */

/* MODIFICADORES */

	void estructuraSoluciones::setnumSoluciones(int n)
	{
		numSoluciones = n;
	}

/* OBSERVADORES */

	int estructuraSoluciones::getnumSoluciones()
	{
		return numSoluciones;
	}