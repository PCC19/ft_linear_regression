#set terminal wxt enhanced size 1200, 800
set terminal dumb ansi 210, 60

# Set ranges
#set xrange [-2:2]
#set yrange [-2:2]

# Set labels and title
set title "Error surface"
set xlabel "t0"
set ylabel "t1"

plot "grid.txt" with image notitle, \
     "train.txt" using 1:2 with points pt 2 lc rgb 'gray' notitle

