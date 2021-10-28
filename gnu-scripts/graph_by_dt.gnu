set datafile separator ","

set title "X(t)" font ",20"
set xlabel "T" font ",10"
set ylabel "X" font ",10"
set key left box

set style line 1 \
    linecolor rgb 'blue' \
    linetype -1 linewidth 2 \
    pointtype 7 pointsize 0 

set style line 2 \
    linecolor rgb 'red' \
    linetype -1 linewidth 2 \
    pointtype 7 pointsize 0 

set style line 3 \
    linecolor rgb 'green' \
    linetype -1 linewidth 2 \
    pointtype 7 pointsize 0 


plot 'csv/step_eulero.csv' index 0 using 1:2 with linespoints linestyle 1 title 'dt 0.1',\
     'csv/step_eulero.csv' index 1 using 1:2 with linespoints linestyle 2 title 'dt 0.05',\
     'csv/step_eulero.csv' index 2 using 1:2 with linespoints linestyle 3 title 'dt 0.01'