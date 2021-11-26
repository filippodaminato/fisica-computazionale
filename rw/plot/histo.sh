reset
  
n=4 #indice per quale t graficare
binsize=2

set title "Istogramma posizioni a t=2^".(n+1)
set xlabel "Posizione"
set ylabel "Entries/Numero di traiettorie"

set xrange [-2**(n+1)-1:2**(n+1)+1]
bin(x,width)=width*(floor(1.*x/width))
P(x,t)=exp(-0.5*x*x/t)/sqrt(2*pi*t)

set boxwidth 0.7 relative
set style fill solid 1.0 

p "histo.out"  u (bin(($1),binsize=2)):2 in n sm un w boxes ls 7 ti "Dati sperimentali" , P(x,2**(n+1)) lw 1.5 ti "Curva attesa"

# save "histo_t".n.".png"

