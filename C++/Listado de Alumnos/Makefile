# Makefile Listado Alumnos

all: listado

listado: main.o Agenda.o Persona.o Alumno.o Profesor.o
	g++ -Wall -o listado main.o Agenda.o Persona.o Alumno.o Profesor.o

main.o: main.cpp Agenda.h Persona.h Alumno.h Profesor.h main.h
	g++ -Wall -c main.cpp

Agenda.o: Agenda.cpp Agenda.h Persona.h Alumno.h Profesor.h
	g++ -Wall -c Agenda.cpp

Persona.o: Persona.cpp Agenda.h Persona.h Alumno.h Profesor.h
	g++ -Wall -c Persona.cpp

Alumno.o: Alumno.cpp Agenda.h Persona.h Alumno.h Profesor.h
	g++ -Wall -c Alumno.cpp

Profesor.o: Profesor.cpp Agenda.h Persona.h Alumno.h Profesor.h
	g++ -Wall -c Profesor.cpp

clean:
	rm -f listado *.o