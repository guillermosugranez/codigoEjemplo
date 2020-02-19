//Alumno.cpp
//Funciones de la clase Alumno.

#include "Agenda.h"

// CONSTRUCTOR

Alumno::Alumno()
{
	
}

// OBSERVADORES

int Alumno::getCursoMasAlto_() const {
	return cursoMasAlto_;
}

bool Alumno::getEsLider_() const {
	return esLider_;
}

int Alumno::getGrupo_() const {
	return grupo_;
}

// MODIFICADORES

void Alumno::setCursoMasAlto_(int cursoMasAlto_) {
	this->cursoMasAlto_ = cursoMasAlto_;
}

void Alumno::setEsLider_(bool esLider_) {
	this->esLider_ = esLider_;
}

void Alumno::setGrupo_(int grupo_) {
	this->grupo_ = grupo_;
}
