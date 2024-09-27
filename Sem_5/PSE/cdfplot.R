

# Probability distribution for the sum of two dice
x_values <- 2:12
probabilities <- c(1/36, 2/36, 3/36, 4/36, 5/36, 6/36, 5/36, 4/36, 3/36, 2/36, 1/36)

# Cumulative distribution function
F_x <- cumsum(probabilities)

# Extend F(x) to include values below 2 and above 12
F_x_full <- c(0, F_x, 1)

# Corresponding x values for the extended F(x)
x_full <- c(1, x_values, 13)

# Plotting the cumulative distribution function
plot(x_full, F_x_full, type = "s", col = "blue", 
     xlab = "Sum of Points (X)", 
     ylab = "Cumulative Probability (F(x))", 
     main = "Cumulative Distribution Function for the Sum of Two Dice",
     xlim = c(1, 13), ylim = c(0, 1),
     xaxt = "n")
axis(1, at = 2:12) # Customize x-axis to show values from 2 to 12
grid()

# Adding a horizontal line at y = 0 and y = 1 for clarity
abline(h = 0, col = "lightgray", lty = "dotted")
abline(h = 1, col = "lightgray", lty = "dotted")
