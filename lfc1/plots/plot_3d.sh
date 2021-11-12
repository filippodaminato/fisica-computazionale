set datafile separator ","

set title "F(x,y,z) per t_{max} = 100 sec" font ",20"
set xlabel "X" font ",10"
set ylabel "Y" font ",10"
set zlabel "Z" font ",10"
# set key left box

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

set grid

set autoscale xy

splot "1_1.txt" u 2:3:4 every 10 with linespoints linestyle 1 title 'a=b=0.1, c=1 e x0=y0=z0=0'