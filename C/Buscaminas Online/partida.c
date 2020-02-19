#include "auxiliar.h"

//---------------------------------------------------------------------------------------------------

/*
	* Antes de inciar Partida hay que estar logueado (validado)
	* Emparejarlo con el primer Usuario de la cola si hay
	* Si no hay meterle en cola
	* Si encuentra un oponente, activar el flag en Partida.
*/
int buscarPartida(Usuario * u, InfoServidor * servidor)
{
	printf("buscarPartida\n");

	char respuesta[MSG_SIZE];
	bzero(respuesta, MSG_SIZE);

	// Compruebo que no esté ya en una partida
	if(u->idPartida != NULL)
	{
		bzero(respuesta, MSG_SIZE);
		sprintf(respuesta, BRED"-Err. Ya estás en una partida.\n"RESET);
		send(u->socket, respuesta, MSG_SIZE, 0);

		return false;
	}

	// Comprobar primero si el Usuario está validado
	if(u->validado)
	{
		// Lo metemos en la cola

		meterCola(u, servidor);

		if(servidor->numPartidas >= MAX_PARTIDAS)
		{
			// Si se ha llegado al maximo de arrayPartidas, toca esperar en la cola
			bzero(respuesta, MSG_SIZE);
			sprintf(respuesta, BRED"-Err. Demasiadas partidas actualmente. En cola hasta que cierre alguna.\n"RESET);
			send(u->socket, respuesta, MSG_SIZE, 0);

			return false;
		}
		else if(servidor->cola[0] != NULL && servidor->cola[1] != NULL)
		{
			// Si no se ha llegado al máximo de arrayPartidas, compruebo que haya dos oponentes en cola

			crearPartida(servidor);

			return true;
		}
		else
		{
			// Si no, tengo que esperar en cola hasta que haya un nuevo oponente
			bzero(respuesta, MSG_SIZE);
			sprintf(respuesta, BYELLOW"+Ok. - la espera de otro jugador.\n"RESET);
			send(u->socket, respuesta, MSG_SIZE, 0);

			return false;
		}
	}
	else
	{
		bzero(respuesta, MSG_SIZE);
		sprintf(respuesta, BRED"-Err. Primero es necesario validar un Usuario registrado.\n"RESET);
		send(u->socket, respuesta, MSG_SIZE, 0);

		return false;
	}
}

void meterCola(Usuario * u, InfoServidor * servidor)
{
	printf("meterCola\n");
	servidor->cola[servidor->usuariosEnCola] = u;
	printf("El Usuario %s ha sido incluido en la cola.\n", servidor->cola[servidor->usuariosEnCola]->nombre);

	servidor->usuariosEnCola++; // Dejamos hueco en la cola
	
	return;
}

void crearPartida(InfoServidor * servidor)
{
	printf("crearPartida.\n");

	srand (time(NULL));

	int numBombas = 20;

	char respuesta[MSG_SIZE];
	bzero(respuesta, MSG_SIZE);

	Partida * p = (Partida*)malloc(sizeof(Partida));

	p->a = servidor->cola[0];
	p->b = servidor->cola[1];

	p->turno = p->a; // El primer turno es para el usuario que estaba antes en la cola
	p->oponente = p->b;

	servidor->cola[0] = NULL;
	servidor->cola[1] = NULL;

	reorganizarCola(servidor);

	p->a->idPartida = (void*)p;
	p->b->idPartida = (void*)p;

	bzero(respuesta, MSG_SIZE);
	sprintf(respuesta, BYELLOW"+Ok. La Partida ha comenzado\n"RESET);
	send(p->a->socket, respuesta, MSG_SIZE, 0);
	send(p->b->socket, respuesta, MSG_SIZE, 0);

	p->tableroSolucion = crearTablero(10);
	p->tableroJugadores = crearTablero(10);

	// Ahora hay que crear los barcos

	crearBombas(p->tableroSolucion, numBombas);

	// Enviar cadena con la tablero a los usuarios
	bzero(respuesta, MSG_SIZE);
	tableroCadena(p->tableroJugadores, respuesta);

	// printf("\n\nEl tamaño de la cadena es: %d\n\n", strlen(respuesta));

	send(p->a->socket, respuesta, MSG_SIZE, 0);
	send(p->b->socket, respuesta, MSG_SIZE, 0);

	//Indicar de quién es el turno
	bzero(respuesta, MSG_SIZE);
	sprintf(respuesta, BYELLOW"+Ok. Es su turno\n"RESET);
	send(p->a->socket, respuesta, MSG_SIZE, 0);

	bzero(respuesta, MSG_SIZE);
	sprintf(respuesta, BYELLOW"+Ok. Es el turno de: %s\n"RESET, p->turno->nombre);
	send(p->b->socket, respuesta, MSG_SIZE, 0);

	// Se incluye en el array de partidas
	servidor->arrayPartidas[servidor->numPartidas] = p;
	(servidor->numPartidas)++; // Se deja hueco para una nueva Partida

	printf("Finaliza crearPartida\n");

	return;
}

