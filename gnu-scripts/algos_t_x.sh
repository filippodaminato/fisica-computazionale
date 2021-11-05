set datafile separator ","
set title "X(t)" font ",20"
set xlabel "T" font ",10"
set ylabel "X" font ",10"
set key left box

#Plotting Eulero
set style line 1 \
    linecolor rgb 'blue' \
    linetype -1 linewidth 2 \
    pointtype 7 pointsize 0 

plot 'csv/eulero.csv' i 4 using 1:2 with linespoints linestyle 1 title 'Cromer'

#Plotting Cromer
set style line 2 \
    linecolor rgb 'red' \
    linetype -1 linewidth 2 \
    pointtype 7 pointsize 0 

replot 'csv/eulerocromer.csv' i 4 using 1:2 with linespoints linestyle 2 title 'Eulero Cromer'

#Plotting Leap Frog
set style line 3 \
    linecolor rgb 'green' \
    linetype -1 linewidth 2 \
    pointtype 7 pointsize 0 

replot 'csv/leapfrog.csv' i 4 using 1:2 with linespoints linestyle 3 title 'LeapFrog'

#Plotting Leap Frog
set style line 4 \
    linecolor rgb 'orange' \
    linetype -1 linewidth 2 \
    pointtype 7 pointsize 0 

replot 'csv/VerletPosition.csv' i 4 using 1:2 with linespoints linestyle 4 title 'VerletPosition'

#Plotting Leap Frog
set style line 5 \
    linecolor rgb 'black' \
    linetype -1 linewidth 2 \
    pointtype 7 pointsize 0 

replot 'csv/VerletVelocity.csv' i 4 using 1:2 with linespoints linestyle 5 title 'VerletVelocity'