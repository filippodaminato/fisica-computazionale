set datafile separator ","
set title "X vs dT^2" font ",20"
set xlabel "dt" font ",10"
set ylabel "X" font ",10"
set key right box

#Plotting Eulero
set style line 1 \
    linecolor rgb 'blue' \
    linetype -1 linewidth 2 \
    pointtype 7 pointsize 0 

plot 'error_dt2.out' using ($1)**2:2 with p pt 7 linecolor rgb 'red' title 'X'

f(x) = m * x + q  

fit f(x) 'error_dt2.out' u ($1)**2:($2) via m, q

replot f(x) linestyle 1 title 'Fit X vs dT^2'


# Final set of parameters            Asymptotic Standard Error
# =======================            ==========================
# m               = -6.44786         +/- 0.03189      (0.4945%)
# q               = -0.611784        +/- 0.0001242    (0.02031%)

# correlation matrix of the fit parameters:
#                 m      q      
# m               1.000 
# q              -0.463  1.000 