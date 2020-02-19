//agenda->cpp
//Funciones de la clase agenda->

#include "Agenda.h"

using namespace std;

// FUNCIONES PRIVADAS

bool Agenda::comprobarDni(const string &s) const
{
	bool respuesta = false; // Positiva si lo encuentra
	
	for(int i = 0; i < numAlumnos_; i++)
	{
		if(lista_[i]->getDni_() == s)
			respuesta = true;
	}
	
	return respuesta;
}

bool Agenda::comprobarEmail(const string &s) const
{
	bool respuesta = false;
	
	for(int i = 0; i < numAlumnos_; i++)
	{
		if(lista_[i]->getEmail_() == s)
			respuesta = true;
	}
	
	return respuesta;
}

void Agenda::liberarMemoria()
{
	for(int i = 0; i < numAlumnos_; i++)
	{
		delete lista_[i];
		lista_[i] = 0;
	}
	
	numAlumnos_ = 0;
	
	return;
}

// OBSERVADORES

Alumno ** Agenda::getLista_() const {
	return lista_;
}
int Agenda::getNumAlumnos_() const {
	return numAlumnos_;
}
unsigned int Agenda::getMaxAlumnos_() const {
	return maxAlumnos_;
}

void Agenda::listarTodosLosAlumnos() 
{
	Alumno * temp = 0;

	// Salgo si no hay alumnos que mostrar
	if(numAlumnos_ <= 0)
	{
		cout<<"\n\tNo hay alumnos en la lista.";
		return;
	}
	
	// Hay que determinar el criterio de búsqueda primero
	
	int criterioBusqueda = 2;
	int orden = 1; // 0 Ascendente, 1 Descendente (Por defecto Descendente)
	string palabra = "";
	// Se puede buscar por Apellidos o por DNI, por tanto, primero habría que especificarlo
	
	cout<<"\n\tIndica el criterio de busqueda: ";
	cout<<"\n\t1) Ordenar por Primer Apellido: ";
	cout<<"\n\t2) Ordenar por DNI: ";
	cout<<"\n\t3) Ordenar por Nombre: ";
	cout<<"\n\t4) Ordenar por Curso más alto: ";
	cout<<"\n\tPulse 0 si desea salir";

	cout<<"\n\n\tCriterio: ";
	scanf ("%d",&criterioBusqueda);
	
	if(criterioBusqueda == 0) // Salir
		return;
	else if(criterioBusqueda < 0 || criterioBusqueda > 4)
	{
		criterioBusqueda = 2;
		cout<<"\n\tCriterio desconocido. Por defecto ordenar por DNI";
	}
	
	cout<<"\n\t¿Orden Ascendente (0) o Descendente (1)?: ";
	scanf ("%d",&orden);
	getchar();

	if(criterioBusqueda == 1)
		for(int i=0; i<numAlumnos_-1; i++)
			for(int j=i+1; j<numAlumnos_; j++)
				if(lista_[i]->getPrimerApellido_() > lista_[j]->getPrimerApellido_())
				{
					temp = lista_[i];
					lista_[i] = lista_[j];
					lista_[j] = temp;
				}

	if(criterioBusqueda == 2)
		for(int i=0; i<numAlumnos_-1; i++)
			for(int j=i+1; j<numAlumnos_; j++)
				if(lista_[i]->getDni_() > lista_[j]->getDni_())
				{
					temp = lista_[i];
					lista_[i] = lista_[j];
					lista_[j] = temp;
				}

	if(criterioBusqueda == 3)
		for(int i=0; i<numAlumnos_-1; i++)
			for(int j=i+1; j<numAlumnos_; j++)
				if(lista_[i]->getNombre_() > lista_[j]->getNombre_())
				{
					temp = lista_[i];
					lista_[i] = lista_[j];
					lista_[j] = temp;
				}

	if(criterioBusqueda == 4)
		for(int i=0; i<numAlumnos_-1; i++)
			for(int j=i+1; j<numAlumnos_; j++)
				if(lista_[i]->getCursoMasAlto_() > lista_[j]->getCursoMasAlto_())
				{
					temp = lista_[i];
					lista_[i] = lista_[j];
					lista_[j] = temp;
				}
	
	// Mostramos la lista con los campos que se han tenido en cuenta
	cout<<"# Lista de Alumnos"<<endl;;
	if(orden) // Descendente
	{
		for(int i = 0; i < numAlumnos_ ; i++)
		{
			cout <<"\n"<<i + 1<< ". ";

			cout << lista_[i]->getDni_() << " - ";
			cout << lista_[i]->getNombre_() << " ";
			cout << lista_[i]->getPrimerApellido_() << ". Curso más alto: ";
			cout << lista_[i]->getCursoMasAlto_();
		}
	}
	else
	{
		for(int i = numAlumnos_-1; i >= 0 ; i--)
		{
			cout <<"\n "<<(numAlumnos_ - i)<<". ";

			cout << lista_[i]->getDni_() << " - ";
			cout << lista_[i]->getNombre_() << " ";
			cout << lista_[i]->getPrimerApellido_() << ". Curso más alto: ";
			cout << lista_[i]->getCursoMasAlto_();
		}
	}

	// Abrimos el fichero
	ofstream salida("./Ficheros/Lista.md"); // Borra la que hubiera antes
	if(!salida)
	{
		cout << "ERROR de apertura";
		return;
	}
	
	// Mostramos la lista con los campos que se han tenido en cuenta
	salida<<"# Lista de Usuarios"<<endl;;
	if(orden) // Descendente
	{
		for(int i = 0; i < numAlumnos_ ; i++)
		{
			salida <<"\n"<<i<< ". ";

			salida << lista_[i]->getDni_() << " - ";
			salida << lista_[i]->getNombre_() << " ";
			salida << lista_[i]->getPrimerApellido_() << ". Curso más alto: ";
			salida << lista_[i]->getCursoMasAlto_();
		}
	}
	else
	{
		for(int i = numAlumnos_-1; i >= 0 ; i--)
		{
			salida <<"\n\t "<<numAlumnos_ - i<<". ";

			salida << lista_[i]->getDni_() << " - ";
			salida << lista_[i]->getNombre_() << " ";
			salida << lista_[i]->getPrimerApellido_() << ". Curso más alto: ";
			salida << lista_[i]->getCursoMasAlto_();
		}
	}

    cout<<endl;
	
	return;
}

