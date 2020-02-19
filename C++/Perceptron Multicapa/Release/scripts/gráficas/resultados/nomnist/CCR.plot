# Ejemplo de GnuPlot

set term png

set title  "NOMNIST"
set ylabel "CCR Test"
set xlabel "Nº de Iteraciones"
set output "CCR_NOMNIST_400.png"
plot "datos.dat" using 1:5 title "CCR" with points