#include <stdio.h>

#define MAX 10

void inputMatrix(int matrix[MAX][MAX], int rows, int cols) {
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            printf("Enter element [%d][%d]: ", i + 1, j + 1);
            scanf("%d", &matrix[i][j]);
        }
    }
}

void displayMatrix(int matrix[MAX][MAX], int rows, int cols) {
    int i, j;

    for (i = 0; i < rows; i++) {
        printf("| ");

        for (j = 0; j < cols; j++) {
            printf("%4d ", matrix[i][j]);
        }

        printf("|\n");
    }
}

void addMatrix(int A[MAX][MAX], int B[MAX][MAX],
               int result[MAX][MAX], int rows, int cols) {
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            result[i][j] = A[i][j] + B[i][j];
        }
    }
}

void multiplyMatrix(int A[MAX][MAX], int B[MAX][MAX],
                    int result[MAX][MAX],
                    int r1, int c1, int c2) {
    int i, j, k;

    for (i = 0; i < r1; i++) {
        for (j = 0; j < c2; j++) {

            result[i][j] = 0;

            for (k = 0; k < c1; k++) {
                result[i][j] += A[i][k] * B[k][j];
            }
        }
    }
}

void transposeMatrix(int matrix[MAX][MAX],
                     int transpose[MAX][MAX],
                     int rows, int cols) {
    int i, j;

    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            transpose[j][i] = matrix[i][j];
        }
    }
}

void displayMenu() {
    printf("\n============================================\n");
    printf("           MATRIX OPERATIONS SYSTEM\n");
    printf("============================================\n");
    printf("  1. Matrix Addition\n");
    printf("  2. Matrix Multiplication\n");
    printf("  3. Transpose of Matrix A\n");
    printf("  4. Transpose of Matrix B\n");
    printf("  5. Display Matrices\n");
    printf("  6. Exit\n");
    printf("============================================\n");
}

int main() {

    int A[MAX][MAX], B[MAX][MAX];
    int result[MAX][MAX];
    int transpose[MAX][MAX];

    int r1, c1, r2, c2;
    int choice;

    printf("============================================\n");
    printf("       WELCOME TO MATRIX OPERATIONS\n");
    printf("============================================\n");

    do {
        printf("\nEnter rows and columns for Matrix A (1-10): ");
        scanf("%d %d", &r1, &c1);

        if (r1 < 1 || r1 > MAX || c1 < 1 || c1 > MAX) {
            printf("Invalid dimensions! Please enter values from 1 to 10.\n");
        }

    } while (r1 < 1 || r1 > MAX || c1 < 1 || c1 > MAX);

    printf("\nEnter elements of Matrix A:\n");
    inputMatrix(A, r1, c1);

    do {
        printf("\nEnter rows and columns for Matrix B (1-10): ");
        scanf("%d %d", &r2, &c2);

        if (r2 < 1 || r2 > MAX || c2 < 1 || c2 > MAX) {
            printf("Invalid dimensions! Please enter values from 1 to 10.\n");
        }

    } while (r2 < 1 || r2 > MAX || c2 < 1 || c2 > MAX);

    printf("\nEnter elements of Matrix B:\n");
    inputMatrix(B, r2, c2);

    do {

        displayMenu();

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:

                if (r1 == r2 && c1 == c2) {

                    addMatrix(A, B, result, r1, c1);

                    printf("\n------------- MATRIX ADDITION -------------\n");

                    printf("\nMatrix A:\n");
                    displayMatrix(A, r1, c1);

                    printf("\nMatrix B:\n");
                    displayMatrix(B, r2, c2);

                    printf("\nA + B =\n");
                    displayMatrix(result, r1, c1);

                } else {

                    printf("\nERROR: Matrix addition is not possible.\n");
                    printf("Both matrices must have the same dimensions.\n");
                }

                break;

            case 2:

                if (c1 == r2) {

                    multiplyMatrix(A, B, result, r1, c1, c2);

                    printf("\n---------- MATRIX MULTIPLICATION ----------\n");

                    printf("\nMatrix A:\n");
                    displayMatrix(A, r1, c1);

                    printf("\nMatrix B:\n");
                    displayMatrix(B, r2, c2);

                    printf("\nA x B =\n");
                    displayMatrix(result, r1, c2);

                } else {

                    printf("\nERROR: Matrix multiplication is not possible.\n");
                    printf("Columns of Matrix A must equal rows of Matrix B.\n");
                }

                break;

            case 3:

                transposeMatrix(A, transpose, r1, c1);

                printf("\n---------- TRANSPOSE OF MATRIX A ----------\n");

                printf("\nOriginal Matrix A:\n");
                displayMatrix(A, r1, c1);

                printf("\nTranspose of Matrix A:\n");
                displayMatrix(transpose, c1, r1);

                break;

            case 4:

                transposeMatrix(B, transpose, r2, c2);

                printf("\n---------- TRANSPOSE OF MATRIX B ----------\n");

                printf("\nOriginal Matrix B:\n");
                displayMatrix(B, r2, c2);

                printf("\nTranspose of Matrix B:\n");
                displayMatrix(transpose, c2, r2);

                break;

            case 5:

                printf("\n--------------- MATRICES ----------------\n");

                printf("\nMatrix A:\n");
                displayMatrix(A, r1, c1);

                printf("\nMatrix B:\n");
                displayMatrix(B, r2, c2);

                break;

            case 6:

                printf("\n============================================\n");
                printf("     Thank you for using Matrix System!\n");
                printf("============================================\n");

                break;


            default:

                printf("\nInvalid choice!\n");
                printf("Please select an option between 1 and 6.\n");
        }

    } while (choice != 6);

    return 0;
}
