set datafile separator ","
set title "X vs Y in regime stazionario c = 9" font ",20"
set xlabel "X" font ",10"
set ylabel "Y" font ",10"
set key left box
set grid

set autoscale xy

set style line 1 \
    linecolor rgb 'red' \
    linetype 0 linewidth 1 \
    pointtype 7 pointsize 0 

set style line 2 \
    linecolor rgb 'blue' \
    linetype -1 linewidth 1.5 \
    pointtype 7 pointsize 0 

set style line 3 \
    linecolor rgb 'green' \
    linetype -1 linewidth 1 \
    pointtype 7 pointsize 0 

set style line 4 \
    linecolor rgb 'coral' \
    linetype -1 linewidth 1 \
    pointtype 7 pointsize 0 

set style line 5 \
    linecolor rgb 'black' \
    linetype -1 linewidth 0 \
    pointtype 7 pointsize 1 

set style line 6 \
    linecolor rgb 'red' \
    linetype -1 linewidth 1 \
    pointtype 7 pointsize 0 

set term png     

set output "c_2.png" 
set title "X vs Y in regime stazionario c = 2" font ",20"
plot 'analyze_by_c.out' i 0 using 2:3 with linespoints linestyle 2 title ''

set output "c_3.png"
set title "X vs Y in regime stazionario c = 3" font ",20"
plot 'analyze_by_c.out' i 1 using 2:3 with linespoints linestyle 2 title ''

set output "c_4.png"
set title "X vs Y in regime stazionario c = 4" font ",20"
plot 'analyze_by_c.out' i 2 using 2:3 with linespoints linestyle 2 title ''

set output "c_5.png"
set title "X vs Y in regime stazionario c = 5" font ",20"
plot 'analyze_by_c.out' i 3 using 2:3 with linespoints linestyle 2 title ''

set output "c_6.png"
set title "X vs Y in regime stazionario c = 6" font ",20"
plot 'analyze_by_c.out' i 4 using 2:3 with linespoints linestyle 2 title ''

set output "c_7.png"
set title "X vs Y in regime stazionario c = 7" font ",20"
plot 'analyze_by_c.out' i 5 using 2:3 with linespoints linestyle 2 title ''

set output "c_8.png"
set title "X vs Y in regime stazionario c = 8" font ",20"
plot 'analyze_by_c.out' i 6 using 2:3 with linespoints linestyle 2 title ''

set output "c_9.png"
set title "X vs Y in regime stazionario c = 9" font ",20"
plot 'analyze_by_c.out' i 7 using 2:3 with linespoints linestyle 2 title ''

set output "c_10.png"
set title "X vs Y in regime stazionario c = 10" font ",20"
plot 'analyze_by_c.out' i 8 using 2:3 with linespoints linestyle 2 title ''
