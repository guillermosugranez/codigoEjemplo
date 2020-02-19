#######################################

Se resuelven ecuciones de segundo grado
introduciendo los parámetros por
pantalla.

Si no existen soluciones se indica, y 
si las hay, se muestran al final.

#######################################

_borrar;

_lugar(10,20);
escribir_cadena('!!! Resolver Ecuaciones de 2º grado !!!\n');

escribir_cadena('\n - Introduce a: ');
leer(a);

escribir_cadena('\n - Introduce b: ');
leer(b);

escribir_cadena('\n - Introduce el término independiente c: ');
leer(c);

neg := -b;

raizcua := b**2-4*a*c;

raizcua := raizcua**0.5;

si(raizcua > 0) entonces
	_borrar;
	_lugar(10,20);
	escribir_cadena('\n - La primera solución x1 es: ');
	totalx1:=(NEG+Raizcua)/(2*a);
	escribir(Totalx1);

	escribir_cadena('\n - La segunda solucion x2 es: ');
	totalx2:=(NEG-Raizcua)/(2*a);
	escribir(Totalx2);
si_no
	_borrar;
	_lugar(10,20);
	escribir_cadena('La ecuacion no se puede resolver porque la raíz es negativa.');
fin_si
