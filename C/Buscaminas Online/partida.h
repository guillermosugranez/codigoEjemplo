#ifndef PARTIDA_H_
#define PARTIDA_H_

#include "auxiliar.h"

typedef struct _InfoServidor InfoServidor;
typedef struct _Partida Partida;
typedef struct _Usuario Usuario;

//---------------------------------------------------------------------------------------------------

struct _Partida{

	Usuario * a;
	Usuario * b;

	// Se van alternando los valores para determinar quien tiene el turno
	Usuario * turno;
	Usuario * oponente;

	char ** tableroJugadores;
	char ** tableroSolucion;
};

//---------------------------------------------------------------------------------------------------

int buscarPartida(Usuario * u, InfoServidor * servidor);
void meterCola(Usuario * u, InfoServidor * servidor);
void crearPartida(InfoServidor * servidor);
void finalizarPartida(Partida * p, InfoServidor * servidor);
void reorganizarCola(InfoServidor * servidor);

char ** crearTablero(int n);
void actualizarTablero(Partida * p, InfoServidor * servidor, int x, int y);
void borrarTablero(char ** c);
void tableroCadena(char ** c, char * respuesta);

void crearBombas(char ** c, int numBombas);
int descubrir(char * mensaje, Usuario * u, InfoServidor * servidor);
int ponerBandera(char * mensaje, Usuario * u, InfoServidor * servidor);
int comprobarGanador(Usuario * u);

#endif