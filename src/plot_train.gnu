#set terminal wxt enhanced
set terminal dumb ansi 140, 40

set key autotitle columnhead

# Set labels and title
set title "Normalized Regression"
set xlabel "Normalized Mileage"
set ylabel "Normalized Price"

# Set grid
set grid


# Define the point from the data file
#set datafile separator ","  # Set the separator if necessary


# Plot the data
plot [0:1] 'output_data.txt' using 1:2 with points pt 7 lc rgb 'blue' title 'Scatter Plot', \
     [0:1] 'output_data.txt' using 1:3 with lines lw 2 lc rgb 'red' title 'Regression"
