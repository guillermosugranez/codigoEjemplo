# Makefile practica 6. BACKTRACKING, ALGORITMOS PROBABILISTICOS

all: servidor

servidor: servidor.o auxiliar.o partida.o usuario.o
	gcc -Wall -o servidor servidor.o auxiliar.o partida.o usuario.o

servidor.o: servidor.c auxiliar.h partida.h usuario.h macros.h main.h
	gcc -Wall -c servidor.c

auxiliar.o: auxiliar.c auxiliar.h partida.h usuario.h macros.h
	gcc -Wall -c auxiliar.c

partida.o: partida.c auxiliar.h partida.h usuario.h macros.h
	gcc -Wall -c partida.c

usuario.o: usuario.c auxiliar.h partida.h usuario.h macros.h
	gcc -Wall -c usuario.c

clean:
	rm -f servidor *.o
