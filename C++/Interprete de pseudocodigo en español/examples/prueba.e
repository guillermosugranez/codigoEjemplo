#
a:=1; @ 1
escribir(a);
a:*=3; @ 3
escribir(a);
a:/=3; @ 1
escribir(a);
a:+=3; @ 4
escribir(a);
a:-=2; @ 2
escribir(a);
a:=a++; @ 3
escribir(a);
a:=a--; @ 2
escribir(a);

si(a=2)entonces
escribir_cadena('funciona!!\n');
fin_si
#

a:='cadena grande';
b:='cadena';

si(a>b)entonces
escribir_cadena('>\n');
escribir(1);
fin_si

a:=1;
b:=2;

si(a<b)entonces
escribir_cadena('<\n');
escribir(1);
fin_si

a:='cadena grande';
b:='cadena';

si(a>=b)entonces
escribir_cadena('>=\n');
escribir(1);
fin_si

si(a<=b)entonces
escribir_cadena('<=\n');
escribir(1);
fin_si

si(a=b)entonces
escribir_cadena('=\n');
escribir(1);
fin_si

si(a<>b)entonces
escribir_cadena('<>\n');
escribir(1);
fin_si


#
para a desde 1 hasta 5 paso 1
hacer
escribir(a);
escribir_cadena('\n');
a:=a+1;
fin_para
#
#
a:=3;
repetir
	escribir(a);
	a:=a-1;
hasta(a<>0)
#
#
a:=3;
mientras(a>0) hacer
	escribir(a);
	a:=a-1;
fin_mientras
#
#
escribir_cadena('Introduce el Valor de a: ');
leer(a);
escribir_cadena('El Valor de a es: ');
escribir(a);

si(a=3) entonces
	escribir_cadena('\ncorrecto! es 3\n');
	escribir(1);
si_no
	si(a=5) entonces
		escribir_cadena('correcto! es 5\n');
		escribir(1);
	si_no
		escribir_cadena('No es ninguna\n');
		escribir(0);
	fin_si
fin_si
#

