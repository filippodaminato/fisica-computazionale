set datafile separator ","
set title "X(t)" font ",20"
set xlabel "T" font ",10"
set ylabel "X" font ",10"
set key left box

set style line 1 \
    linecolor rgb 'blue' \
    linetype -1 linewidth 0.25 \
    pointtype 7 pointsize 0 

set grid

set autoscale xy

set term png     

set output "t_100.png" 
set title "X(t) con t_{max} = 100" font ",20"
plot '100sec.out' using 1:2 with linespoints linestyle 1 title 'X'

set output "t_200.png" 
set title "X(t) con t_{max} = 200" font ",20"
plot '200sec.out' using 1:2 with linespoints linestyle 1 title 'X'

set output "t_300.png" 
set title "X(t) con t_{max} = 300" font ",20"
plot '300sec.out' using 1:2 with linespoints linestyle 1 title 'X'

set output "t_400.png" 
set title "X(t) con t_{max} = 400" font ",20"
plot '400sec.out' using 1:2 with linespoints linestyle 1 title 'X'
