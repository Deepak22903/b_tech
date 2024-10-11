#!/bin/bash

height=5 

for ((i=0; i<height; i++)); do
    for ((j=0; j<5; j++)); do
        echo -n " "
    done
    for ((j=height-i; j>1; j--)); do
        echo -n " "
    done

    # Print stars
    for ((k=0; k<(2*i+1); k++)); do
        echo -n "*"
    done
    echo
done


height=10  

for ((i=0; i<height-6; i++)); do
    for ((j=0; j<i; j++)); do
        echo -n " "
    done

    for ((k=0; k<(2*(height-i)-1); k++)); do
        echo -n "*"
    done
    echo
done

a=0
for((i=0; i < 6; i++))
do
  
    for((j=0; j < 4; j++))
    do
        echo -n " "
    done

    # Print stars
    for((k=6-a; k > 0; k--))
    do
        echo -n "*"
    done

    for((l=0; l < a; l++))
    do
        echo -n " "
    done
     for((l=0; l < a; l++))
    do
        echo -n " "
    done
   
  
 for((k=6-a; k > 0; k--))
    do
        echo -n "*"
    done
    echo

    a=$((a+1))
done

