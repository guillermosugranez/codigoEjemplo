#include "auxiliar.h"

//---------------------------------------------------------------------------------------------------

/*
	* Devuelve el puntero del nuevo cliente
*/
int entrarUsuario(int socket, char * nombre, InfoServidor * servidor)
{
	printf("entrarUsuario\n");

	char respuesta[MSG_SIZE];
	bzero(respuesta, MSG_SIZE);

	Usuario * u = (Usuario*)malloc(sizeof(Usuario));

	// Se inicializa la estructura
	u->socket = socket;
	strcpy(u->nombre, nombre);

	u->validado = false;
	u->idPartida = NULL;
	u->numBanderas = 0;

	// Se manda la respuesta al cliente
	sprintf(respuesta, BGREEN"+Ok. Usuario Conectado\n"RESET);
	send(u->socket, respuesta, MSG_SIZE, 0);

	servidor->arrayUsuarios[servidor->numUsuarios] = u;
	(servidor->numUsuarios)++;

	return true;
}

/*
	* Elimina al Usuario u
*/
int salirUsuario(Usuario * u, InfoServidor * servidor)
{
	printf("salirUsuario\n");

	int i = 0;

	// Comprobar que esta en una Partida
	if(u->idPartida != NULL)
		finalizarPartida((Partida*)u->idPartida, servidor);

	//Re-estructurar el array de clientes
	for (i = 0; i < (servidor->numUsuarios - 1); i++)
		if (servidor->arrayUsuarios[i] == u) // Busca la posicion donde estaba el socket en el array
			break;

	free(u);

	for (; i < (servidor->numUsuarios - 1); i++) // Recorro hasta el final del array (ahora con una posicion menos)
		servidor->arrayUsuarios[i] = servidor->arrayUsuarios[i+1]; // Incremento la posicion de cada uno para compensar

	(servidor->numUsuarios)--;

	printf("fin salirUsuario\n");

	return true;
}

/*
	* Registra en el fichero de usuarios un nuevo Usuario con su contraseña correspondiente

	* Retorna true o false en funcion del existo de la operacion
*/
int registrarUsuario(char * mensaje)
{
	printf("Registrar Usuario\n");

	char password[MSG_SIZE];
	bzero(password, sizeof(password));

	char nombre[MSG_SIZE];
	bzero(nombre, sizeof(nombre));

	char * aux = NULL;
	int i = 0;

	int flag_password = false;
	int flag_nombre = false;

	 /*** SE EXTRAE EL NOMBRE ***/

	aux = strstr(mensaje, " -u ");

	if(aux)
	{
		aux = aux + 4; // Hay que adelantarse 4 posiciones en el vector correspondientes a " -u "

		while(aux[i] != ' ' && aux[i] != '\0' && aux[i] != '\n')
		{
			nombre[i] = aux[i];
			i++;
		}

		nombre[i] = '\0';
		flag_nombre = true;
	}
	else
	{
		bzero(mensaje, MSG_SIZE);
		strcpy(mensaje, BRED"-Err. No se ha podido registar al Usuario. Orden -u no encontrada o no valida\n"RESET);
		return false;
	}

	if(comprobarUsuario(nombre))
	{
		bzero(mensaje, MSG_SIZE);
		strcpy(mensaje, BRED"-Err. EL Usuario introducido ya está registrado\n"RESET);
		return false;
	}

	/*** SE EXTRAE EL PASSWORD ***/

	aux = strstr(mensaje, " -p ");

	if(aux)
	{
		i = 0;

		aux = aux + 4;

		while(aux[i] != ' ' && aux[i] != '\0' && aux[i] != '\n')
		{
			password[i] = aux[i];
			i++;
		}

		password[i] = '\0';
		flag_password = true;
	}
	else
	{
		bzero(mensaje, MSG_SIZE);
		strcpy(mensaje, BRED"-Err. No se ha podido registar al Usuario. Orden -p no encontrada o no valida\n"RESET);
		return false;
	}

	/*** SE PROCEDE AL REGISTRO ***/

	if(flag_nombre && flag_password)
	{
		// Se abre un fichero para escritura al final del contenido, si no existe se crea.
		FILE * registro = fopen("usuarios.txt", "a");

		fprintf(registro, "%s %s\n", nombre, password);
		fclose(registro);

		bzero(mensaje, MSG_SIZE);
		strcpy(mensaje, BGREEN"+Ok. Usuario registrado con exito\n"RESET);
		return true;
	}
	else
	{
		bzero(mensaje, MSG_SIZE);
		strcpy(mensaje, BRED"-Err. No se ha podido registar al Usuario. Debe haber un Usuario y una contraseña\n"RESET);
		return false;
	}
}

/*
	* Comprueba que el Usuario se encuentra en la lista de usuarios registrados (usuarios.txt)
*/
int comprobarUsuario(const char * nombre)
{
	printf("comprobarUsuario\n");

	int i = 0;

	char linea[MSG_SIZE]; // Aqui van las lineas que vamos leyendo del fichero

	char aux[30]; // Nombre auxiliar que vamos creando en cada iteracion
	bzero(aux, sizeof(aux)); // Inicializa aux

	FILE * registro;

	if((registro = fopen("usuarios.txt","r"))) // Se abre un fichero para escritura al final del contenido, si no existe se crea.
	{
		while(fgets(linea, MSG_SIZE, (FILE*) registro)) // Mientras haya lineas
		{
			i = 0;
			bzero(aux, sizeof(aux));

			while(linea[i] != ' ')
			{
				aux[i] = linea[i];
				i++;
			}

			if(strcmp(aux, nombre) == 0) // Si lo ha encontrado se para
				break;
		}

		fclose(registro);

		if(strcmp(aux, nombre) == 0)
			return true;
		else
			return false;
	}
	else
	{
		perror("El archivo no se pudo abrir\n");
		return false;
	}
}

