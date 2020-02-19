#ifndef PROFESOR_H
#define PROFESOR_H

#include "Agenda.h"

class Profesor : public Persona {

private:
	bool coordinador_;

public:
	
    Profesor();
    
	// CONSTRUCTOR
	
	Profesor(const string& dni, const string& email, string nombre, string primerApellido, string segundoApellido, double telefono, string direccion, string codPostal, string fechaNacimiento, bool Coordinador) :
		Persona(dni, email, nombre, primerApellido, segundoApellido, telefono, direccion, codPostal, fechaNacimiento) {
		
		coordinador_ = Coordinador;
	}

	// DESTRUCTOR

	// ~Profesor();

	// OBSERVADORES

	bool getCoordinador_() const;

	// MODIFICADORES

	void setCoordinador_(bool Coordinador);
};

#endif
