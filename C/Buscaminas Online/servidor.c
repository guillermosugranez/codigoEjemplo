#include "auxiliar.h"
#include "main.h"
//----------------------------------------------------------------------

int main()
{
	/*---------------------------------------------------- 
		Descriptor del socket y servidor.buffer de datos                
	-----------------------------------------------------*/
		//contadores
		int i, j, k;

		// Servidor
		struct sockaddr_in sockname;
		InfoServidor servidor;

		fd_set auxfds;
		
		int salida; // Salida de la funcion select(). Equivale al descriptor que realiza la comunicacion

		// Se inicializan los vectores del servidor
		for(i = 0; i < MAX_CLIENTS; i++)
			servidor.arrayUsuarios[i] = NULL;
		servidor.numUsuarios = 0; // Se va incrementando conforme se va aceptando a los nuevos clientes y viceversa

		for(i = 0; i < MAX_PARTIDAS; i++)
			servidor.arrayPartidas[i] = NULL;
		servidor.numPartidas = 0;

		for(i = 0; i < MAX_CLIENTS; i++)
			servidor.arrayClientes[i] = -1;
		servidor.numClientes = 0;

		for(i = 0; i < TAM_COLA; i++)
			servidor.cola[i] = NULL;
		servidor.usuariosEnCola = 0; // Numero de usuarios actuales en cola de espera para Partida

		int recibidos; // Cantidad de bytes recibidos con recv()
		
		int on = 1;
	
		i = j = k = 0;

	/* --------------------------------------------------
		Se abre el socket servidor
	---------------------------------------------------*/

		servidor.sd = socket (AF_INET, SOCK_STREAM, 0);

		if (servidor.sd == -1)
		{
			perror("No se puede abrir el socket cliente\n");
			exit (1);	
		}
		
		/*
			* Activaremos una propiedad del socket que permitirá que otros
			sockets puedan reutilizar cualquier puerto al que nos enlacemos.

			* Esto permitirá en protocolos como el TCP, poder ejecutar un
			mismo programa varias veces seguidas y enlazarlo siempre al mismo puerto.

			* De lo contrario habría que esperar a que el puerto
			quedase disponible (TIME_WAIT en el caso de TCP)
		*/
		
		setsockopt(servidor.sd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

		sockname.sin_family = AF_INET;
		sockname.sin_port = htons(2050);
		sockname.sin_addr.s_addr =  INADDR_ANY;

		// Asocia el socket servidor con un puerto
		if (bind (servidor.sd, (struct sockaddr *) &sockname, sizeof (sockname)) == -1)
		{
			perror("Error en la operación bind");
			exit(1);
		}

	/*---------------------------------------------------------------------
		Del las peticiones que vamos a aceptar sólo necesitamos el 
		tamaño de su estructura, el resto de información (familia, puerto, 
		ip), nos la proporcionará el método que recibe las peticiones (accept()).
	----------------------------------------------------------------------*/

		if(listen(servidor.sd, 1) == -1)
		{
			perror("Error en la operación de listen");
			exit(1);
		}
	
		//Inicializar los conjuntos fd_set
		FD_ZERO(&servidor.readfds);
		FD_ZERO(&auxfds);

		/*
			* La funcion select() hace que el programa se bloqueé hasta que ocurra algo en los descriptores señalados
			* Cuando aún no hay ningún cliente, los descriptores señalados (por readfds) son:
				- El Servidor		->	sd	->	Por aqui es por donde llegan las peticiones para conectarse al servidor de los nuevos clientes
				- El teclado		->	0	->	Por aqui es por donde vienen las señales internas como ctrl+c
				- Otro descriptor	->	Por cualquier otro descriptor quiere decir que la informacion viene de un cliente conectado
		*/
		FD_SET(servidor.sd, &servidor.readfds);
		FD_SET(0, &servidor.readfds);
		
		/*
			* signal()

				- Sirve para capturar señales como Ctrl+c
				- permite redefinir la función de tratamiento de señales
				* Parametros:
					- int: Codigo de señal (SIGINT es Ctrl+c)
					- void (*) : funcion a la que llamar cuando encontremos la señal
		*/
		signal(SIGINT, manejador); // Capturamos la señal SIGINT (Ctrl+c)
	
	/*-----------------------------------------------------------------------
		El servidor acepta una petición
	------------------------------------------------------------------------ */

		printf(CLEAR_SCREEN);
		printf(UNDERLINE BIBLUE "\n\tBUSCA MINAS 1.0\n"RESET);
		puts("");

		while(!salir)
		{	
			//Esperamos recibir mensajes de los clientes (nuevas conexiones o mensajes de los clientes ya conectados)
			
			auxfds = servidor.readfds;

			// FD_SETSIZE -> Es el descriptor más alto posible (hace la funcion de maximo respecto a los descriptores)

			salida = select(FD_SETSIZE, &auxfds, NULL, NULL, NULL);

			if(salida > 0) // Solo si llega un mensaje o una señal de algun descriptor
			{
				// Recorre los sockets para buscar cual ha sido el que ha establecido la comunicación
				for(i=0; i<FD_SETSIZE; i++)
				{
					bzero(servidor.buffer,MSG_SIZE);

					if(FD_ISSET(i, &auxfds)) // Primero comprueba que esté en el grupo de socket readfds
					{
						if(i == servidor.sd) /*** NUEVO CLIENTE ***/
						{
							nuevoCliente(&servidor);
						}
						else if (i == 0) /* MENSAJE DEL SERVIDOR */
						{
							//Se ha introducido información de teclado
							fgets(servidor.buffer, MSG_SIZE, stdin);
							
							//Controlar si se ha introducido "SALIR", cerrando todos los sockets y finalmente saliendo del servidor.
							if(strcmp(servidor.buffer, "SALIR\n") == 0)
								salirServidor(&servidor);

							// No hace nada en cualquier otro caso
						} 
						else /*** MENSAJE DE CLIENTE ***/
						{
							recibidos = recv(i, servidor.buffer, MSG_SIZE, 0);
							
							if(recibidos > 0) // El cliente ha enviado un mensaje
								mensajeDeCliente(i, servidor.buffer, &servidor); // Anliza el mensaje
							else if(recibidos == 0)
							{
								printf("El socket %d, ha introducido ctrl+c\n", i);
								salirCliente(i, &servidor);
							}
						}
					}
				}
			}
		} // End While

	salirServidor(&servidor);
}
