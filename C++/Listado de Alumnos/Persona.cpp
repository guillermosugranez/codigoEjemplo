//Persona.cpp
//Funciones de la clase Persona.

#include "Agenda.h"

	// CONSTRUCTOR
	
	Persona::Persona()
	{
		
	}

	// OBSERVADORES

	string Persona::getDireccion_() const {
		return direccion_;
	}

	string Persona::getEmail_() const {
		return email_;
	}

	double Persona::getTelefono_() const {
		return telefono_;
	}

	string Persona::getFechaNacimiento_() const {
		return fechaNacimiento_;
	}

	string Persona::getSegundoApellido_() const {
		return segundoApellido_;
	}

	string Persona::getPrimerApellido_() const {
		return primerApellido_;
	}

	string Persona::getNombre_() const {
		return nombre_;
	}

	string Persona::getDni_() const {
		return dni_;
	}

	// MODIFICADORES

	void Persona::setDireccion_(string direccion_) {
		this->direccion_ = direccion_;
	}

	void Persona::setEmail_(string email_) {
		this->email_ = email_;
	}

	void Persona::setTelefono_(double telefono_) {
		this->telefono_ = telefono_;
	}

	void Persona::setFechaNacimiento_(string fechaNacimiento_) {
		this->fechaNacimiento_ = fechaNacimiento_;
	}

	void Persona::setSegundoApellido_(string segundoApellido_) {
		this->segundoApellido_ = segundoApellido_;
	}

	void Persona::setPrimerApellido_(string primerApellido_) {
		this->primerApellido_ = primerApellido_;
	}

	void Persona::setNombre_(string nombre_) {
		this->nombre_ = nombre_;
	}

	void Persona::setDni_(string dni_) {
		this->dni_ = dni_;
	}
		