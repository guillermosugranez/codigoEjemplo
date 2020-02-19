#
@ Esto es un comentario de una linea
dato :=3;
dato_1:= 3.3E-3;
dato_1_a := -3e3;
escribir(-dato);
escribir(dato_1);
escribir(dato_1_a);

_dato:=3;
dato_ :=3.3;
dato__1 := 3e3;

	- Ahora seguiremos con las comprobaciones

escribir(3-4);
a:='hola mundo';
#
@ **** FIN SI ****
#

leer(a);
si(a=3)
	entonces
	escribir_cadena('Verdadero!');
	si_no
	escribir_cadena('falso!');
fin_si;

escribir_cadena('hemos acabado\n');
#

#
@ **** MIENTRAS ****
mientras(a=3) hacer
	escribir_cadena(' Introduce un valor para la variable a:\t');
	leer(a);
fin_mientras;
#

#
@ **** REPETIR HASTA ****
escribir_cadena('\tEjemplo para repetir:');

repetir
	escribir_cadena(' Introduce un valor para la variable a:\t');
	leer(a);
hasta(a=3);
#
#
@ **** PARA ****
escribir_cadena('\tEjemplo para for:\n');
a:=7;
escribir(a);
escribir_cadena('\n');
para a desde 7 hasta 5 paso -1 hacer
	escribir_cadena('Linea\n');
fin_para;
escribir(a);
escribir_cadena('\n');
escribir_cadena('Hemos terminado el ejemplo\n');
#
#
@ **** ++ ****
a:=3;
escribir_cadena('Primera prueba');
escribir(a);
a:=a++;
escribir(a);
escribir_cadena('Segunda prueba');
a++;
escribir(a);
#
#
@ **** -- ****
escribir_cadena('Decremento');
escribir_cadena('Primera prueba');
escribir(a);
a:=a--;
escribir(a);
escribir_cadena('Segunda prueba');
a--;
escribir(a);
#

#
@ **** +:= ****
escribir_cadena('Suma asignacion');
a:=3;
escribir(a);
a+:=1;
escribir(A);
escribir_cadena('Fin de la prueba');
#

#
@ **** -:= ****
escribir_cadena('Suma asignacion');
a:=3;
escribir(a);
a-:=1;
escribir(A);
escribir_cadena('Fin de la prueba');
#

#
@ **** repetir ****
escribir_cadena('\tEjemplo para repetir:');
a:=1;
escribir(a);
repetir
	a++;
	escribir_cadena('El valor de la variable a es: \t');
	escribir(a);
hasta(a=8);
#

#
@ **** division_entera ****
a:=6;
b:=3;
c:=a _div b;
escribir(a);
escribir(b);
escribir(c);
#

#
@ **** multiplicacion ****
a:=6.1;
b:=3;
c:=a / b;
escribir(a);
escribir(b);
escribir(c);
#

#
@ **** modulo ****
a:=6.1;
b:=5;
c:=a _mod b;
escribir(a);
escribir(b);
escribir(c);
#

#
@ **** potencia ****
a:=2;
b:=3;
c:=a ** b;
escribir(a);
escribir(b);
escribir(c);
#

#
@ **** restar ****
a:=2;
b:=3;
c:=a - b;
escribir(a);
escribir(b);
escribir(c);
#

#
@ **** sumar ****
a:=2;
b:=3;
c:=a + b;
escribir(a);
escribir(b);
escribir(c);
#
#
@ **** incrementar ****
a:=2;
b:=3;
c:=a + b;
c++;
escribir(a);
escribir(b);
escribir(c);
#

#
@ **** incrementar ****
a:=2;
b:=3;
c:=a + b;
c--;
escribir(a);
escribir(b);
escribir(c);
#

#
@ **** Varios ****
a:=2;
escribir(a);
a++;
escribir(a);
a:=-a;
escribir(a);
a:=+a;
escribir(a);
#

_borrar;
altura:=10;
i:= 0;
j:= 0;
aleatorio:=Azar();
para i desde 1 hasta 9 paso 1 hacer
	_lugar(altura,10);
	para j desde 9 hasta 1 paso -1 hacer
		aleatorio +:= 2 ** 0.9 ;
		aleatorio := aleatorio _mod 10;
		si(i = j) entonces
			escribir_cadena(' [ * ] ');
		si_no
			si(i>j) entonces
				si(aleatorio _mod 2 = 0) entonces	
					escribir_cadena(' [ ');
					escribir(aleatorio);
					escribir_cadena(' ] ');
				si_no
					escribir_cadena(' [   ] ');
				fin_si;
			si_no
				si(aleatorio _mod 2 <> 0) entonces	
					escribir_cadena(' [ ');
					escribir(aleatorio);
					escribir_cadena(' ] ');
				si_no
					escribir_cadena(' [   ] ');
				fin_si;
			fin_si;
		fin_si;
	fin_para;
	altura+:=1;
	escribir_cadena('\n');
fin_para;

_lugar(20,10);
escribir_cadena('Fin del programa\n\n');