reset
set term qt 0
set title "Probabilità di percolazione vs densità di occupazione"
set xla "Prbabilità di occupazione"
set yla "Probabilità di percolazione"
set grid
set key left top

pl "l20.out" u 2:($5/$3) w lp ps 0.7 pt 7  lw 1.5  ti "L=20"
rep "l40.out" u 2:($5/$3) w lp pt 7 ps 0.7 lw 1.5  ti "L=40"
rep "l80.out" u 2:($5/$3) w lp pt 7 ps 0.7 lw 1.5  ti "L=80"
rep "l160.out" u 2:($5/$3) w lp pt 7  ps 0.7 lw 1.5  ti "L=160"


reset
set term qt 1
set title "Taglia media cluster più grande vs densità di occupazione"
set xla "Prbabilità di occupazione"
set yla "Taglia"
set grid
set key left top

pl "l20.out" u 2:($6/$3) w lp ps 0.7 pt 7 lw 1.5   ti "L=20"
rep "l40.out" u 2:($6/$3) w lp pt 7 ps 0.7  lw 1.5  ti "L=40"
rep "l80.out" u 2:($6/$3) w lp pt 7 ps 0.7 lw 1.5 ti "L=80"
rep "l160.out" u 2:($6/$3) w lp pt 7  ps 0.7 lw 1.5 ti "L=160"


reset
set term qt 2
set title "Taglia media normalizzata del cluster più grande vs densità di occupazione"
set xla "Prbabilità di occupazione"
set yla "Taglia/L^2"
set grid
set key left top

pl "l20.out" u 2:(($6/$3)/($1*$1))  w p ps 0.7 pt 7 lw 1.5   ti "L=20"
rep "l40.out" u 2:(($6/$3)/($1*$1))  w p pt 7 ps 0.7 lw 1.5  ti "L=40"
rep "l80.out" u 2:(($6/$3)/($1*$1)) w p pt 7 ps 0.7 lw 1.5  ti "L=80"
rep "l160.out" u 2:(($6/$3)/($1*$1))  w p pt 7  ps 0.7 lw 1.5  ti "L=160"


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


reset
set term qt 4
set title "Taglia media dei cluster escluso quello percolante vs densità di occupazione"
set xla "Prbabilità di occupazione"
set yla "Taglia"
set grid
set key left top

pl "l20.out" u 2:((($4-$6)/$3*($4-$6)/$3)/$8) w lp ps 0.7 pt 7 lw 1.5   ti "L=20"
rep "l40.out" u 2:((($4-$6)/$3*($4-$6)/$3)/$8) w lp pt 7 ps 0.7 lw 1.5 ti "L=40"
rep "l80.out" u 2:((($4-$6)/$3*($4-$6)/$3)/$8)  w lp pt 7 ps 0.7 lw 1.5 ti "L=80"
rep "l160.out" u 2:((($4-$6)/$3*($4-$6)/$3)/$8) w lp pt 7  ps 0.7 lw 1.5 ti "L=160"


reset
set term qt 5
set title "Taglia media normalizzata dei cluster escluso quello percolante vs densità di occupazione"
set xla "Prbabilità di occupazione"
set yla "Taglia"
set grid
set key left top

pl "l20.out" u 2:(((($4-$6)/$3*($4-$6)/$3)/$8)/($1*$1)) w lp ps 0.7 pt 7  lw 1.5  ti "L=20"
rep "l40.out" u 2:(((($4-$6)/$3*($4-$6)/$3)/$8)/($1*$1))  w lp pt 7 ps 0.7 lw 1.5 ti "L=40"
rep "l80.out" u 2:(((($4-$6)/$3*($4-$6)/$3)/$8)/($1*$1))   w lp pt 7 ps 0.7 lw 1.5 ti "L=80"
rep "l160.out" u 2:(((($4-$6)/$3*($4-$6)/$3)/$8)/($1*$1))  w lp pt 7  ps 0.7 lw 1.5  ti "L=160"