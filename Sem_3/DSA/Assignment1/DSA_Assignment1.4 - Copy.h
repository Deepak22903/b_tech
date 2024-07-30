#include <stdio.h>

float da(){
    float sal;
    float da=0;

    printf("Enter your Salary : ");
    scanf("%f",&sal);

    if(sal >= 10000 && sal <= 20000){
        da = (sal*10)/100;
    } else if (sal > 20000 && sal <=50000)
    {
        da = (sal*15)/100;
    } else if (sal > 50000 && sal <= 100000){
        da = (sal*20)/100;
    } else if (sal > 100000){
    }

    printf("Your DA is %f", da);

    return da;
    


}