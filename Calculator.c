#include <stdio.h>

int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int multiply(int a, int b)
{
    return a * b;
}

float divide(int a, int b)
{
    if(b==0)
    {
        printf("Division by zero not allowed\n");
        return 0;
    }
    return (float)a/b;
}

int main()
{
    int num1, num2;
    int choice;

    while(1)
    {
        printf("\n========== SIMPLE CALCULATOR ==========\n");
        printf("1. Addition\n");
        printf("2. Subtraction\n");
        printf("3. Multiplication\n");
        printf("4. Division\n");
        printf("5. Exit\n");
        printf("=======================================\n");

        printf("Enter your choice: ");
        scanf("%d",&choice);

        if(choice==5)
        {
            printf("Exiting program...\n");
            break;
        }

        printf("Enter first number: ");
        scanf("%d",&num1);

        printf("Enter second number: ");
        scanf("%d",&num2);

        if(choice==1)
        {
            printf("Result = %d\n", add(num1,num2));
        }
        else if(choice==2)
        {
            printf("Result = %d\n", subtract(num1,num2));
        }
        else if(choice==3)
        {
            printf("Result = %d\n", multiply(num1,num2));
        }
        else if(choice==4)
        {
            printf("Result = %.2f\n", divide(num1,num2));
        }
        else
        {
            printf("Invalid choice\n");
        }
    }

    return 0;
}
