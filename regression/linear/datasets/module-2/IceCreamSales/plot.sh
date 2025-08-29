# For Learning purpose only

# Set the datafile separator to comma
set datafile separator ','

# Set line color to red
set style line 1 linecolor rgb "red" linewidth 2

# Set Y-axis range from 50 to 0 and scale from 1 to 10
set yrange [50:0]
set ytics 0,5,50  # Optional: set ticks every 5 units

# Set X-axis range from 1 to 20000 and scale from 1 to 10
set xrange [1:20000]
set xtics 1,2000,20000  # Optional: set ticks every 2000 units

# Plot the data with lines connecting points
plot 'graph.data' using 1:2 with lines linestyle 1
