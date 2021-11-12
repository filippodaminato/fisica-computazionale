set datafile separator ","
set title "X(t)" font ",20"
set xlabel "X" font ",10"
set ylabel "Y" font ",10"
set key left box

#Plotting Eulero
set style line 1 \
    linecolor rgb 'blue' \
    linetype -1 linewidth 2 \
    pointtype 7 pointsize 0 

plot 'output.out' using 2:3 with linespoints linestyle 1 title 'X'
