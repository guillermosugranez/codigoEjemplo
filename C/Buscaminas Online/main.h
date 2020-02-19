#ifndef MAIN_H_
#define MAIN_H_

int salir = false;

void manejador (int signum)
{
	//int i = 0;

	printf("\nSe ha recibido la señal sigint\n");
	signal(SIGINT,manejador);

	// Implementar lo que se desee realizar cuando ocurra la excepción de ctrl+c en el servidor

	salir = true; // Hace que el bucle while pare y salga liberando memoria correctamente con la funcion salirServidor()
}

#endif