void finalizarPartida(Partida * p, InfoServidor * servidor)
{
	printf("finalizarPartida\n");

	int i = 0;

	send(p->a->socket, "La Partida ha terminado", MSG_SIZE, 0);
	send(p->b->socket, "La Partida ha terminado", MSG_SIZE, 0);

	p->a->idPartida = NULL;
	p->b->idPartida = NULL;

	borrarTablero(p->tableroSolucion);
	borrarTablero(p->tableroJugadores);

	p->tableroSolucion = NULL;
	p->tableroSolucion = NULL;

	p->a = NULL;
	p->b = NULL;

	p->turno = NULL;
	p->oponente = NULL;

	//Re-estructurar el array de partidas
	for (i = 0; i < (servidor->numPartidas - 1); i++)
		if (servidor->arrayPartidas[i] == p) // Busca la posicion donde estaba la Partida en el array
			break;

	free(p);

	for (; i < (servidor->numPartidas - 1); i++) // Recorro hasta el final del array (ahora con una posicion menos)
		servidor->arrayPartidas[i] = servidor->arrayPartidas[i+1]; // Incremento la posicion de cada uno para compensar

	(servidor->numPartidas)--;

	if(servidor->cola[0] != NULL && servidor->cola[1] != NULL)
		crearPartida(servidor);

	printf("fin finalizarPartida\n");

	return;
}

