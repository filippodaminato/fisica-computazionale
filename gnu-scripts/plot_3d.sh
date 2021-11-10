set datafile separator ","

# set title "X(t)" font ",20"
# set xlabel "T" font ",10"
# set ylabel "X" font ",10"
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


splot "output.out" u 2:3:4 every 100 with linespoints linestyle 1