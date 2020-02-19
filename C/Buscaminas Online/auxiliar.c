#include "auxiliar.h"

//---------------------------------------------------------------------------------------------------

int salirServidor(InfoServidor * servidor)
{
	printf("salirServidor\n");

	printf("El numero de partidas es: %d\n", servidor->numPartidas);
	printf("El numero de usuarios es: %d\n", servidor->numUsuarios);
	printf("El numero de clientes es: %d\n", servidor->numClientes);

	int i;
	int cliente;

	if(servidor->numClientes > 0)
	{
		for (i = 0; i < servidor->numClientes; i++)
		{
			cliente = servidor->arrayClientes[i];
			printf("El socket %d va a cerrarse.\n", cliente);
			send(servidor->arrayClientes[i], "Desconexion servidor\n", MSG_SIZE,0);
			close(cliente);
			FD_CLR(cliente, &servidor->readfds);
		}
	}

	if(servidor->numPartidas > 0)
	{
		for (i = 0; i < servidor->numPartidas; i++)
		{
			printf("Eliminando partida.\n");
			servidor->arrayPartidas[i]->a = NULL;
			servidor->arrayPartidas[i]->b = NULL;
			free(servidor->arrayPartidas[i]);
		}
	}

	if(servidor->numUsuarios > 0)
	{
		for (i = 0; i < servidor->numUsuarios; i++)
		{
			printf("Eliminando Usuario.\n");
			servidor->arrayUsuarios[i]->idPartida = NULL;
			free(servidor->arrayUsuarios[i]);
		}
	}

	close(servidor->sd);
	exit(-1);

	printf("fin salirServidor\n");

	return 0;
}

void nuevoCliente(InfoServidor * servidor)
{
	printf("nuevoCliente\n");

	int new_sd;
	struct sockaddr_in from;
	socklen_t from_len;

	/*
		* con la funcion accept() recogemos la informacion del cliente y la guardamos en from
		* sd se refiere al socket por donde se realiza la conexion entre el servidor y el cliente
		* new_sd es el nuevo descriptor de socket referente al nuevo cliente
	*/
	if((new_sd = accept(servidor->sd, (struct sockaddr *)&from, &from_len)) == -1)
	{
		perror("Error aceptando peticiones.\n");
		exit(1);
	}
	else
	{
		if(servidor->numClientes < MAX_CLIENTS)
		{
			printf("El socket %d se ha conectado\n", new_sd);
			send(new_sd, "Bienvenido\n", MSG_SIZE, 0);
			servidor->arrayClientes[servidor->numClientes] = new_sd;
			(servidor->numClientes)++;
			FD_SET(new_sd, &servidor->readfds);
		}
		else
		{
			strcpy(servidor->buffer,"Demasiados clientes conectados\n");
			send(new_sd, servidor->buffer, MSG_SIZE, 0);
			close(new_sd);
		}
		
	}

	printf("fin nuevoCliente\n");

	return;
}

void salirCliente(int socket, InfoServidor * servidor)
{
	printf("salirCliente\n");

	int i = 0;
	Usuario * u = NULL;

	//Eliminar primero el Usuario asociado
	if(servidor->numUsuarios > 0)
	{
		printf("\n");
		u = buscarUsuario(socket, servidor);

		if(u != NULL)
			salirUsuario(u, servidor);
	}
	

	// Elimino el cliente
	close(socket);

	FD_CLR(socket, &servidor->readfds);

	//Re-estructurar el array de clientes
	for (i = 0; i < (servidor->numClientes - 1); i++)
		if (servidor->arrayClientes[i] == socket) // Busca la posicion donde estaba el socket en el array
			break;

	for (; i < (servidor->numClientes - 1); i++) // Recorro hasta el final del array (ahora con una posicion menos)
		servidor->arrayClientes[i] = servidor->arrayClientes[i+1]; // Incremento la posicion de cada uno para compensar

	(servidor->numClientes)--;

	printf("fin salirCliente\n");

	return;
}

void mensajeDeCliente(int socket, char * mensaje, InfoServidor * servidor)
{
	printf("mensajeDeCliente\n");

	Usuario * u = NULL;

	if(servidor->numUsuarios > 0)
		u = buscarUsuario(socket, servidor);

	char instruccion[MSG_SIZE];
	bzero(instruccion,MSG_SIZE);

	extraerInstruccion(mensaje, instruccion);

	if(strcmp(instruccion,"SALIR") == 0)
	{
		salirCliente(socket, servidor);
	}
	else if(strcmp(instruccion,"USUARIO") == 0)
	{
		indicarUsuario(mensaje, socket, servidor);
	}
	else if(strcmp(instruccion,"PASSWORD") == 0)
	{
		validarUsuario(mensaje, u, servidor);
	}
	else if(strcmp(instruccion,"INICIAR-PARTIDA") == 0)
	{
		buscarPartida(u, servidor);
	}
	else if(strcmp(instruccion,"REGISTER") == 0)
	{
		registrarUsuario(mensaje);
	}
	else if(strcmp(instruccion,"DESCUBRIR") == 0)
	{
		descubrir(mensaje, u, servidor);
	}
	else if(strcmp(instruccion,"PONER-BANDERA") == 0)
	{
		ponerBandera(mensaje, u, servidor);
	}
	else
	{
		sprintf(mensaje, IRED"-Err. El comando es erroneo.\n"RESET);
		send(socket, mensaje, MSG_SIZE, 0);
	}

	printf("fin mensajeDeCliente\n");

	return;
}

void difusion(const char * mensaje, InfoServidor * servidor)
{
	printf("difusion\n");

	int i = 0;

	for(i=0; i<servidor->numUsuarios-1; i++)
		send(servidor->arrayUsuarios[i]->socket, mensaje, MSG_SIZE, 0);

	printf("fin difusion\n");

	return;
}

/*
	Recorre los primeros caracteres del mensaje para determinar el tipo de mensaje que ha enviado el Usuario
*/
void extraerInstruccion(const char * mensaje, char * instruccion)
{
	printf("extraerInstruccion\n");

	int i = 0;
	
	while(mensaje[i] != ' ' && mensaje[i] != '\0' && mensaje[i] != '\n')
	{
		instruccion[i] = mensaje[i];
		i++;
	}

	printf("fin extraerInstruccion\n");

	return;
}

//---------------------------------------------------------------------------------------------------