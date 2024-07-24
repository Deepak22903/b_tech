#include <stdio.h>

int add(int a[3][3], int b[3][3]){
    int c[3][3];

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            c[i][j]= a[i][j] + b[i][j];
        }
    }

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }

    return 0;

}

int trans(int a[3][3]){

    int c[3][3];

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            c[i][j]= a[j][i];
        }
    }

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }

    return 0;

}

int mul(int a[3][3], int b[3][3]){
    int c[3][3];

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            c[i][j]=0;
            for( int k=0; k<3; k++){
                c[i][j]= c[i][j] + a[i][k] * b[k][j];
            }
        }
    }

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("%d ",c[i][j]);
        }
        printf("\n");
    }

    return 0;
}

int main(){
    int a[3][3];
    int b[3][3];

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("Enter value for a[%d][%d] : ", i+1,j+1);
            scanf("%d",&a[i][j]);
        }
    }

    for(int i=0; i<3; i++){
        for(int j=0; j<3; j++){
            printf("Enter value for b[%d][%d] : ", i+1,j+1);
            scanf("%d",&b[i][j]);
        }
    }

    printf("\n\nAddition of Matrix a and b = \n\n");
    add(a,b);
    printf("\n\nTranspose of Matrix a =\n\n");
    trans(a);
    printf("\n\nMultiplication of Matrix a and b = \n\n");
    mul(a,b);



}