#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"

struct Student {
    int id;
    char name[50];
    float marks;
};

// -----------------------------------------
//  DISPLAY MENU
// -----------------------------------------
void showMenu() {
    printf("\n==============================");
    printf("\n   STUDENT MANAGEMENT SYSTEM  ");
    printf("\n==============================");
    printf("\n 1. Add Student");
    printf("\n 2. Display All Students");
    printf("\n 3. Search Student");
    printf("\n 4. Update Student");
    printf("\n 5. Delete Student");
    printf("\n 6. Exit");
    printf("\n==============================");
    printf("\n Enter your choice: ");
}

// -----------------------------------------
//  ADD STUDENT
// -----------------------------------------
void addStudent() {
    FILE *fp = fopen(FILE_NAME, "ab");
    if (fp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    struct Student s;
    printf("\n--- Add Student ---\n");
    printf("Enter ID: ");
    scanf("%d", &s.id);
    printf("Enter Name: ");
    scanf("%s", s.name);
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(struct Student), 1, fp);
    fclose(fp);

    printf("Student added successfully!\n");
}

// -----------------------------------------
//  DISPLAY ALL STUDENTS
// -----------------------------------------
void displayAll() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    struct Student s;
    int count = 0;

    printf("\n%-10s %-20s %-10s\n", "ID", "Name", "Marks");
    printf("------------------------------------------\n");

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("%-10d %-20s %-10.2f\n", s.id, s.name, s.marks);
        count++;
    }
    fclose(fp);

    if (count == 0)
        printf("No student records found!\n");
}

// -----------------------------------------
//  SEARCH STUDENT
// -----------------------------------------
void searchStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    int searchId, found = 0;
    struct Student s;

    printf("\nEnter Student ID to search: ");
    scanf("%d", &searchId);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.id == searchId) {
            printf("\n--- Student Found ---\n");
            printf("ID    : %d\n", s.id);
            printf("Name  : %s\n", s.name);
            printf("Marks : %.2f\n", s.marks);
            found = 1;
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("Student with ID %d not found!\n", searchId);
}

// -----------------------------------------
//  UPDATE STUDENT
// -----------------------------------------
void updateStudent() {
    FILE *fp = fopen(FILE_NAME, "r+b");
    if (fp == NULL) {
        printf("No records found!\n");
        return;
    }

    int searchId, found = 0;
    struct Student s;

    printf("\nEnter Student ID to update: ");
    scanf("%d", &searchId);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.id == searchId) {
            printf("Enter New Name: ");
            scanf("%s", s.name);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);

            fseek(fp, -(long)sizeof(struct Student), SEEK_CUR);
            fwrite(&s, sizeof(struct Student), 1, fp);
            found = 1;
            printf("Student updated successfully!\n");
            break;
        }
    }
    fclose(fp);

    if (!found)
        printf("Student with ID %d not found!\n", searchId);
}

// -----------------------------------------
//  DELETE STUDENT
// -----------------------------------------
void deleteStudent() {
    FILE *fp = fopen(FILE_NAME, "rb");
    FILE *temp = fopen("temp.dat", "wb");

    if (fp == NULL || temp == NULL) {
        printf("Error opening file!\n");
        return;
    }

    int searchId, found = 0;
    struct Student s;

    printf("\nEnter Student ID to delete: ");
    scanf("%d", &searchId);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.id == searchId) {
            found = 1;
        } else {
            fwrite(&s, sizeof(struct Student), 1, temp);
        }
    }

    fclose(fp);
    fclose(temp);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
        printf("Student deleted successfully!\n");
    else
        printf("Student with ID %d not found!\n", searchId);
}

// -----------------------------------------
//  CLEAR FILE ON START
// -----------------------------------------
void clearFileOnStart() {
    FILE *fp = fopen(FILE_NAME, "wb");  // "wb" = purana data erase kar do
    if (fp != NULL)
        fclose(fp);
}

// -----------------------------------------
//  MAIN
// -----------------------------------------
int main() {
    int choice;

    clearFileOnStart();  // Program start hote hi purana data delete!

    do {
        showMenu();
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent();    break;
            case 2: displayAll();    break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("\nExiting... Goodbye!\n"); break;
            default: printf("\nInvalid choice! Try again.\n");
        }

    } while (choice != 6);

    return 0;
}
