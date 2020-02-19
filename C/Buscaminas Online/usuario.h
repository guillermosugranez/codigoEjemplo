#ifndef USUARIO_H_
#define USUARIO_H_

#include "auxiliar.h"

typedef struct _InfoServidor InfoServidor;
typedef struct _Partida Partida;
typedef struct _Usuario Usuario;

//---------------------------------------------------------------------------------------------------

struct _Usuario{

	int socket;
	char nombre[30];
	int validado;
	int numBanderas;
	
	void * idPartida;
};

//---------------------------------------------------------------------------------------------------

int entrarUsuario(int socket, char * nombre, InfoServidor * servidor);
int salirUsuario(Usuario * u, InfoServidor * servidor);
int registrarUsuario(char * mensaje);
int comprobarUsuario(const char * nombre);
Usuario * buscarUsuario(int socket, InfoServidor * servidor);
int indicarUsuario(char * nombre, int socket, InfoServidor * servidor);
int validarUsuario(char * mensaje, Usuario * u, InfoServidor * servidor);

#endif