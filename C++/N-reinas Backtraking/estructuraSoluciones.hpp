#ifndef ESTRUCTURASOLUCION_HPP_
#define ESTRUCTURASOLUCION_HPP_

#include <iostream>
#include <vector>

using namespace std;

class estructuraSoluciones
{
	private:

		/* ATRIBUTOS */

		int numSoluciones;
		vector< vector<int> > v;

		/* FUNCIONES DE CLASE */
		

	public:

		/* CONSTRUCTORES  */

		estructuraSoluciones(); // Constructor por defecto

		/* DESTRUCTOR */

		~estructuraSoluciones();

		/* SOBRECARGA DE OPERADORES */

		/* MODIFICADORES */
		
		void meterSolucion(const vector<int> &x);

		/* OBSERVADORES */

		int getnumSoluciones();
		void mostrarSoluciones();

};

#endif