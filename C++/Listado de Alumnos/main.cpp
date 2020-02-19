//============================================================================
// Name        : Listado.cpp
// Author      : Guillermo Sugráñez Pérez
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include "main.h"

using namespace std;

int main()
{
	Profesor * p = 0;
	char opcion = 0;
	bool login = false;
	
	// Lo primero es loguearse o registrarse
	do
	{
		cout<<"\n - Seleccione la operación que desea realizar: "<<endl;
		cout<<"\n\t1) Iniciar Sesión";
		cout<<"\n\t2) Registrarse";

		cout<<"\n\n\t0) Salir";
		cout<<"\n\n\tOpción: ";
		cin>>opcion;
		
		cout<<endl;
		switch(opcion)
		{
			case '1':
				login = iniciarSesion(p);
				break;
				
			case '2':
				registrar();
				break;
				
			default:
				if(opcion != '0')
					cout<<"Opción no válida. Pruebe de nuevo";
				break;
		}
	}while(opcion != '0' && login == false);
	
	if(opcion == '0')
		return 0;
	
	// Una vez logueado hay que cargar la información del archivo predeterminado
	
	Agenda agenda;
	agenda.cargarDatos("./Ficheros/Alumnos"); // Hubicación por defecto

	do
	{
		cout<<"\n\tSeleccione la operación que desea realizar: "<<endl;
		cout<<"\n\t1) Introducir un nuevo alumno";
		cout<<"\n\t2) Borrar un alumno";
		cout<<"\n\t3) Mostrar la información de un alumno";
		cout<<"\n\t4) Modificar la información de un alumno";
		cout<<"\n\t5) Establecer lider de grupo";
		cout<<"\n\t6) Listar todos los alumnos";
		cout<<"\n\t7) Guardar cambios";
		cout<<"\n\t8) Guardar copia de seguridad externa";
		cout<<"\n\t9) Cargar copia de seguridad externa";
		
		cout<<"\n\n\t0) Salir";
		cout<<"\n\n\tOpción: ";
		cin>>opcion;
		
		switch(opcion)
		{
			case '1':
				agenda.insertarAlumno();
				break;
				
			case '2':
				agenda.borrarAlumno();
				break;
				
			case '3':
				agenda.mostrarAlumno();
				break;
				
			case '4':
				agenda.modificarAlumno();
				break;
				
			case '5':
				agenda.establecerLider();
				break;
				
			case '6':
				agenda.listarTodosLosAlumnos(); // Hubicación por defecto
				break;
				
			case '7':
				agenda.guardarCambios("./Ficheros/Alumnos"); // Hubicación por defecto
				break;
				
			case '8':
				agenda.guardarCopiaSeguridad(p); // Se pasa el profesor
				break;
				
			case '9':
				agenda.cargarCopiaSeguridad(p);
				break;
				
			default:
				if(opcion != '0')
					cout<<"\n\t - Opción no válida. Pruebe de nuevo";
				break;
		}
		
		// Posible nueva operación
		if(opcion != '0')
		{
			cout<<"\n\t- Para hacer otra operación pulse cualquier tecla distinta de 0 seguido de enter.\n\tPara salir pulse 0 seguido de enter ";
			cout<<"\n\t- ¿Desea realizar otra operación? : ";
			cin>>opcion;
		}
		

	}while(opcion != '0');

	if(p)
		delete p;

	return 0;
}

// Al hacer el formulario rellenar si eres coordinador o no
// Sobreescribir la informacion y no añadir