Alumno * Agenda::buscarAlumno(int &posicion)
{
	Alumno * a;
	int numCoincidencias = 0;
	int opcion = 0; // Permite elegir si hay mas de una coincidencias
	
	char criterioBusqueda = '0';
	string palabra = "";
	// Se puede buscar por Apellidos o por DNI, por tanto, primero habría que especificarlo
	
	cout<<"\n\tIndica el criterio de busqueda: ";
	cout<<"\n\t1) Busqueda por Apellidos: ";
	cout<<"\n\t2) Busqueda por DNI: ";
	cout<<"\n\t3) Busqueda por Grupo: ";
	cout<<"\n\tPulse 0 si desea salir";

	cout<<"\n\n\tCriterio: ";
	cin>>criterioBusqueda;
	
	if(criterioBusqueda == '0') // Salir
		return 0;
	else if(criterioBusqueda != '1' && criterioBusqueda != '2' && criterioBusqueda != '3')
	{
		cout<<"\n\tCriterio desconocido. Por defecto busqueda por DNI";
	}
	
	cout<<"\n\tIntroduce la palabra clave: ";
	cin>>palabra;
	
	Alumno * coincidencias[numAlumnos_]; // Aqui guardo temporalmente las coincidencias
	
	for(int i = 0; i < numAlumnos_ ; i++)
	{
		if(criterioBusqueda == '1') // Por apellidos
		{
			if(lista_[i]->getPrimerApellido_() == palabra || lista_[i]->getSegundoApellido_() == palabra)
			{
				coincidencias[numCoincidencias] = lista_[i];
				numCoincidencias++;
			}	
		}
		else if(criterioBusqueda == '2') // Por DNI
		{
			if(lista_[i]->getDni_() == palabra)
			{
				coincidencias[numCoincidencias] = lista_[i];
				numCoincidencias++;
			}	
		}
		else if(criterioBusqueda == '3') // Por número de grupo
		{
			if(lista_[i]->getGrupo_() == stoi(palabra))
			{
				coincidencias[numCoincidencias] = lista_[i];
				numCoincidencias++;
			}	
		}
	}
	
	if(numCoincidencias == 1)
	{
		a = coincidencias[0]; // Apunto la direccion del alumno dentro de la lista
		posicion = 0;
	}
	else if(numCoincidencias > 1)
	{
		// Si hay más de una coincidencia tengo que elegir
		cout<<"\n\tHa habido más de una coincidencia. Especifica el Alumno manualmente:\n";

		for(int i = 0; i < numAlumnos_; i++)
			cout<<"\n\t"<<i<<") "<<coincidencias[i]->getDni_() <<" ; "<< coincidencias[i]->getPrimerApellido_()<<" ; "<<coincidencias[i]->getSegundoApellido_();
		
		cout<<"\n\n\t-> ";
		cin>>opcion;
		a = coincidencias[opcion];
	}
	else
	{
		cout<<"\n\tNo hubo coincidencias"<<endl;
		return 0;
	}
	
	// Encuentra la posicion primero
	for(int i = 0; i < numAlumnos_; i++)
	{
		if(lista_[i]->getDni_() == a->getDni_())
		{
			posicion = i;
			break;
		}
	}

	// cout<<"La posicion es: "<<posicion<<endl;

	return a;
}