/*
	* Pone una bandera en posicion
*/
int ponerBandera(char * mensaje, Usuario * u, InfoServidor * servidor)
{
	printf("ponerBandera\n");

	char respuesta[MSG_SIZE];
	bzero(respuesta, MSG_SIZE);

	Partida * p = (Partida*)u->idPartida;
	Usuario * aux = NULL;

	char letra = -1;
	int x = -1; // Es la letra pero en numero
	int y = -1;

	char bandera;

	int n = 0;

	// Primero hay que comprobar que esta en una Partida
	if(p != NULL)
	{
		// Despues hay que comprobar que sea su turno
		if(p->turno == u)
		{
			n = sscanf(mensaje, "PONER-BANDERA %c,%d\n", &letra, &y);
			printf("La letra es: %c\n", letra);
			printf("El numero es: %d\n", y);

			if(n < 2) // scanf fallido
			{
				bzero(respuesta, MSG_SIZE);
				sprintf(mensaje, IRED"-Err. El formato de PONER-BANDERA debe ser PONER-BANDERA letra,numero\n"RESET);
				send(u->socket, mensaje, MSG_SIZE, 0);
				return false;
			}
			else
			{
				x = (int)(letra - 96);
				printf("La letra convertida en numero es: %d\n", x);

				if(x > 10 || y > 10)
				{
					bzero(respuesta, MSG_SIZE);
					sprintf(mensaje, IRED"-Err. Coordenadas incorrectas, vuelva a intentarlo\n"RESET);
					send(u->socket, mensaje, MSG_SIZE, 0);
					return false;
				}

				// Determina que bandera es
				if(u == p->a)
						bandera = 'A';
					else
						bandera = 'B';

				// Comprueba si puedo poner una bandera
				if(p->tableroJugadores[x][y] == '-' || p->tableroJugadores[x][y] == 'A' || p->tableroJugadores[x][y] == 'B')
				{
					if(p->tableroJugadores[x][y] == 'A' ||p->tableroJugadores[x][y] == 'B')
						bandera = 'C';

					p->tableroJugadores[x][y] = bandera; // Actualiza el tablero con la nueva bandera

					bzero(respuesta, MSG_SIZE);
					sprintf(respuesta, BGREEN"+Ok. Bandera puesta\n"RESET);
					send(u->socket, respuesta, MSG_SIZE, 0);

					bzero(respuesta, MSG_SIZE);
					sprintf(respuesta, BGREEN"+Ok. Nueva bandera puesta en: (%c, %d)\n"RESET, letra, y);
					send(p->oponente->socket, respuesta, MSG_SIZE, 0);

					(u->numBanderas)++;

					// Enviar cadena con el tablero actualizado
					bzero(respuesta, MSG_SIZE);
					tableroCadena(p->tableroJugadores, respuesta);
					send(p->oponente->socket, respuesta, MSG_SIZE, 0);
					send(u->socket, respuesta, MSG_SIZE, 0);

					if(u->numBanderas > 9) // Si ya ha puesto 10 banderas
					{
						bzero(respuesta, MSG_SIZE);

						if(comprobarGanador(u))
						{
							sprintf(respuesta, BGREEN"+Ok. %s ha ganado la partida\n"RESET, u->nombre);
							send(u->socket, respuesta, MSG_SIZE, 0);
							send(p->oponente->socket, respuesta, MSG_SIZE, 0);
						}
						else
						{
							sprintf(respuesta, BGREEN"+Ok. %s ha fallado al poner las banderas y ha perdido la partida\n"RESET, u->nombre);
							send(u->socket, respuesta, MSG_SIZE, 0);
							send(p->oponente->socket, respuesta, MSG_SIZE, 0);
						}

						finalizarPartida(p, servidor);
						return true;
					}
					else // Cambio de turno
					{
						aux = p->turno;
						p->turno = p->oponente;
						p->oponente = aux;
					}
				}
				else if(p->tableroSolucion[x][y] == 'C')
				{
					bzero(respuesta, MSG_SIZE);
					sprintf(mensaje, IRED"-Err. En esta posicion ya hay una bandera puesta por cada jugador. Vuelva a intentarlo\n"RESET);
					send(u->socket, mensaje, MSG_SIZE, 0);
					return false;
				}
				else
				{
					bzero(respuesta, MSG_SIZE);
					sprintf(mensaje, IRED"-Err. No puede poner una bandera en esta posicion. Vuelva a intentarlo\n"RESET);
					send(u->socket, mensaje, MSG_SIZE, 0);
					return false;
				}
			}

			bzero(respuesta, MSG_SIZE);
			sprintf(respuesta, BGREEN"+Ok. Es turno del usuario %s\n"RESET, p->turno->nombre);
			send(p->oponente->socket, respuesta, MSG_SIZE, 0);

			bzero(respuesta, MSG_SIZE);
			sprintf(respuesta, BGREEN"+Ok. Es su turno\n"RESET);
			send(p->turno->socket, respuesta, MSG_SIZE, 0);

			return true;
		}
		else
		{
			bzero(respuesta, MSG_SIZE);
			sprintf(respuesta, BRED"-Err. Debe esperar su turno\n"RESET);
			send(u->socket, respuesta, MSG_SIZE, 0);
			return false;
		}
	}
	else
	{
		bzero(respuesta, MSG_SIZE);
		sprintf(respuesta, BRED"-Err. El Usuario no esta actualmente en ninguna Partida\n"RESET);
		send(u->socket, respuesta, MSG_SIZE, 0);
		return false;
	}

	printf("fin ponerBandera\n");
	return true;
}

