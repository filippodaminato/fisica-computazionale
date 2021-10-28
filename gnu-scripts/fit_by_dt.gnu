
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
    linetype 0 linewidth 0 \
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

fit f(x) 'csv/step_eulero.csv' i 0 u (log($1)):(log($4)) via m, q
fit g(x) 'csv/step_eulero.csv' i 1 u (log($1)):(log($4)) via k, z
fit h(x) 'csv/step_eulero.csv' i 2 u (log($1)):(log($4)) via h, c

f(x) = exp(m * log(x) + q )
g(x) = exp(k * log(x) + z )
h(x) = exp(h * log(x) + c )



plot 'csv/step_eulero.csv' i 0 u 1:4 every 15 with linespoints linestyle 1 title 'dt 0.1'
replot f(x) linestyle 2 title 'Fit dt 0.1'

replot 'csv/step_eulero.csv' i 1 u 1:4 every 50 with linespoints linestyle 3 title 'dt 0.05'
replot g(x) linestyle 4 title 'Fit dt 0.05'

replot 'csv/step_eulero.csv' i 2 u 1:4 every 250 with linespoints linestyle 5 title 'dt 0.01'
replot h(x) linestyle 6 title 'Fit dt 0.01'
