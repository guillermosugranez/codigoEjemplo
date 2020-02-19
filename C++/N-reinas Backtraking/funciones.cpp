#include "funciones.hpp"
#include "estructuraSoluciones.hpp"

#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

void repetir(bool &prueba)
{
	cout<<" - Introduzca un 1 si desea realizar otra prueba. Si desea salir pulse 0. ";
	cin>>prueba;

	return;
}

bool Lugar(int k, const vector<int> &x)
{
	for(int i = 1; i <= (k-1); i++)
	{
		if(x[i] == x[k] || abs(x[i]-x[k]) == abs(i-k))
			return false;
	}

	return true;
}

void nReinas(int n, estructuraSoluciones &soluciones)
{
	int k = 1;
	vector<int> x(n+1, 0);

	while(k > 0) // mientras no se tengan todas las soluciones
	{
		x[k] = x[k]+1; // Desplazar reina a la siguiente columna

		while(x[k] <= n && Lugar(k,x) == false) // minetras no salga del tablero y sea amenazada por una anterior
		{
			x[k] = x[k] + 1; // desplazar reina a la siguiente columna
		}

		if(x[k] <= n) // si una posicion correcta ha sido encontrada
		{
			if(k == n) // si es la ultima reina se tiene la solucion
			{
				// mostrarSolucion(x); // escribir la solucion
				soluciones.meterSolucion(x);
			}

			else // si no es la ultima reina
			{
				k = k+1; // probar la siguiente reina
				x[k] = 0; // ubicandandola en la columna 0
			}
		}
		else // la reina no se puede ubicar
		{
			k = k-1; // volvemos a la reina anterior
		}
	}

	return;
}

void mostrarSolucion(const vector<int> &x)
{
	cout<<"La solucion es: \n"<<endl;

	for(unsigned int i = 1; i <= x.size(); i++)
		cout<<"x["<<i<<"] = "<<x[i]<<endl;

	return;
}



