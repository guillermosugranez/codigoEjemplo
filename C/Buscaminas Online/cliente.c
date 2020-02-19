#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h> // socklen_t, accept(), bind(), connect(), socket()...
#include <netinet/in.h>
#include <netdb.h>

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>

#define MSG_SIZE 250

int main(int argc, char ** argv)
{
	char * ip_Servidor;

	if(argc < 2)
	{
		perror("No se ha introducido la direccion del servidor\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		ip_Servidor = argv[1];
	}
  
	/*---------------------------------------------------- 
		Descriptor del socket y buffer de datos                
	-----------------------------------------------------*/
		
		int sd; // Socket Cliente. Hace de interfaz entre el cliente y el servidor

		struct sockaddr_in sockname; // Informacion del cliente
		socklen_t len_sockname; // Tamaño de la estructura del Cliente

		char buffer[MSG_SIZE]; // Buffer para el mensaje

		/*
			* readfds

			- Es un puntero a los descriptores de los que nos interesa saber si hay 
			algún dato disponible para leer o que queremos que se nos avise cuando lo haya.
			- También se nos avisará cuando haya un nuevo cliente o cuando un cliente cierre la conexión.
		*/
		fd_set readfds;
		fd_set auxfds; // Conjunto auxiliar para

		// Inicializamos las estructuras
		// FD_ZERO (fd_set *) nos vacía el puntero, de forma que estamos indicando que no nos interesa ningún descriptor de fichero.
		FD_ZERO(&auxfds);
		FD_ZERO(&readfds);

		int salida;
		int fin = 0; // Es un flag que indica si queremos salir de la conexión
	
	
	/* --------------------------------------------------
		Se abre el socket Cliente
	---------------------------------------------------*/

		// AF_INET es la familia de direcciones (IPv4)
		// SOCK_STREAM indica que se trata de un socket TCP (Orientado a Conexión)
		// El 0 en el tercer argumento hace que el sistema elija el protocolo

		sd = socket (AF_INET, SOCK_STREAM, 0);
		if (sd == -1)
		{
			perror("No se puede abrir el socket cliente\n");
			exit (1);	
		}


	/* ------------------------------------------------------------------
		Se rellenan los campos de la estructura con la IP del 
		servidor y el puerto del servicio que solicitamos
	-------------------------------------------------------------------*/
	
		sockname.sin_family = AF_INET; // Familia de protocolos
		sockname.sin_port = htons(2050); // Puerto de comunicacion entre servidor y cliente
		sockname.sin_addr.s_addr = inet_addr(ip_Servidor); // IP del servidor


	/* ------------------------------------------------------------------
		Se solicita la conexión con el servidor
	-------------------------------------------------------------------*/
		
		len_sockname = sizeof(sockname);
		
		if (connect(sd, (struct sockaddr *)&sockname, len_sockname) == -1)
		{
			perror ("Error de conexión"); // El servidor debe estar funcionando previamente
			exit(1);
		}
	
	/* ------------------------------------------------------------------
		Se transmite la información
	-------------------------------------------------------------------*/
	
		/*
			* Funcion select()

			- Esta funcion hace que el servidor duerma mientras no ocurra nada
			* Actua y atiende a un cliente si:
				- Quiere conectarse
				- Pide un servicio
			- El servidor le asigna a cada cliente un numero de cliente y se lo envía
		*/

		// FD_SET -> Añade un descriptor de socket al conjunto readfds
		FD_SET(0,&readfds); // El 0 representa el teclado
		FD_SET(sd,&readfds); // sd representa al cliente

		do
		{
			auxfds = readfds;
			salida = select(sd+1,&auxfds,NULL,NULL,NULL);
			
			// Si llega un mensaje al cliente
			if(FD_ISSET(sd, &auxfds))
			{	
				bzero(buffer,MSG_SIZE); // Limpia el buffer para 
				recv(sd,buffer,MSG_SIZE,0);

				//printf("\n\nEl tamaño de la cadena es: %d\n\n", strlen(buffer));
				
				printf("\n%s\n",buffer);
				
				if(strcmp(buffer,"Demasiados clientes conectados\n") == 0)
					fin =1;
				
				if(strcmp(buffer,"Desconexion servidor\n") == 0)
					fin =1;	
			}
			else //He introducido información por teclado (para enviar una señal de sistema)
			{
				if(FD_ISSET(0,&auxfds))
				{
					bzero(buffer,MSG_SIZE); // Limpiamos el buffer para poder meter nueva información
					fgets(buffer,MSG_SIZE,stdin); // Copiamos la entrada por teclado
					
					if(strcmp(buffer,"SALIR\n") == 0)
					{
						fin = 1; // Salimos si encontramos SALIR
					}
					
					send(sd, buffer, MSG_SIZE, 0); // Enviamos SALIR al servidor para decir que queremos salir
				}
			}			
		} while(fin == 0);
			
		close(sd);

		return 0;
}
