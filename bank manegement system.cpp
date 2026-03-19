#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "bank.dat"

struct Account {
    int accNumber;
    char name[50];
    float balance;
};

// -----------------------------------------
//  DISPLAY MENU
// -----------------------------------------
void showMenu() {
    printf("\n==============================");
    printf("\n   BANK ACCOUNT MANAGEMENT   ");
    printf("\n==============================");
    printf("\n 1. Create Account");
    printf("\n 2. Deposit Money");
    printf("\n 3. Withdraw Money");
    printf("\n 4. Balance Enquiry");
    printf("\n 5. Exit");
    printf("\n==============================");
    printf("\n Enter your choice: ");
}

// -----------------------------------------
//  CREATE ACCOUNT
// -----------------------------------------
void createAccount() {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Account acc;
    printf("\n--- Create Account ---\n");
    printf("Enter Account Number: ");
    scanf("%d", &acc.accNumber);
    printf("Enter Name: ");
    scanf("%s", acc.name);
    acc.balance = 0.0;

    fwrite(&acc, sizeof(struct Account), 1, fp);
    fclose(fp);

    printf("Account created successfully!\n");
}

// -----------------------------------------
//  DEPOSIT
// -----------------------------------------
void deposit() {
    FILE *fp = fopen(FILE_NAME, "r+b");
    if (fp == NULL) {
        printf("No accounts found!\n");
        return;
    }

    int accNo, found = 0;
    float amount;
    struct Account acc;

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accNumber == accNo) {
            printf("Enter Amount to Deposit: ");
            scanf("%f", &amount);
            acc.balance += amount;

            fseek(fp, -(long)sizeof(struct Account), SEEK_CUR);
            fwrite(&acc, sizeof(struct Account), 1, fp);

            printf("Rs. %.2f Deposited Successfully!\n", amount);
            printf("New Balance: Rs. %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("Account not found!\n");
}

// -----------------------------------------
//  WITHDRAW
// -----------------------------------------
void withdraw() {
    FILE *fp = fopen(FILE_NAME, "r+b");
    if (fp == NULL) {
        printf("No accounts found!\n");
        return;
    }

    int accNo, found = 0;
    float amount;
    struct Account acc;

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accNumber == accNo) {
            printf("Enter Amount to Withdraw: ");
            scanf("%f", &amount);

            if (amount > acc.balance) {
                printf("Insufficient Balance!\n");
            } else {
                acc.balance -= amount;
                fseek(fp, -(long)sizeof(struct Account), SEEK_CUR);
                fwrite(&acc, sizeof(struct Account), 1, fp);
                printf("Rs. %.2f Withdrawn Successfully!\n", amount);
                printf("Remaining Balance: Rs. %.2f\n", acc.balance);
            }
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("Account not found!\n");
}

// -----------------------------------------
//  BALANCE ENQUIRY
// -----------------------------------------
void balanceEnquiry() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No accounts found!\n");
        return;
    }

    int accNo, found = 0;
    struct Account acc;

    printf("\nEnter Account Number: ");
    scanf("%d", &accNo);

    while (fread(&acc, sizeof(struct Account), 1, fp)) {
        if (acc.accNumber == accNo) {
            printf("\n--- Account Details ---\n");
            printf("Account No : %d\n", acc.accNumber);
            printf("Name       : %s\n", acc.name);
            printf("Balance    : Rs. %.2f\n", acc.balance);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("Account not found!\n");
}

// -----------------------------------------
//  MAIN
// -----------------------------------------
int main() {
    int choice;

    do {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: createAccount();  break;
            case 2: deposit();        break;
            case 3: withdraw();       break;
            case 4: balanceEnquiry(); break;
            case 5: printf("\nExiting... Goodbye!\n"); break;
            default: printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 5);

    return 0;
}
