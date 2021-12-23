reset
set term qt 0
set style line 1  linecolor rgb "red"  linewidth 3.000 dashtype 2 pointtype 2 pointsize default
set style function linespoints

set title "Probabilità di percolazione vs densità di occupazione"
set xla "Probabilità di occupazione"
set yla "Probabilità di percolazione"
set grid
set key left top

pl "l20.out" u 2:($5/$3) w lp ps 0.7 pt 7 pi -6  lw 1.5  ti "L=20"
rep "l40.out" u 2:($5/$3) w lp pt 7 ps 0.7 lw 1.5  ti "L=40"
rep "l80.out" u 2:($5/$3) w lp pt 7 ps 0.7 lw 1.5  ti "L=80"
rep "l160.out" u 2:($5/$3) w lp pt 7  ps 0.7 lw 1.5  ti "L=160"