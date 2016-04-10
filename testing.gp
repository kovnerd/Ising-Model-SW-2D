#Gnuplot script file for plotting ising model data from the file "results2D.dat"
#this file is called Data.p
set term pdfcairo
set output "testing.pdf"
set size 1, 1
set autoscale
unset log
unset label
set xtic auto
set ytic auto
set title "Magnetic Susceptibility vs Temperature for Different Lattice sizes"
set ylabel "Magnetic Susceptibility"
set xlabel "Temperature" 
plot "2DSquareModelResults10x10Testing.dat" using 1:4 title "L = 5" with lines;  
set output
