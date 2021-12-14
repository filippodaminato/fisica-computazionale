reset
set term qt 0
set title "Esempi di Random Walk "
set xlabel "t"
set ylabel "x"
unset key
pl for[i=0:3] "tj.out" in i  w l lw 1.5