// MODIFICADORES

void Agenda::setLista_(Alumno ** lista){
	this->lista_ = lista;
}

void Agenda::setNumAlumnos_(int numAlumnos_) {
	this->numAlumnos_ = numAlumnos_;
}

void Agenda::setMaxAlumnos_(unsigned int maxAlumnos_) {
	this->maxAlumnos_ = maxAlumnos_;
}

bool Agenda::insertarAlumno()
{
	// Comprobar que existe espacio suficiente
	if(numAlumnos_ >= maxAlumnos_)
		return false;
	
	// Campos obligatorios
	
	bool flag = false;
	char strAux[100];
	int intAux = 0;
	
	Alumno * a = new Alumno;

	cin.clear(); // unset failbit
	cin.ignore(numeric_limits<streamsize>::max(),'\n'); // skip bad input
	
	// Primero comprobar los campos que no deben repetirse (dni y correo)
	do
	{
		cout<<"\n\tIntroduce el DNI del nuevo alumno: ";
		cin.getline(strAux,100);
		
		flag = comprobarDni(strAux);
		
		if(!flag)
			a->setDni_(strAux);
		else
			cout<<"\n\tEl DNI introducido ya existe o no es válido. Pruebe de nuevo."<<endl;
		
	}while(flag);

	do
	{
		cout<<"\n\tIntroduce el Correo Electronico del nuevo alumno: ";
		cin.getline(strAux,100);
		
		flag = comprobarEmail(strAux);
		
		if(!flag)
			a->setEmail_(strAux);
		else
			cout<<"\n\tEl eMail introducido ya existe o no es válido. Pruebe de nuevo."<<endl;
		
	}while(flag);
	
	// Después, completar los campos obligatorios
	
	cout<<"\n\tIntroduce el Nombre del nuevo alumno: ";
	cin.getline(strAux,100);
	a->setNombre_(strAux);
	
	cout<<"\n\tIntroduce el Primer Apellido del nuevo alumno: ";
	cin.getline(strAux,100);
	a->setPrimerApellido_(strAux);
	
	cout<<"\n\tIntroduce el Segundo Apellido del nuevo alumno: ";
	cin.getline(strAux,100);
	a->setSegundoApellido_(strAux);
	
	cout<<"\n\tIntroduce la Dirección Postal del nuevo alumno: ";
	cin.getline(strAux,100);
	a->setDireccion_(strAux);

	cout<<"\n\tIntroduce la Fecha de Nacimiento del nuevo alumno: ";
	cin.getline(strAux,100);
	a->setFechaNacimiento_(strAux);

	//==================================================================

	cout<<"\n\tIntroduce el Telefono del nuevo alumno: ";
	cin>>strAux;
	if(intAux >= 600000000 && intAux <= 699999999)
		a->setTelefono_(intAux);	
	else
		a->setTelefono_(0);

	cin.clear(); // unset failbit
	cin.ignore(numeric_limits<streamsize>::max(),'\n'); // skip bad input
	
	cout<<"\n\tIntroduce el Grupo del nuevo alumno: ";
	cin>>intAux;
	if(intAux >= 0 && intAux <= 20)
		a->setGrupo_(intAux);	
	else
		a->setGrupo_(0);

	cin.clear(); // unset failbit
	cin.ignore(numeric_limits<streamsize>::max(),'\n'); // skip bad input

	cout<<"\n\tIntroduce el Curso Más Alto del nuevo alumno: ";
	cin>>intAux;
	if(intAux > 0 && intAux <= 4)
		a->setCursoMasAlto_(intAux);	
	else
		a->setCursoMasAlto_(0);
	
	lista_[numAlumnos_] = a; // Metemos el alumno en la lista
	numAlumnos_++; // Incrementamos el número de alumnos

	cin.clear(); // unset failbit
	cin.ignore(numeric_limits<streamsize>::max(),'\n'); // skip bad input

	return true;
}


