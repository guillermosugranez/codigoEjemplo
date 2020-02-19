#ifndef AUXILIAR_H_
#define AUXILIAR_H_

#define MSG_SIZE 250
#define MAX_CLIENTS 6
#define TAM_COLA MAX_CLIENTS - (MAX_PARTIDAS*2)
#define MAX_PARTIDAS 1

#define true 1
#define false 0

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

// Cabeceras Nuevas

#include <signal.h> // signal (), SIGINT 
#include <time.h>
#include <arpa/inet.h>

#include "partida.h"
#include "usuario.h"
#include "macros.h"

//---------------------------------------------------------------------------------------------------

typedef struct _InfoServidor InfoServidor;
typedef struct _Partida Partida;
typedef struct _Usuario Usuario;

struct _InfoServidor{

	int sd;
	fd_set readfds;

	int numUsuarios;
	Usuario * arrayUsuarios[MAX_CLIENTS];

	int usuariosEnCola;
	Usuario * cola[TAM_COLA];

	int numPartidas;
	Partida * arrayPartidas[MAX_PARTIDAS];

	int numClientes;
	int arrayClientes[MAX_CLIENTS];

	// Mensaje
	char buffer[MSG_SIZE];
};

//---------------------------------------------------------------------------------------------------

int salirServidor(InfoServidor * servidor);
void nuevoCliente(InfoServidor * servidor);
void salirCliente(int socket, InfoServidor * servidor);
void mensajeDeCliente(int socket, char * mensaje, InfoServidor * servidor);
void difusion(const char * mensaje, InfoServidor * servidor);
void extraerInstruccion(const char * cadena, char * subcadena);

#endif