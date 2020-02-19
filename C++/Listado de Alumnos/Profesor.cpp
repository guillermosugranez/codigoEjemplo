#include "Agenda.h"

// CONSTRUCTOR

Profesor::Profesor()
{
	
}

// OBSERVADORES

bool Profesor::getCoordinador_() const {
    return coordinador_;
}

void Profesor::setCoordinador_(bool Coordinador) {
    coordinador_ = Coordinador;
}