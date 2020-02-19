//Agenda.h
//Definicion de la clase Agenda.

#ifndef AGENDA_H
#define AGENDA_H

#include "Persona.h"
#include "Profesor.h"
#include "Alumno.h"

#include <list>
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <sstream>
#include <limits>
#include <cstdio>

using namespace std;

class Alumno;

class Agenda {

private:
	int maxAlumnos_;
	int numAlumnos_;
	Alumno ** lista_;
		
	// Funciones auxiliares
	
	/*
	 * 
	 */
	bool comprobarDni(const string &s) const;
	
	/*
	 * 
	 */
	bool comprobarEmail(const string &s) const;
	
	/*
	 * 
	 */
	void liberarMemoria();

public:

	//CONSTRUCTOR
	//===========

	/*
	Nombre: Agenda.
	Objetivo: Inicializar por defecto las variables de la clase Agenda.
	Parametros de entrada:
		- Ninguno.
	Devuelve:
		- Nada.
	*/
	Agenda()
	{
		maxAlumnos_ = 150;
		numAlumnos_ = 0;
		lista_ = new Alumno * [maxAlumnos_];
	}

	// DESTRUCTOR
		
	~Agenda()
	{
		for(int i = 0; i < numAlumnos_; i++)
			delete lista_[i];

		delete [] lista_;
	}

	// OBSERVADORES

	/*
	Nombre: getMaxAlumnos.
	Objetivo: Conocer el número máximo de alumnos que hay inscritos en la base de datos.
	Parametros de entrada:
		- Ninguno.
	Devuelve:
		- unsigned int: Número entero cuyo valor equivale al número máximo de alumnos inscritos en la base de datos.
	*/
	unsigned int getMaxAlumnos_() const;

	/*

	*/
	Alumno ** getLista_() const;

	/*

	*/
	int getNumAlumnos_() const;

	/*
	Nombre: listarAlumnos.
	Objetivo: El sistema quiere leer todos los alumnos inscritos en el sistema.
	Parametros de entrada:
		- bool: Se definirá ascendente para TRUE o desendente para FALSE.
	Devuelve:
		- Nada.
	*/
	void listarTodosLosAlumnos();

	/*
	Nombre: buscarAlumno.
	Objetivo: Buscar a un alumno en la base de datos.
	Parametros de entrada:
		- string: Cadena de caracteres introducida por teclado pasada por referencia.
		- int: Numero entero que define que criterio de búsqueda vamos a utilizar, es decir, queremos buscar por su DNI, apellido o equipo en el que está.
	Devuelve:
		- list: Devuelve una lista de alumnos cuyas características han coincidido con el criterio de búsqueda.
	*/
	Alumno * buscarAlumno(int &posicion);

	// MODIFICADORES

	/*
	Nombre: setMaxAlumnos.
	Objetivo: Modificar el número máximo de alumnos que hay inscritos en la base de datos.
	Parametros de entrada:
		- unsigned int: Número entero cuyo valor es el nuevo valor de _maxAlumnos. 
	Devuelve:
		- Nada.
	*/
	void setMaxAlumnos_(unsigned int maxAlumnos_);

	/*

	*/
	void setLista_(Alumno ** lista);
	
	/*

	*/
	void setNumAlumnos_(int numAlumnos);

	/*
	Nombre: insertarAlumno.
	Objetivo: Insertar un alumno en la base de datos.
	Parametros de entrada:
		- Alumno: Clase alumno recibida por referencia para inscribir a dicho alumno de la base de datos.
	Devuelve:
		- bool: True si el alumno ha sido insertado con éxito, o False en caso contrario.
	*/
	bool insertarAlumno();

	/*
	Nombre: borrarAlumno.
	Objetivo: Borrar a un alumno determinado en una base de datos.
	Parametros de entrada:
		- const Alumno: Clase Alumno recibida por referencia para borrar a dicho alumno de la base de datos.
	Devuelve:
		- bool: True si el alumno ha sido borrado con éxito, o False en caso contrario.
	*/
	bool borrarAlumno();

	/*
	Nombre: establecerLider.
	Objetivo: Establece un líder de grupo 
	Parametros de entrada:
		- Alumno: Clase Alumno recibida por referencia para borrar a dicho alumno de la base de datos.
	Devuelve:
		- bool: True si el alumno ha sido borrado con éxito, o False en caso contrario.
	*/
	bool establecerLider();

	/*
	Nombre: modificarAlumno.
	Objetivo: Modificar los datos de un alumno. 
	Parametros de entrada:
		- Alumno: Clase Alumno recibida por referencia para modificar algun campo de dicho alumno de la base de datos.
	Devuelve:
		- bool: True si el alumno ha sido modificado con éxito, o False en caso contrario.
	*/
	bool modificarAlumno();
		
	/*
	 * 
	 */
	void mostrarAlumno() ;
	
	/*
	* Inicializa la agenda con la información almacenada en el fichero determinado por Conf
	*/
	bool cargarDatos(const string &s); // Lo realiza el sistema
	
	/*
	* Borra todo y lo guarda como si fuera nuevo
	*/
	bool guardarCambios(const string &s); // Cualquier profesor
	
	/*
	* Guarda la información pero en un archivo externo
	*/
	bool guardarCopiaSeguridad(Profesor * p); // Solo si es coordinador
	
	/*
	* Carga la información, pero de un archivo externo
	*/
	bool cargarCopiaSeguridad(Profesor * p); // Solo si es coordinador
};

#endif