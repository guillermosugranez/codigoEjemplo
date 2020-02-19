#######################################

Se pide un número por pantalla y un 
número de intentos y ha de resolverse 
indicando el programa si el numero es 
menor o mayor por cada intento que se 
realice.

#######################################

_borrar;

_lugar(10,20);
escribir_cadena('!!! Adivinar el número... !!!\n');

escribir_cadena('\n - Introduce el numero secreto: ');
leer(respuesta);

escribir_cadena('\n - Introduce el numero de intentos: ');
leer(intentos);

escribir_cadena('\n');
_borrar;

repetir
	_lugar(13,20);
	escribir_cadena('Introduce un numero: ');
	leer(numero);
	si(numero=respuesta)
		entonces
		_borrar;
		_lugar(10,10);
		escribir_cadena('Verdadero! HAS ACERTADO !! \n');
		intentos:=0;
	si_no
		_borrar;
		_lugar(14,20);
		si(numero>respuesta)
		entonces
			escribir_cadena('Falso!, el número es MENOR\n');
		si_no
			escribir_cadena('Falso!, el número es MAYOR\n');
		fin_si;
		intentos := intentos--; @ Ejemplo de decremento
		si(intentos = 0)
		entonces
			_lugar(16,20);
			escribir_cadena('\tLo sentimos. No tienes mas intentos.');
		fin_si;
	fin_si;
hasta(intentos = 0);

_lugar(17,10);
escribir_cadena('\tHemos acabado. Hasta Pronto !!\n\n');