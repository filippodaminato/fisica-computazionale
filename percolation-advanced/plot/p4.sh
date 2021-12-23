reset
set term qt 3
set title "Taglia media dei cluster vs densità di occupazione"
set xla "Prbabilità di occupazione"
set yla "Taglia"
set log y 
set grid
set key left top

pl "l20.out" u 2:($7/$8/$3) w lp ps 0.7 pt 7  lw 1.5  ti "L=20"
rep "l40.out" u 2:($7/$8/$3) w lp pt 7 ps 0.7 lw 1.5  ti "L=40"
rep "l80.out" u 2:($7/$8/$3) w lp pt 7 ps 0.7 lw 1.5  ti "L=80"
rep "l160.out" u 2:($7/$8/$3)  w lp pt 7  ps 0.7 lw 1.5 ti "L=160"