#include <stdio.h>

#define SIZE 3

// -----------------------------------------
//  MATRIX INPUT
// -----------------------------------------
void inputMatrix(int mat[SIZE][SIZE], char name) {
    printf("\nEnter Matrix %c:\n", name);
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            printf("  [%d][%d]: ", i+1, j+1);
            scanf("%d", &mat[i][j]);
        }
}

// -----------------------------------------
//  DISPLAY MATRIX
// -----------------------------------------
void displayMatrix(int mat[SIZE][SIZE]) {
    for (int i = 0; i < SIZE; i++) {
        printf("  ");
        for (int j = 0; j < SIZE; j++)
            printf("%5d ", mat[i][j]);
        printf("\n");
    }
}

// -----------------------------------------
//  MATRIX ADDITION
// -----------------------------------------
void addMatrix(int a[SIZE][SIZE], int b[SIZE][SIZE]) {
    int result[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            result[i][j] = a[i][j] + b[i][j];

    printf("\n--- Matrix Addition Result ---\n");
    displayMatrix(result);
}

// -----------------------------------------
//  MATRIX MULTIPLICATION
// -----------------------------------------
void multiplyMatrix(int a[SIZE][SIZE], int b[SIZE][SIZE]) {
    int result[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++) {
            result[i][j] = 0;
            for (int k = 0; k < SIZE; k++)
                result[i][j] += a[i][k] * b[k][j];
        }

    printf("\n--- Matrix Multiplication Result ---\n");
    displayMatrix(result);
}

// -----------------------------------------
//  MATRIX TRANSPOSE
// -----------------------------------------
void transposeMatrix(int a[SIZE][SIZE]) {
    int result[SIZE][SIZE];
    for (int i = 0; i < SIZE; i++)
        for (int j = 0; j < SIZE; j++)
            result[j][i] = a[i][j];

    printf("\n--- Transpose of Matrix A ---\n");
    displayMatrix(result);
}

// -----------------------------------------
//  MAIN
// -----------------------------------------
int main() {
    int a[SIZE][SIZE], b[SIZE][SIZE];
    int choice;

    inputMatrix(a, 'A');
    inputMatrix(b, 'B');

    do {
        printf("\n==============================");
        printf("\n      MATRIX OPERATIONS       ");
        printf("\n==============================");
        printf("\n 1. Matrix Addition");
        printf("\n 2. Matrix Multiplication");
        printf("\n 3. Transpose of Matrix A");
        printf("\n 4. Exit");
        printf("\n==============================");
        printf("\n Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addMatrix(a, b);      break;
            case 2: multiplyMatrix(a, b); break;
            case 3: transposeMatrix(a);   break;
            case 4: printf("\nExiting... Goodbye!\n"); break;
            default: printf("\nInvalid choice!\n");
        }

    } while (choice != 4);

    return 0;
}
