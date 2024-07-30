#include <stdio.h>

int main() {
    int n;
    printf("Enter a num: ");
    scanf("%d", &n);

    if (n < 2) {
        printf("enter 2 or more numbers\n");
        return 0;
    }

    int numbers[n];

    printf("Enter %d nums :\n", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &numbers[i]);
    }

    int max1, max2;

    if (numbers[0] > numbers[1]) {
        max1 = numbers[0];
        max2 = numbers[1];
    } else {
        max1 = numbers[1];
        max2 = numbers[0];
    }

    for (int i = 2; i < n; i++) {
        if (numbers[i] > max1) {
            max2 = max1;
            max1 = numbers[i];
        } else if (numbers[i] > max2 && numbers[i] != max1) {
            max2 = numbers[i];
        }
    }

    double average = (double)(max1 + max2) / 2.0;

    printf("The largest two numbers are: %d and %d\n", max1, max2);
    printf("The average of the largest two numbers is: %.2lf\n", average);

    return 0;
}