/*
	* Descubrir una posicion del tablero
*/
int descubrir(char * mensaje, Usuario * u, InfoServidor * servidor)
{
	printf("descubrir\n");

	char respuesta[MSG_SIZE];
	bzero(respuesta, MSG_SIZE);

	Partida * p = (Partida*)u->idPartida; // Recojo la partida
	Usuario * aux = NULL; // Sirve para cambiar de turno

	char letra = -1;
	int x = -1;
	int y = -1;

	int n = 0;

	// Primero hay que comprobar que esta en una Partida
	if(p != NULL)
	{
		// Despues hay que comprobar que sea su turno
		if(p->turno == u)
		{
			n = sscanf(mensaje, "DESCUBRIR %c,%d\n", &letra, &y);
			printf("La letra es: %c\n", letra);
			printf("El numero es: %d\n", y);

			if(n < 2) // scanf fallido
			{
				sprintf(mensaje, IRED"-Err. El formato de DESCUBRIR debe ser DESCUBRIR letra,numero\n"RESET);
				send(u->socket, mensaje, MSG_SIZE, 0);
				return false;
			}
			else
			{
				x = (int)(letra - 96);
				printf("La letra convertida en numero es: %d\n", x);

				if(x > 10 || y > 10)
				{
					sprintf(mensaje, IRED"-Err. Coordenadas incorrectas, vuelva a intentarlo\n"RESET);
					send(u->socket, mensaje, MSG_SIZE, 0);
					return false;
				}

				if(p->tableroJugadores[x][y] == 'A' || p->tableroJugadores[x][y] == 'B' || p->tableroJugadores[x][y] == 'C')
				{
					sprintf(mensaje, IRED"-Err. No puede descubrir una posicion con una bandera puesta. Vuelva a intentarlo\n"RESET);
					send(u->socket, mensaje, MSG_SIZE, 0);
					return false;
				}
				else if(p->tableroSolucion[x][y] == '-') // Comprueba si había una bomba
				{
					sprintf(respuesta, BGREEN"+Ok. LIMPIO\n"RESET);
					send(u->socket, respuesta, MSG_SIZE, 0);

					sprintf(respuesta, BGREEN"+Ok. Nueva posicion descubierta: (%c, %d)\n"RESET, letra, y);
					send(p->oponente->socket, respuesta, MSG_SIZE, 0);

					actualizarTablero(p, servidor, x, y);

					// Enviar cadena con el tablero actualizado
					tableroCadena(p->tableroJugadores, respuesta);
					send(p->oponente->socket, respuesta, MSG_SIZE, 0);
					send(u->socket, respuesta, MSG_SIZE, 0);

					aux = p->turno;
					p->turno = p->oponente;
					p->oponente = aux;

				}
				else if(p->tableroSolucion[x][y] == '*')
				{
					sprintf(respuesta, BGREEN"+Ok. %s ha descubierto una mina y ha perdido la partida\n"RESET, u->nombre);
					send(u->socket, respuesta, MSG_SIZE, 0);
					send(p->oponente->socket, respuesta, MSG_SIZE, 0);

					finalizarPartida(p, servidor);

					return true;
				}
			}

			sprintf(respuesta, BGREEN"+Ok. Es turno del usuario %s\n"RESET, p->turno->nombre);
			send(p->oponente->socket, respuesta, MSG_SIZE, 0);

			sprintf(respuesta, BGREEN"+Ok. Es su turno\n"RESET);
			send(p->turno->socket, respuesta, MSG_SIZE, 0);

			return true;
		}
		else
		{
			sprintf(respuesta, BRED"-Err. Debe esperar su turno\n"RESET);
			send(u->socket, respuesta, MSG_SIZE, 0);
			return false;
		}
	}
	else
	{
		sprintf(respuesta, BRED"-Err. El Usuario no esta actualmente en ninguna Partida\n"RESET);
		send(u->socket, respuesta, MSG_SIZE, 0);
		return false;
	}

	printf("fin descubrir\n");
	return true;
}

