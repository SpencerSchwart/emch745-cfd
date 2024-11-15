# set terminal pngcairo size 8,6 font "Arial, 20"
set output "refine.png"
set size ratio 0.8

set log x
set xtics 0, 10, 1000 logscale

set title "Bo=2 | CA=110" font "Arial, 18"
set xlabel "ds" font "Arial, 20"
set ylabel "H^*" font "Arial, 20"

plot 'h_vs_ds.dat' u 1:2 w l t 'Bo=2 | CA=110'


