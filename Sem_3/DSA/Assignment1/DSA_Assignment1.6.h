#include <stdio.h>
const float PI=3.14;

int circle(){

    float r;
    float area;
    float circum;

    printf("Enter radius : ");
    scanf("%f",&r);

    area = PI * r * r;

    circum = 2 * PI * r;

    printf("Area of Circle = %f\n", area);
    printf("Cicumference of Circle %f= ", circum);

    return 0;

}