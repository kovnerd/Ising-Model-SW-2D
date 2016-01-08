#Gnuplot script file for plotting ising model data from the file "results2D.dat"
#this file is called Data.p
set term pdfcairo
set output "Ising_2D_Square_MagSus.pdf"
set size 1, 1
set autoscale
unset log
unset label
set xtic auto
set ytic auto
set title "Magnetic Susceptibility of a 25 2D spin lattice vs step"
set ylabel "Magnetic Susceptibility"
set xlabel "step" 
plot "results2D.dat" using 1:4 notitle with linespoint; 
set output
