# Makefile practica 6. BACKTRACKING, ALGORITMOS PROBABILISTICOS

all: practica6

practica6: main.o funciones.o estructuraSoluciones.o
	g++ -Wall -o practica6 main.o funciones.o estructuraSoluciones.o

main.o: main.cpp funciones.hpp estructuraSoluciones.hpp
	g++ -Wall -c main.cpp

funciones.o: funciones.cpp funciones.hpp estructuraSoluciones.hpp
	g++ -Wall -c funciones.cpp

estructuraSoluciones.o: estructuraSoluciones.cpp estructuraSoluciones.hpp
	g++ -Wall -c estructuraSoluciones.cpp

clean:
	rm -f practica6 *.o
