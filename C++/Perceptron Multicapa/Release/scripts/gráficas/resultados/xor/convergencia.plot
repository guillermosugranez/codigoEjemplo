# Ejemplo de GnuPlot

set term png

set title  "XOR"
set ylabel "Error"
set xlabel "Número de Iteraciones"
set output "Convergencia_XOR_100.png"
plot "datos.dat" using 1:2 title "Train Error" with lines, "datos.dat" using 1:3 title "Validation Error" with lines, "datos.dat" using 1:4 title "Test Error" with lines