//Persona.h
//Definicion de la clase Persona.

#ifndef PERSONA_H
#define PERSONA_H

#include "Agenda.h"
#include <string>
using namespace std;

class Persona {

private:
	string dni_;
	string nombre_;
	string primerApellido_;
	string segundoApellido_;
	string fechaNacimiento_;
	int telefono_;
	string email_;
	string direccion_;

public:

    // CONSTRUCTOR

    Persona();
    
	/*
	Nombre: Persona.
	Objetivo: Inicializar por defecto las variables de la clase Persona.
	Parametros de entrada:
		- Ninguno.
	Devuelve:
		- Nada.
	*/
	Persona(string const &dni, string const &email, string &nombre, string &primerApellido, string &segundoApellido, double telefono, string &direccion, string &codPostal, string &fechaNacimiento) {
		dni_ = dni;
		email_ = email;
		nombre_ = nombre;
		primerApellido_ = primerApellido;
		segundoApellido_ = segundoApellido;
		telefono_ = telefono;
		direccion_ = direccion;
		fechaNacimiento_ = fechaNacimiento;
	}

	// DESTRUCTOR
	//virtual ~Persona();
        
	//OBSERVADORES

	string getDireccion_() const;

	string getEmail_() const;

	double getTelefono_() const;

	string getFechaNacimiento_() const;

	string getSegundoApellido_() const;

	string getPrimerApellido_() const;

	string getNombre_() const;

	string getDni_() const;


	//MODIFICADORES

	void setDireccion_(string direccion_);

	void setEmail_(string email_);

	void setTelefono_(double telefono_);
	
	void setFechaNacimiento_(string fechaNacimiento_);

	void setSegundoApellido_(string segundoApellido_);

	void setPrimerApellido_(string primerApellido_);

	void setNombre_(string nombre_);

	void setDni_(string dni_);

};

#endif
