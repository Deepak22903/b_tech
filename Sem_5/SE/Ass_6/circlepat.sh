#!/bin/bash
# Script to print a circular star pattern using loops

radius=10  # Define the radius of the circle
center=$radius  # Center of the circle

# Outer loop for rows
for ((i=0; i<=2*radius; i++))
do
    # Inner loop for columns
    for ((j=0; j<=2*radius; j++))
    do
        # Calculate distance from the center (approximation)
        dx=$((i - center))
        dy=$((j - center))
        distance_squared=$((dx*dx + dy*dy))

        # Check if the point is inside the circle boundary
        if ((distance_squared <= radius*radius))
        then
            echo -n "* "
        else
            echo -n "  "
        fi
    done
    echo
done
