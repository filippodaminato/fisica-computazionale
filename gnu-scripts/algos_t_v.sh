set datafile separator ","
set title "V(t)" font ",20"
set xlabel "T" font ",10"
set ylabel "X" font ",10"
set key left box


#Plotting Eulero
set style line 1 \
    linecolor rgb 'blue' \
    linetype -1 linewidth 2 \
    pointtype 7 pointsize 0 

plot 'csv/eulero.csv' using 1:3 with linespoints linestyle 1 title 'Cromer'


#Plotting Cromer
set style line 2 \
    linecolor rgb 'red' \
    linetype -1 linewidth 2 \
    pointtype 7 pointsize 0 

replot 'csv/eulerocromer.csv' using 1:3 with linespoints linestyle 2 title 'Eulero Cromer'

#Plotting Leap Frog
set style line 3 \
    linecolor rgb 'green' \
    linetype -1 linewidth 2 \
    pointtype 7 pointsize 0 

replot 'csv/leapfrog.csv' using 1:3 with linespoints linestyle 3 title 'LeapFrog'