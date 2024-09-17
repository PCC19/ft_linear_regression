#set terminal wxt enhanced
set terminal dumb ansi 140, 40

set key autotitle columnhead

# Set labels and title
set title "Price Model"
set xlabel "Mileage"
set ylabel "Price"

# Set grid
set grid


# Define the point from the data file
set datafile separator ","  # Set the separator if necessary

# Set arrow styles for dashed lines
set style line 1 lt 2 lw 1 lc rgb 'black' dashtype 2  # Dashed line style

x = ARG1
y = ARG2
# Draw vertical dashed line at x = x coordinate from the file
set arrow from x, 0 to x,y nohead ls 1 lc rgb "green"

# Draw horizontal dashed line at y = y coordinate from the file
set arrow from 0, y to x,y  nohead ls 1 lc rgb "green"

# Plot the data
#plot 'data.csv' using 1:2 with points pt 7 lc rgb 'blue' title 'Scatter Plot'
plot 'data.csv' using 1:2 with points pt 7 lc rgb 'blue' title 'Scatter Plot', \
     'line_data.txt' using 1:2 with lines lw 2 lc rgb 'red' title 'Regression', \
     'point_data.txt' using 1:2 with points pt 5 lc rgb 'green' title 'Estimate' 