/*
	* Esta funcion te devuelve el puntero del cliente cuyo socket es el indicado por el parametro socket
*/
Usuario * buscarUsuario(int socket, InfoServidor * servidor)
{
	printf("buscarUsuario\n");

	int i = 0;

	printf("El numero de usuarios es: %d\n", servidor->numUsuarios);
	for(i = 0; i < servidor->numUsuarios; i++)
	{
		if(servidor->arrayUsuarios[i]->socket == socket)
		{
			printf("fin buscarUsuario\n");
			return servidor->arrayUsuarios[i];
		}
	}

	printf("fin buscarUsuario\n");
	return NULL;
}

/*
	Comprueba que el nombre de Usuario aparezca en usuarios.txt
*/
int indicarUsuario(char * mensaje, int socket, InfoServidor * servidor)
{
	printf("indicarUsuario\n");

	char respuesta[MSG_SIZE];
	bzero(respuesta, MSG_SIZE);

	char nombre[30];
	bzero(nombre, sizeof(nombre));

	int i = 8; // 8 = U S U A R I O + el primer espacio

	while(mensaje[i] != ' ' && mensaje[i] != '\0' && mensaje[i] != '\n')
	{
		nombre[i-8] = mensaje[i];
		i++;
	}

	if(servidor->numUsuarios > 0)
	{
		for(i = 0; i < servidor->numUsuarios; i++)
		{
			if(strcmp(servidor->arrayUsuarios[i]->nombre, nombre) == 0)
			{
				sprintf(respuesta, BRED"-Err. El Usuario introducido ya está logueado\n"RESET);
				send(socket, respuesta, MSG_SIZE, 0);
				return false;
			}
		}
	}

	if(comprobarUsuario(nombre))
	{
		entrarUsuario(socket, nombre, servidor);
		sprintf(respuesta, BGREEN"+Ok. Usuario correcto\n"RESET);
		send(socket, respuesta, MSG_SIZE, 0);
		return true;
	}
	else
	{
		sprintf(respuesta, BRED"-Err. Usuario incorrecto\n"RESET);
		send(socket, respuesta, MSG_SIZE, 0);
		return false;
	}
}

/*
	* Comprueba el password una vez introducido el Usuario
*/
int validarUsuario(char * mensaje, Usuario * u, InfoServidor * servidor)
{
	printf("validarUsuario\n");

	char respuesta[MSG_SIZE];
	bzero(respuesta, MSG_SIZE);

	int i = 0;
	int j = 0;

	char password[15]; // Aqui va la password que recojamos del fichero
	bzero(password, sizeof(password)); // Inicializa password

	char linea[MSG_SIZE]; // Aqui van las lineas que vamos leyendo del fichero

	char aux[30]; // Nombre auxiliar que vamos creando en cada iteracion
	bzero(aux, sizeof(aux)); // Inicializa aux

	//----------------------------------------------------------------------------------------------------------------

	if(!u->validado) // Solo si no está validado
	{
		/* EXTRAIGO LA PASSWORD DEL MENSAJE DEL CLIENTE */

		i = 9; // 9 = P A S S W O R D + el primer espacio

		while(mensaje[i] != ' ' && mensaje[i] != '\0' && mensaje[i] != '\n')
		{
			//printf("El char es: %c\n", mensaje[i]);
			password[i-9] = mensaje[i];
			i++;
		}

		//--------------------------------------------------------------------------------------------------------------------

		/* LA COMPARO CON LA DEL REGISTRO */

		i = 0;

		FILE * registro;

		if((registro = fopen("usuarios.txt","r"))) // Se abre un fichero para escritura al final del contenido, si no existe se crea.
		{
			while(fgets(linea, MSG_SIZE, (FILE*) registro)) // Mientras haya lineas
			{
				i = 0;
				bzero(aux, sizeof(aux));

				while(linea[i] != ' ')
				{
					aux[i] = linea[i];
					i++;
				}

				if(strcmp(aux, u->nombre) == 0) // Encuentro la linea donde está el Usuario
				{
					j = 0;
					i++; // Avanzo una posicion y me salto el espacio
					bzero(aux, sizeof(aux));

					while(linea[i] != ' ' && linea[i] != '\n' && linea[i] != '\0')
					{
						aux[j] = linea[i]; // Copio la password
						i++;
						j++;
					}

					break;
				}
			}

			fclose(registro);

			if(strcmp(aux, password) == 0)
			{
				u->validado = true;
				sprintf(respuesta, BGREEN"+Ok. Usuario Validado\n"RESET);
				send(u->socket, respuesta, MSG_SIZE, 0);
				return true;
			}
			else
			{
				sprintf(respuesta, BRED"-Err. Error en la validación\n"RESET);
				send(u->socket, respuesta, MSG_SIZE, 0);
				return false;
			}
		}
		else
		{
			perror("El archivo no se pudo abrir\n");
			return false;
		}
	}
	else
	{
		sprintf(respuesta, BRED"-Err. Error en la validación, el Usuario ya está validado\n"RESET);
		send(u->socket, respuesta, MSG_SIZE, 0);
		return false;
	}
}

