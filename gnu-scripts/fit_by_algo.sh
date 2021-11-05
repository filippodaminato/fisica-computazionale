set datafile separator ","

set title "{/Symbol D}E/E_0 vs {/Symbol D}t "
set key top left
set xlabel " {/Symbol D}t "
set ylabel " {/Symbol D}E/E_0 "
set log xy

set grid
set key bottom center box height 1.4


set style line 1 \
    linecolor rgb 'red' \
    linetype 0 linewidth 0 \
    pointtype 7 pointsize 1 

set style line 2 \
    linecolor rgb 'blue' \
    linetype -1 linewidth 2 \
    pointtype 7 pointsize 0 

set style line 3 \
    linecolor rgb 'green' \
    linetype -1 linewidth 0 \
    pointtype 7 pointsize 1 

set style line 4 \
    linecolor rgb 'coral' \
    linetype -1 linewidth 2 \
    pointtype 7 pointsize 0 

set style line 5 \
    linecolor rgb 'black' \
    linetype 0 linewidth 0 \
    pointtype 7 pointsize 1 

set style line 6 \
    linecolor rgb 'red' \
    linetype -1 linewidth 2 \
    pointtype 7 pointsize 0 


f(x) = m * x + q       
g(x) = k * x + z  
h(x) = h * x + c  
z(x) = t * x + b  

fit f(x) 'csv/RECAP_eulero.csv' u (log($1)):(log($5)) via m, q
fit g(x) 'csv/RECAP_eulerocromer.csv' u (log($1)):(log($5)) via k, z
fit h(x) 'csv/RECAP_leapfrog.csv' u (log($1)):(log($5)) via h, c
fit z(x) 'csv/RECAP_VerletVelocity.csv' u (log($1)):(log($5)) via t, b

f(x) = exp(m * log(x) + q )
g(x) = exp(k * log(x) + z )
h(x) = exp(h * log(x) + c )
z(x) = exp(t * log(x) + b )

plot 'csv/RECAP_eulero.csv' u 1:5 with linespoints linestyle 1 title 'Eulero' 
replot f(x) linestyle 1 title 'Fit Eulero'

replot 'csv/RECAP_eulerocromer.csv' u 1:5  with linespoints linestyle 2 title 'eulerocromer'
replot g(x) linestyle 2 title 'Fit eulerocromer'

replot 'csv/RECAP_leapfrog.csv' u 1:5 with linespoints linestyle 3 title 'LeapFrog'
replot h(x) linestyle 3 title 'Fit LeapFrog'

replot 'csv/RECAP_VerletVelocity.csv' u 1:5 with linespoints linestyle 4 title 'VerletVelocity'
replot h(x) linestyle 4 title 'Fit VerletVelocity'



