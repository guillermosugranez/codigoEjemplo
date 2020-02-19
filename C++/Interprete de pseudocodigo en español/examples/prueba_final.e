#
dato = 1;
dato_1 = 1;
dato_1_a = 1;
_dato = 1;
dato_ = 1;
dato__1 = 1;
#

#
a:=3; 
b:=6;
c := a _mod b;
escribir c;
#

#
a:=3; 
b:=6;

	si(_no a = 3 _o b = 6)
		escribir a;
	si_no
		escribir b;	

c:= -b _div a;
escribir c;

#

#
@ NUMEROS
a:=-1E10;
b:= -1 * a;
escribir a;
escribir b;
c:= a + b;
escribir c;
#

#

@ Sentencia if else

leer(a);
si (a = 3) entonces
	{
		escribir 1;
	}
si_no
	{
		escribir 0;
	}
fin_si

#

#
leer(a);
b:=0;

mientras (a <> b) hacer
{
	escribir 0;
	a := a - 1;
}
fin_mientras
#

#
leer(a);
b:=0;

repetir
{
	escribir 0;
	a := a - 1;
} hasta (a <> b)
#

#
a:=3;
a++;
escribir a;
#

#
a:=3;
a--;
escribir a;
#

#
escribir_cadena 'Hola mundo. Empieza la cuenta atrás\n';

a:=3;

para b
	desde 1
	hasta 5
	hacer
		{
			escribir a;
			a:=a-1;
			escribir_cadena'\n';
		}
fin_para
#