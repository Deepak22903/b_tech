#include <stdio.h>

int main() {
  double num1, num2, result;
  char operator;

  printf("Enter first number: ");
  scanf("%lf", &num1);

  printf("Enter an operator (+, -, *, /, %%): ");
  scanf(" %c", &operator); // space before %c to consume leftover newline

  printf("Enter second number: ");
  scanf("%lf", &num2);

  switch (operator) {
  case '+':
    result = num1 + num2;
    printf("Result: %.2lf\n", result);
    break;
  case '-':
    result = num1 - num2;
    printf("Result: %.2lf\n", result);
    break;
  case '*':
    result = num1 * num2;
    printf("Result: %.2lf\n", result);
    break;
  case '/':
    if (num2 == 0) {
      printf("Error: Division by zero.\n");
    } else {
      result = num1 / num2;
      printf("Result: %.2lf\n", result);
    }
    break;
  case '%':
    // Modulus only works on integers
    if ((int)num2 == 0) {
      printf("Error: Division by zero.\n");
    } else {
      int mod_result = (int)num1 % (int)num2;
      printf("Result: %d\n", mod_result);
    }
    break;
  default:
    printf("Invalid operator.\n");
  }

  return 0;
}
