#set terminal wxt enhanced
set terminal dumb ansi 140, 40

set key autotitle columnhead

# Set labels and title
set title "Delta Training Error"
set xlabel "Epoch"
set ylabel "Error"

# Set grid
set grid


# Define the point from the data file
#set datafile separator ","  # Set the separator if necessary


# Plot the data
plot 'output_error.txt' using 1:3 with points pt 7 lc rgb 'red' notitle
