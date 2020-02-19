//Alumno.h
//Definicion de la clase alumno.

#ifndef ALUMNO_H
#define ALUMNO_H

#include "Agenda.h"

class Alumno:public Persona {

private:
    int grupo_;
    bool esLider_;
    int cursoMasAlto_;

public:

	//CONSTRUCTOR
	//===========

	Alumno();
        
	/*
	Nombre: Alumno.
	Objetivo: Inicializar por defecto las variables de la clase Alumno.
	Descripción: la clase Alumno hereda de la clase Persona.
	Parametros de entrada:
		- Obligatorios: dni y email.
		- Opcionales: partes privadas de ambas clases anteriormente nombradas.
	Devuelve:
		- Nada.
	*/
	Alumno(string const &dni, string const &email, string &nombre, string &primerApellido, string &segundoApellido, string &fechaNacimiento, double telefono, string &direccion, string &codPostal, int grupo, bool esLider, int cursoMasAlto):
		Persona(dni, email, nombre, primerApellido, segundoApellido, telefono, direccion, codPostal, fechaNacimiento) {
		grupo_ = grupo;
		esLider_ = esLider;
		cursoMasAlto_ = cursoMasAlto;
	}

	// DESTRUCTOR
	//~Alumno();

	//OBSERVADORES
	//============

	/*
	Nombre: getGrupo.
	Objetivo: Saber el numero de grupo en el que está el alumno.
	Parametros de entrada:
		- Ninguno.
	Devuelve:
		- int: Entero cuyo valor equivale al grupo en el que está el alumno.
	*/
	int getGrupo_() const;

	/*
	Nombre: getEsLider.
	Objetivo: Saber si es lider de grupo.
	Parametros de entrada:
		- Ninguno.
	Devuelve:
		- bool: valor booleano, true si es lider o false en caso contrario.
	*/
	bool getEsLider_() const;

	/*
	Nombre: getCursoMasAlto.
	Objetivo: Observar el curso mas alto en el que se encuentra el alumno.
	Parametros de entrada:
		- Ninguno.
	Devuelve: int: entero que equivale al curso mas alto en el que se encuentra el alumno.
		- 
	*/
	int getCursoMasAlto_() const;

	//MODIFICADORES
	//=============

	/*
	Nombre: setGrupo.
	Objetivo: Modificar el grupo en el que se encuentra el alumno. 
	Parametros de entrada:
		-  int: Entero que equivale al numero de grupo en el que queremos meter al alumno.
	Devuelve:
		- Nada.
	*/
	void setGrupo_(int grupo_);

	/*
	Nombre: setEsLider.
	Objetivo: Modificar al alumno introduciendo si es lider o no. 
	Parametros de entrada:
		-  bool: true si queremos que el alumno sea lider o false, en caso contrario.
	Devuelve:
		- Nada.
	*/
	void setEsLider_(bool esLider_);

	/*
	Nombre: setCursoMasAlto.
	Objetivo: Modificar el curso mas alto en el que esta el alunno.
	Parametros de entrada:
		- int: Entero que vale al curso mas alto al que queremos que este el alumno. 
	Devuelve:
		- Nada.
	*/
	void setCursoMasAlto_(int cursoMasAlto_);
};

#endif