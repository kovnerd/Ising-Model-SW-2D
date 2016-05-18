set term pdfcairo
set output "Ising_2D_Square_SW_SpecHeat.pdf"
set size 1, 1
set autoscale
unset log
unset label
set xtic auto
set ytic auto
set title " Plot of Specific Heat  vs Temperature for Different Lattice sizes"
set ylabel "Specific Heat"
set xlabel "Temperature" 
plot "2DSquareModelSWResults5x5.dat" using 1:5 title "L = 5" with lines, "2DSquareModelSWResults10x10.dat" using 1:5 title "L = 10" with lines, "2DSquareModelSWResults20x20.dat" using 1:5 title "L = 20" with lines, "2DSquareModelSWResults50x50.dat" using 1:5 title "L = 50" with lines;  
set output