bool Agenda::borrarAlumno()
{
	int posicion = -1; // Posición por defecto (0 puede representar al primer elemento)
	
	Alumno * a = buscarAlumno(posicion);
	
	if(a == 0)
	{
		cout<<"\n\tNo se pudo realizar la operacion Borrar Alumno";
		return false;
	}
	else
	{
		// Hay que eliminarlo de la lista y reorganizar si es preciso
		
		// Comprueba si es el último elemento
		if(posicion == numAlumnos_-1) // -1 Por corregir que el indice empiece en 0
		{
			cout<<"\nÚltimo elemento";
			delete lista_[numAlumnos_];
			lista_[numAlumnos_] = 0;
			numAlumnos_--;
		}
		else // Toca reorganizar la lista
		{
			cout<<"\nReorganizar lista";
			delete lista_[posicion];
			for(int i = posicion; i < numAlumnos_; i++)
				lista_[i] = lista_[i+1];
			
			numAlumnos_--;
		}
	}
	
	return true;
}

bool Agenda::establecerLider()
{
	int antiguoLider = -1;
	int nuvoLider = -1;
	int grupo = -1;
	int numAlumnosEnGrupo = 0;
	Alumno * coincidencias[numAlumnos_]; // Aqui guardo temporalmente las coincidencias
	
	// Prguntar por el alumno
	
	int posicion = -1; // Posición por defecto (0 puede representar al primer elemento)
	
	Alumno * a = buscarAlumno(posicion);
	
	// Comprobar si existe el alumno
	if(a == 0)
	{
		cout<<"\n\tNo se pudo realizar la operacion Establecer Lider";
		return false;
	}
	else
	{
		// Listar el grupo
		grupo = a->getGrupo_();
		cout<<"\n\tLos alumnos del grupo "<<grupo<<" son:\n";
		
		for(int i = 0; i < numAlumnos_; i++)
		{
			if(lista_[i]->getGrupo_() == grupo) // Si el alumno actual está en el mismo grupo...
			{
				// Lo meto en la lista de coincidencias
				coincidencias[numAlumnosEnGrupo] = lista_[i];
				
				// Muestra la información básica del alumno
				cout<<"\t"<<numAlumnosEnGrupo<<") "<<lista_[i]->getDni_()<<" - \t";
				cout<<lista_[i]->getNombre_()<<" ";
				cout<<lista_[i]->getPrimerApellido_()<<" ";
				cout<<lista_[i]->getSegundoApellido_()<<" ";
				
				// Si es el lider lo muestro y apunto su dirección
				if(lista_[i]->getEsLider_())
				{
					cout<<"\t LIDER";
					antiguoLider = numAlumnosEnGrupo;
				}
				
				cout<<endl;
				
				numAlumnosEnGrupo++;
			}
		}
		
		// Proponer a uno de los alumnos como jefe de grupo
		cout<<"\n\t¿Qué alumno desea proponer como nuevo lider del grupo "<<grupo<<"?: ";
		cin>>nuvoLider;
		
		// Comprobar que no hubiera lider antes
		if(antiguoLider != -1)
		{
			cout<<"\n\tCambio de lider";
			coincidencias[nuvoLider]->setEsLider_(true);
			coincidencias[antiguoLider]->setEsLider_(false);
		}
		else
		{
			coincidencias[nuvoLider]->setEsLider_(true);
			return true;
		}
	}
	
	return false;
}


