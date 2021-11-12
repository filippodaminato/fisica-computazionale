set datafile separator ","
set title "(t)" font ",20"
set xlabel "T" font ",10"
set ylabel "X" font ",10"
set key left box

set style line 1 \
    linecolor rgb 'blue' \
    linetype -1 linewidth 1 \
    pointtype 7 pointsize 0 

set grid

set autoscale xy

# set term png     

set output "tx_periodico.png" 
set title "X(t)" font ",20"
plot '400sec.out' using 1:2 with linespoints linestyle 1 title 'X'


# set output "ty_periodico.png" 
# set title "Y(t)" font ",20"
# plot '400sec.out' using 1:3 with linespoints linestyle 1 title 'Y'
