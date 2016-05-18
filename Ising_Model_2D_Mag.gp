#Gnuplot script file for plotting ising model data from the file "results2D.dat"
#this file is called Data.p
set term pdfcairo
set output "Ising_2D_Square_SW_Mag.pdf"
set size 1, 1
set autoscale
unset log
unset label
set xtic auto
set ytic auto
set title "Magnetization vs Temperature for Different Lattice sizes"
set ylabel "Magnetization"
set xlabel "Temperature" 
plot "2DSquareModelSWResults5x5.dat" using 1:3 title "L = 5" with lines, "2DSquareModelSWResults10x10.dat" using 1:3 title "L = 10" with lines, "2DSquareModelSWResults20x20.dat" using 1:3 title "L = 20" with lines, "2DSquareModelSWResults50x50.dat" using 1:3 title "L = 50" with lines;  
set output
