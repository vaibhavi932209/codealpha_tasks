#include <stdio.h>
#include <math.h>

void showMenu() {
    printf("\n====================================\n");
    printf("          SMART CALCULATOR\n");
    printf("====================================\n");
    printf("1. Addition\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    printf("4. Division\n");
    printf("5. Modulus\n");
    printf("6. Power\n");
    printf("7. Exit\n");
    printf("====================================\n");
}

int main() {
    float num1, num2, result;
    int choice;
    char again;

    do {
        showMenu();

        printf("Enter your choice: ");
        scanf("%d", &choice);

        if (choice == 7) {
            printf("\nThank you for using Smart Calculator!\n");
            break;
        }

        printf("Enter first number: ");
        scanf("%f", &num1);

        printf("Enter second number: ");
        scanf("%f", &num2);

        switch (choice) {

            case 1:
                result = num1 + num2;
                printf("\nResult: %.2f + %.2f = %.2f\n",
                       num1, num2, result);
                break;

            case 2:
                result = num1 - num2;
                printf("\nResult: %.2f - %.2f = %.2f\n",
                       num1, num2, result);
                break;

            case 3:
                result = num1 * num2;
                printf("\nResult: %.2f * %.2f = %.2f\n",
                       num1, num2, result);
                break;

            case 4:
                if (num2 == 0) {
                    printf("\nError: Cannot divide by zero!\n");
                } else {
                    result = num1 / num2;
                    printf("\nResult: %.2f / %.2f = %.2f\n",
                           num1, num2, result);
                }
                break;

            case 5:
                if ((int)num2 == 0) {
                    printf("\nError: Cannot perform modulus by zero!\n");
                } else {
                    printf("\nResult: %d %% %d = %d\n",
                           (int)num1, (int)num2,
                           (int)num1 % (int)num2);
                }
                break;

            case 6:
                result = pow(num1, num2);
                printf("\nResult: %.2f ^ %.2f = %.2f\n",
                       num1, num2, result);
                break;

            default:
                printf("\nInvalid choice! Please select 1-7.\n");
        }

        printf("\nDo you want to perform another calculation? (Y/N): ");
        scanf(" %c", &again);

    } while (again == 'Y' || again == 'y');

    printf("\n====================================\n");
    printf("       Thank You! Goodbye!\n");
    printf("====================================\n");

    return 0;
}
