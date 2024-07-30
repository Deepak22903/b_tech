#include <stdio.h>

int fah_to_cel(){
    float fah=0;
    float cel=0;

    printf("Enter Temperature in Fahrenheit : ");
    scanf("%f",&fah);

    cel = (fah-32) * 5/9;

    printf("%f Fahrenheit = %f Celcius", fah,cel);
}