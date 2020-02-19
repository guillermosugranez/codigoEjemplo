#######################################

Se imprimen los numeros primos
que existen en un rango determinado por 
pantalla si éste es válido

#######################################

_borrar;

repetir

	control:=0;

	_lugar(6,20);
	escribir_cadena('!!! Encontrar Numeros Primos !!!\n');

	_lugar(10,20);
	escribir_cadena('\n - Introduce el primer valor del rango: ');
	leer(primero);

	escribir_cadena('\n - Introduce el ultimo valor del rango: ');
	leer(ultimo);

	si(primero <= ultimo) entonces

		control:=1;
		escribir_cadena('\n * Los números primos encontrados son los siguientes: \n\n');

	si_no

		_borrar;
		_lugar(8,20);
		escribir_cadena('El rango introducido no es válido. Por favor introduzca un rango válido\n');

	fin_si

hasta (control = 1)

para j desde primero hasta ultimo hacer

	@ por definicion el 1 no es primo, se empieza en 2
	a:=0;

	para i desde 1 hasta ultimo paso 1 hacer

	si(j _mod i = 0) entonces

		@ si num1 módulo de i es 0, incrementamos a en 1.
		a := a++;

	fin_si

	fin_para

	si(a = 2) entonces
		
		@ si solo tiene dos números divisores entonces es primo y se imprime
		escribir_cadena(' ');
		escribir(j);

	fin_si

fin_para