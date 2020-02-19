# Ejemplo de GnuPlot

set term png

set title  "VOTE"
set ylabel "CCR"
set xlabel "Nº de Iteraciones"
set output "CCR_VOTE_400.png"
plot "datos.dat" using 1:5 title "CCR" with points