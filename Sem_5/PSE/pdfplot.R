# Probability distribution for the sum of two dice
x_values <- 2:12
probabilities <- c(1/36, 2/36, 3/36, 4/36, 5/36, 6/36, 5/36, 4/36, 3/36, 2/36, 1/36)

# Plotting the probability density function (PDF)
barplot(probabilities, names.arg = x_values, 
        col = "lightblue", border = "black",
        xlab = "Sum of Points (X)", 
        ylab = "Probability (P(X))", 
        main = "Probability Density Function for the Sum of Two Dice",
        ylim = c(0, 0.2))

# Adding grid lines for better readability
grid()
