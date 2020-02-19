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

	void estructuraSoluciones::meterSolucion(const vector<int> &x)
	{
		v.push_back(x);
		numSoluciones++;
	}

/* OBSERVADORES */

	int estructuraSoluciones::getnumSoluciones()
	{
		return numSoluciones;
	}

	void estructuraSoluciones::mostrarSoluciones()
	{
		for(int j = 0; j < numSoluciones; j++)
		{
			cout<<"  Solucion "<<j+1<<" : "<<endl;

			for(unsigned int i = 1; i < v[j].size(); i++)
				cout<<"  x["<<i<<"] = "<<v[j][i]<<endl;

			cout<<endl;
		}

		return;
	}