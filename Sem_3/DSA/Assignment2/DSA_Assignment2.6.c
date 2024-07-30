#include <stdio.h>

void numbers(){
    int number=1;
    for(int i=1; i<=4; i++){
        for(int j=1; j<=i; j++){
        printf("%d ",number);
        number++;
        
    }
    printf("\n");
    }

}

void star_pyramid(int rows){
   int i, space, k = 0;
   printf("\n");
   for (i = 1; i <= rows; ++i, k = 0) {
      for (space = 1; space <= rows - i; ++space) {
         printf("  ");
      }
      while (k != 2 * i - 1) {
         printf("* ");
         ++k;
      }
      printf("\n");
   }
   

}

void pascal_triangle(){
    int rows, coef = 1, space, i, j;
    printf("\n");
   printf("Enter the number of rows: ");
   scanf("%d", &rows);
   for (i = 0; i < rows; i++) {
      for (space = 1; space <= rows - i; space++)
         printf("  ");
      for (j = 0; j <= i; j++) {
         if (j == 0 || i == 0)
            coef = 1;
         else
            coef = coef * (i - j + 1) / j;
         printf("%4d", coef);
      }
      printf("\n");
   }
}

void double_pyramid(){
     int i, j, rows, k; 
     printf("\n"); 
    printf (" Enter a number to define the rows: \n");  
    scanf ("%d", &rows); // take a number  
    printf("\n");  
    for ( i = 1; i <= rows; i++)  
    {  
          
        for ( j = 1; j <= rows; j++)  
        {  
            if( j <= i)  
            printf ("%d", j);   
            else  
            printf(" ");  
        }  
        for (j = rows; j >= 1; j--)  
        {  
            if(j <= i)  
            printf ("%d", j);  
            else  
            printf(" ");  
        }  
        printf ("\n");  
    }  
}

int main(){
    int rows;
        printf("\n\n*************************************\n\n");

    numbers();
    printf("\n\n*************************************\n\n");
    printf("Enter the number of rows: ");
    scanf("%d",&rows);
    star_pyramid(rows);
        printf("\n\n*************************************\n\n");
        pascal_triangle();
                printf("\n\n*************************************\n\n");
    double_pyramid();
                printf("\n\n*************************************\n\n");


    


}