bool Agenda::modificarAlumno()
{
	char campo = -1;
	string strAux = "";
	int intAux = -1;
	bool flag = false;
	
	// Primero determinar el alumno que se desea modificar
	int posicion = -1;
	
	// Primero hay que buscar al alumno que queremos mostrar
	Alumno * a = buscarAlumno(posicion);
	
	if(a == 0) // Si no encuentra sale
	{
		cout<<"\n\tNo se pudo realizar la operacion Modificar Alumno";
		return false;
	}
	else
	{
		do
		{
			// Una vez determinado el alumno, hay que determinar qué campo se desea modificar
			cout<<"\n\tIndica el campo que desea modificar: ";
			cout<<"\n\t1) Modificar DNI: ";
			cout<<"\n\t2) Modificar Nombre: ";
			cout<<"\n\t3) Modificar Primer Apellido: ";
			cout<<"\n\t4) Modificar Segundo Apellido: ";
			cout<<"\n\t5) Modificar Teléfono: ";
			cout<<"\n\t6) Modificar Dirección Postal: ";
			cout<<"\n\t7) Modificar Fecha de Nacimiento: ";
			cout<<"\n\t8) Modificar Grupo: ";
			cout<<"\n\t9) Modificar Curso más Alto: ";
			cout<<"\n\ta) Modificar Email: ";
			
			cout<<"\n\tPulse 0 si desea salir";
			
			cout<<"\n\n\tCampo: ";
			cin>>campo;
			
			cout<<endl;
			
			switch(campo)
			{
				case '1':
					do
					{
						cout<<"\tIntroduce el DNI del nuevo alumno: ";
						cin>>strAux;

						flag = comprobarDni(strAux);

						if(!flag)
							a->setDni_(strAux);
						else
							cout<<"\n\tEl DNI introducido ya existe o no es válido. Pruebe de nuevo."<<endl;

					}while(flag);
					break;
					
				case '2':
					cout<<"\n\tIntroduce el Nombre del alumno: ";
					cin>>strAux;
					a->setNombre_(strAux);
					break;
					
				case '3':
					cout<<"\n\tIntroduce el Primer Apellido del nuevo alumno: ";
					cin>>strAux;
					a->setPrimerApellido_(strAux);
					break;
					
				case '4':
					cout<<"\n\tIntroduce el Segundo Apellido del nuevo alumno: ";
					cin>>strAux;
					a->setSegundoApellido_(strAux);
					break;
					
				case '5':
					cout<<"\n\tIntroduce el Telefono del nuevo alumno: ";
					cin>>intAux;
					a->setTelefono_(intAux);
					break;
					
				case '6':
					cout<<"\n\tIntroduce la Dirección Postal del nuevo alumno: ";
					cin>>strAux;
					a->setDireccion_(strAux);
					break;
					
				case '7':
					cout<<"\n\tIntroduce la Fecha de Nacimiento del nuevo alumno: ";
					cin>>strAux;
					a->setFechaNacimiento_(strAux);
					break;
					
				case '8':
					cout<<"\n\tIntroduce el Grupo del nuevo alumno: ";
					cin>>intAux;
					a->setGrupo_(intAux);
					break;
					
				case '9':
					cout<<"\n\tIntroduce el Curso Más Alto del nuevo alumno: ";
					cin>>intAux;
					a->setCursoMasAlto_(intAux);
					break;
					
				case 'a':
					do
					{
						cout<<"\n\tIntroduce el Correo Electronico del nuevo alumno: ";
						cin>>strAux;

						flag = comprobarEmail(strAux);

						if(!flag)
							a->setEmail_(strAux);
						else
							cout<<"\n\tEl eMail introducido ya existe o no es válido. Pruebe de nuevo."<<endl;

					}while(flag);
					break;
					
				default:
					if(campo != '0')
						cout<<"\n\tOpción no válida. Pruebe de nuevo";
					break;
			}
		}while(campo != '0');
	}
	
	return true;	
}

void Agenda::mostrarAlumno()
{
	int posicion = -1;
	
	// Primero hay que buscar al alumno que queremos mostrar
	Alumno * a = buscarAlumno(posicion);
	
	if(a == 0) // Si no encuentra sale
	{
		cout<<"\n\tNo se pudo realizar la operacion Mostrar Alumno";
		return;
	}
	else
	{
		cout<<"\n\t====================================================\n";

		cout<<"\n\t - DNI del alumno: "<<a->getDni_();
		cout<<"\n\t - Email del alumno: "<<a->getEmail_();
		cout<<"\n\t - Nombre del alumno: "<<a->getNombre_();
		cout<<"\n\t - Primer Apellido del alumno: "<<a->getPrimerApellido_();
		cout<<"\n\t - Segundo Apellido del alumno: "<<a->getSegundoApellido_();
		cout<<"\n\t - Fecha de Nacimiento del alumno: "<<a->getFechaNacimiento_();
		cout<<"\n\t - Direccion Postal: "<<a->getDireccion_();

		cout<<"\n\t - Teléfono del alumno: "<<a->getTelefono_();
		cout<<"\n\t - Grupo del alumno: "<<a->getGrupo_();
		
		if(a->getEsLider_())
			cout<<"\n\t - ¿Lider de grupo?: Si";
		else
			cout<<"\n\t - ¿Lider de grupo?: No";
		
		cout<<"\n\t - Curso más alto del alumno: "<<a->getCursoMasAlto_();

		cout<<"\n\n\t====================================================\n";
	}
}

