set size ratio 0.8

set title "CA = 110" font "Arial, 18"
set xlabel "x^*" font "Arial, 20"
set ylabel "z^*" font "Arial, 20"

# plot 'bo2-a110-0.1.dat' u 2:(-$3) w l t "BO=2", \
#        'bo3.5-a110-0.1.dat' u 2:(-$3) w l t "BO=3", \
#            'bo5-a110-0.1.dat' u 2:(-$3) w l t "BO=5"

plot 'bo0.436-a107-0.1.dat' u 2:(-$3) t "BO=0.436, CA=107"