void reorganizarCola(InfoServidor * servidor)
{
	int i = 0;
	int posicion = -1; // Primer elemento de la cola distinto de null

	printf("El tamaño de la cola es: %d\n", TAM_COLA);

	// Reasigno a partir de la primera Partida del vector

	while(i < TAM_COLA)
	{
		if(servidor->cola[i] != NULL)
		{
			posicion = i;
			break;
		}

		i++;
	}

	if(posicion == -1) // Si la cola está totalmente vacía salgo
	{
		servidor->usuariosEnCola = 0;
		return;
	}

	i = 0;

	while(i < TAM_COLA)
	{
		printf("La posicion del primer elemento era: %d. Se pone en cabeza\n", posicion);
		servidor->cola[i] = servidor->cola[i+posicion]; // Desplazo el primer Usuario hasta el principio

		printf("La posicion %d, se establece nula\n", (TAM_COLA-i-1));
		servidor->cola[TAM_COLA-i-1] = NULL; // Relleno por el final

		i++;
	}

	i = 0;
	servidor->usuariosEnCola = 0;

	while(i < TAM_COLA) // Actualiza el numero de usuarios en cola
	{
		if(servidor->cola[i] != NULL)
			servidor->usuariosEnCola++;

		i++;
	}

	printf("Termina reorganizarCola\n");
}

//---------------------------------------------------------------------------------------------------

char ** crearTablero(int n)
{
	printf("crearTablero\n");

	int i, j;

	char ** tablero = (char **)malloc ((n+2)*sizeof(char *));

	for (i=0; i<(n+2); i++)
		tablero[i] = (char *) malloc ((n+2)*sizeof(char));

	// Se inicializa la Tablero

	for(i = 0; i < (n+2); i++)
		for(j = 0; j < (n+2); j++)
			tablero[i][j] = '-';

	printf("fin crearTablero\n");

	return tablero;
}

/*
	- Una vez descubierta una nueva posicion, tiene que actualizar las posiciones de las demas casillas.
*/
void actualizarTablero(Partida * p, InfoServidor * servidor, int x, int y)
{
	printf("actualizarTablero\n");

	// int i = 0;


	printf("fin actualizarTablero\n");
	return;
}

void borrarTablero(char ** tablero)
{
	printf("borrarTablero\n");

	int i;

	for(i = 0; i < 12; i++)
	{
		free(tablero[i]);
		tablero[i] = NULL;
	}

	free(tablero);
	tablero = NULL;

	printf("fin borrarTablero\n");

	return;
}

void tableroCadena(char ** c, char * respuesta)
{
	printf("tableroCadena\n");

	int i,j,k;

	k = 0;

	for(i = 1; i <= 10; i++)
	{
		for(j = 1; j <= 10; j++)
		{
			if(c[i][j] == 'C')
			{
				respuesta[k] = 'A';
				k++;
				respuesta[k] = 'B';
			}
			else
				respuesta[k] = c[i][j];
			k++;
			respuesta[k] = '\t';
			k++;
		}

		respuesta[k] = '\n';
		k++;
	}

	respuesta[k] = '\0';

	printf("fin tableroCadena\n");

	return;
}

void crearBombas(char ** c, int numBombas)
{
	printf("crearBarcos\n");
	
	int fila, columna;

	while(numBombas > 0)
	{
		// Busco una cordenada válida en el tablero (de 1 a 10)
		fila = rand () % 10 + 1;
		columna = rand () % 10 + 1;

		if(c[fila][columna] != '*')
		{
			c[fila][columna] = '*';
			numBombas--;
		}
	}

	printf("fin crearBarcos\n");

	return;
}

int comprobarGanador(Usuario * u)
{
	printf("comprobarGanador\n");

	// Hay que comprobar que las banderas coinciden con las bombas

	printf("fin comprobarGanador\n");

	return false;
}