bool Agenda::cargarDatos(const string &s)
{
	// Primero borrar posibles datos anteriores
	if(numAlumnos_ > 0)
		liberarMemoria();
	
	Alumno * a;

	// Abrir el archivo para escribir la información
	ifstream entrada(s);

	if(!entrada)
	{
		cout << "\nERROR de apertura\n";
		return false;
	}

	string linea;
	int intAux = 0;
	string strAux = "";
	char charAux = ' ';

	// Mientras se pueda leer una linea del archivo ...
	while (getline(entrada, linea))
	{
		lista_[numAlumnos_] = new Alumno;
		a = lista_[numAlumnos_];
		stringstream ss(linea);

		//=============================================================

		// DNI
		getline(ss, strAux, ';');
		a->setDni_(strAux);

		// Correo
		getline(ss, strAux, ';');
		a->setEmail_(strAux);

		// Nombre
		getline(ss, strAux, ';');
		a->setNombre_(strAux);

		// Primer Apellido
		getline(ss, strAux, ';');
		a->setPrimerApellido_(strAux);

		// Segund Apellido
		getline(ss, strAux, ';');
		a->setSegundoApellido_(strAux);

		// Dirección
		getline(ss, strAux, ';');
		a->setDireccion_(strAux);

		// Fecha de Nacimiento
		getline(ss, strAux, ';');
		a->setFechaNacimiento_(strAux);

		//=============================================================

		// Curso más alto
		ss >> intAux;
		a->setCursoMasAlto_(intAux);

		// Descartamos el caracter ';' a continuacion del numero
		ss >> charAux;

		// Lider
		ss >> intAux;
		a->setEsLider_(intAux);

		ss >> charAux;

		// Grupo
		ss >> intAux;
		a->setGrupo_(intAux);

		// Descartamos el caracter ';' a continuacion del numero
		ss >> charAux;

		// Telefono
		ss >> intAux;
		a->setTelefono_(intAux);

		//=============================================================

		numAlumnos_++;
	}
	
	cout<<"\n El numero de alumnos cargados es: "<<numAlumnos_<<endl;
	
	entrada.close();
	
	return true;
}

bool Agenda::guardarCambios(const string &s)
{
	string strAux = "";
	
	// Abrir el archivo para escribir la información
	ofstream salida(s);
	if(!salida)
	{
		cout << "\nERROR de apertura\n";
		return false;
	}
	
	// Las sucesivas lineas son los sucesivos alumnos
	for(int i = 0; i < numAlumnos_; i++)
	{
		salida << lista_[i]->getDni_() << ";";
		salida << lista_[i]->getEmail_() << ";";
		salida << lista_[i]->getNombre_() << ";";
		salida << lista_[i]->getPrimerApellido_() << ";";
		salida << lista_[i]->getSegundoApellido_() << ";";
		salida << lista_[i]->getDireccion_() << ";";
		salida << lista_[i]->getFechaNacimiento_() << ";";

		salida << lista_[i]->getCursoMasAlto_() << ";"; // int
		salida << lista_[i]->getEsLider_() << ";"; // bool
		salida << lista_[i]->getGrupo_() << ";"; // int
		salida << lista_[i]->getTelefono_(); // int
		
		salida << endl;
	}
	
	cout<<"\n - Se guardaron correctamente: "<<numAlumnos_<<" alumnos en la base de Datos."<<endl;
	
	salida.close();
	
	return true;
}

bool Agenda::guardarCopiaSeguridad(Profesor * p) // Solo si es coordinador
{
	string s = "";
	
	// Primero hay que determinar si el profesor es coordinador
	if(!p->getCoordinador_())
	{
		cout<<"\n\tNo se puede guardar una copia de Seguridad externa si no eres Coordinador";
		return false;
	}
	
	cout<<"\tDeterminar la ruta para guardar la información: ";
	cin>>s;
	
	return guardarCambios(s);
}

bool Agenda::cargarCopiaSeguridad(Profesor * p) // Solo si es coordinador
{
	string s = "";
	
	// Primero hay que determinar si el profesor es coordinador
	if(!p->getCoordinador_()) // Sale si no es determinada
	{
		cout<<"\n\tNo se puede cargar una copia de Seguridad externa si no eres Coordinador";
		return false;
	}
		
	cout<<"\tDeterminar la ruta para cargar la información: ";
	cin>>s;
	
	return cargarDatos(s);
}
