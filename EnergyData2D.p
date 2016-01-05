#Gnuplot script file for plotting ising model data from the file "results2D.dat"
#this file is called Data.p
set term pdfcairo
set output "IsingModel2DEnergyPlot.pdf"
set size 1, 0.5
set autoscale
unset log
unset label
set xtic auto
set ytic auto
set title "Energy of a 25 2D spin lattice vs step"
set ylabel "Energy"
set xlabel "step" 
plot "results.dat" using 1:2 title 'J = 0.01 in units of kT^{-1}' with linespoint; 
set output
