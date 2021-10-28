set title "{/Symbol D}E/E_0 vs {/Symbol D}t "
set key top left
set xlabel " {/Symbol D}t "
set ylabel " {/Symbol D}E/E_0 "
set log xy

set style line 1 lt rgb "red" lw 1 pt 7
set style line 2 lt rgb "orange" lw 1 pt 7
set style line 3 lt rgb "yellow" lw 1 pt 7
set style line 4 lt rgb "green" lw 1 pt 7
set style line 5 lt rgb "cyan" lw 1 pt 7
set style line 6 lt rgb "blue" lw 1 pt 7
set style line 7 lt rgb "violet" lw 1 pt 7


f(x)=a*x+b
g(x)=c*x+d
h(x)=e*x+i
l(x)=m*x+n
s(x)=t*x+u
v(x)=z*x+y

fit [:-4] f(x) "dt_dE_Xmax.out" u (log($1)):(log($2)) via a,b
fit [:-3] g(x) "dt_dE_Xmax.out" u (log($1)):(log($3)) via c,d
fit [:-4] h(x) "dt_dE_Xmax.out" u (log($1)):(log($4)) via e,i
fit l(x) "dt_dE_Xmax.out" u (log($1)):(log($5)) via m,n
fit s(x) "dt_dE_Xmax.out" u (log($1)):(log($6)) via t,u
fit v(x) "dt_dE_Xmax.out" u (log($1)):(log($7)) via z,y


o(x)=exp(a*log(x)+b)
p(x)=exp(c*log(x)+d)
q(x)=exp(e*log(x)+i)
r(x)=exp(m*log(x)+n)
k(x)=exp(t*log(x)+u)
j(x)=exp(z*log(x)+y)

pl "dt_dE_Xmax.out" u 1:2 w points  ti "Dati Eulero" pt 7 ,o(x) ti "Curva di best fit Eulero" ls 1,"dt_dE_Xmax.out" u 1:3 w points pt 7 ti "Dati Eulero-Cromer",p(x) ti "Best fit Eulero-Cromer" ls 2,"dt_dE_Xmax.out" u 1:4 w points pt 7 ti "Dati Punto centrale",q(x) ti "Best fit punto centrale" ls 3,"dt_dE_Xmax.out" u 1:5 w points pt 7 ti "Dati Leap frog" ,r(x) ti "Best fit leap frog" ls 4,"dt_dE_Xmax.out" u 1:6 w points pt 7 ti "Dati Velocity Verlet",k(x) ti "Best fit Velocity Verlet" ls 5,"dt_dE_Xmax.out" u 1:7 w points pt 7 ti "Dati Position Verlet",j(x) ti "Best fit Position Verlet" ls 6

pl "dt_dE_Xmax.out" u 1:2 w points  ti "Dati Eulero" ls 1 ,o(x) ti "Curva di best fit Eulero" ls 1,"dt_dE_Xmax.out" u 1:3 w points ls 2 ti "Dati Eulero-Cromer",p(x) ti "Best fit Eulero-Cromer" ls 2,"dt_dE_Xmax.out" u 1:4 w points ls 3 ti "Dati Punto centrale",q(x) ti "Best fit punto centrale" ls 3,"dt_dE_Xmax.out" u 1:5 w points ls 4 ti "Dati Leap frog" ,r(x) ti "Best fit leap frog" ls 4,"dt_dE_Xmax.out" u 1:6 w points ls 5 ti "Dati Velocity Verlet",k(x) ti "Best fit Velocity Verlet" ls 5,"dt_dE_Xmax.out" u 1:7 w points ls 6 ti "Dati Position Verlet",j(x) ti "Best fit Position Verlet" ls 6

 


