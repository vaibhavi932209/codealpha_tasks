#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "students.dat"
#define MAX 50

// Structure for storing student details
struct Student {
    int   id;
    char  name[MAX];
    int   age;
    char  course[MAX];
    int   semester;
    float marks;
    char  grade;
    char  status[10];
};

char calculateGrade(float marks) {
    if (marks >= 90)
        return 'A';
    else if (marks >= 75)
        return 'B';
    else if (marks >= 60)
        return 'C';
    else if (marks >= 40)
        return 'D';
    else
        return 'F';
}

void calculateStatus(float marks, char status[]) {
    if (marks >= 40)
        strcpy(status, "PASS");
    else
        strcpy(status, "FAIL");
}

int idExists(int id) {
    FILE *file;
    struct Student student;

    file = fopen(FILE_NAME, "rb");

    if (file == NULL)
        return 0;

    while (fread(&student, sizeof(student), 1, file)) {
        if (student.id == id) {
            fclose(file);
            return 1;
        }
    }

    fclose(file);
    return 0;
}

void addStudent() {

    FILE *file;
    struct Student student;

    printf("\n============================================\n");
    printf("              ADD STUDENT\n");
    printf("============================================\n");

    printf("Enter Student ID: ");
    scanf("%d", &student.id);

    if (idExists(student.id)) {
        printf("\n❌ Student ID already exists!\n");
        return;
    }

    printf("Enter Student Name: ");
    scanf(" %[^\n]", student.name);

    printf("Enter Age: ");
    scanf("%d", &student.age);

    printf("Enter Course: ");
    scanf(" %[^\n]", student.course);

    printf("Enter Semester: ");
    scanf("%d", &student.semester);

    printf("Enter Marks: ");
    scanf("%f", &student.marks);

    student.grade = calculateGrade(student.marks);
    calculateStatus(student.marks, student.status);

    file = fopen(FILE_NAME, "ab");

    if (file == NULL) {
        printf("\n❌ Error opening file!\n");
        return;
    }

    fwrite(&student, sizeof(student), 1, file);

    fclose(file);

    printf("\n✅ Student added successfully!\n");
    printf("Grade  : %c\n", student.grade);
    printf("Status : %s\n", student.status);
}

void displayStudents() {

    FILE *file;
    struct Student student;
    int count = 0;

    printf("\n==============================================================\n");
    printf("                   STUDENT RECORDS\n");
    printf("==============================================================\n");

    file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("\nNo student records found.\n");
        return;
    }

    printf("%-5s %-18s %-5s %-12s %-5s %-8s %-6s %-8s\n",
           "ID", "Name", "Age", "Course",
           "Sem", "Marks", "Grade", "Status");

    printf("--------------------------------------------------------------\n");

    while (fread(&student, sizeof(student), 1, file)) {

        printf("%-5d %-18s %-5d %-12s %-5d %-8.2f %-6c %-8s\n",
               student.id,
               student.name,
               student.age,
               student.course,
               student.semester,
               student.marks,
               student.grade,
               student.status);

        count++;
    }

    fclose(file);

    if (count == 0)
        printf("No records available.\n");
}

void searchByID() {

    FILE *file;
    struct Student student;
    int id;
    int found = 0;

    printf("\n========== SEARCH BY ID ==========\n");

    printf("Enter Student ID: ");
    scanf("%d", &id);

    file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    while (fread(&student, sizeof(student), 1, file)) {

        if (student.id == id) {

            printf("\n✅ Student Found!\n");
            printf("--------------------------------\n");
            printf("ID       : %d\n", student.id);
            printf("Name     : %s\n", student.name);
            printf("Age      : %d\n", student.age);
            printf("Course   : %s\n", student.course);
            printf("Semester : %d\n", student.semester);
            printf("Marks    : %.2f\n", student.marks);
            printf("Grade    : %c\n", student.grade);
            printf("Status   : %s\n", student.status);

            found = 1;
            break;
        }
    }

    fclose(file);

    if (!found)
        printf("\n❌ Student with ID %d not found.\n", id);
}

void searchByName() {

    FILE *file;
    struct Student student;

    char name[MAX];
    int found = 0;

    printf("\n========== SEARCH BY NAME ==========\n");

    printf("Enter Student Name: ");
    scanf(" %[^\n]", name);

    file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    while (fread(&student, sizeof(student), 1, file)) {

        if (strcmp(student.name, name) == 0) {

            printf("\n✅ Student Found!\n");
            printf("--------------------------------\n");
            printf("ID       : %d\n", student.id);
            printf("Name     : %s\n", student.name);
            printf("Age      : %d\n", student.age);
            printf("Course   : %s\n", student.course);
            printf("Semester : %d\n", student.semester);
            printf("Marks    : %.2f\n", student.marks);
            printf("Grade    : %c\n", student.grade);
            printf("Status   : %s\n", student.status);

            found = 1;
        }
    }

    fclose(file);

    if (!found)
        printf("\n❌ Student '%s' not found.\n", name);
}

void searchStudent() {

    int choice;

    printf("\n============================================\n");
    printf("              SEARCH STUDENT\n");
    printf("============================================\n");
    printf("1. Search by ID\n");
    printf("2. Search by Name\n");
    printf("============================================\n");

    printf("Enter your choice: ");
    scanf("%d", &choice);

    switch (choice) {

        case 1:
            searchByID();
            break;

        case 2:
            searchByName();
            break;

        default:
            printf("\n❌ Invalid choice!\n");
    }
}

void updateStudent() {

    FILE *file;
    struct Student student;

    int id;
    int found = 0;

    printf("\n============================================\n");
    printf("             UPDATE STUDENT\n");
    printf("============================================\n");

    printf("Enter Student ID to update: ");
    scanf("%d", &id);

    file = fopen(FILE_NAME, "rb+");

    if (file == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    while (fread(&student, sizeof(student), 1, file)) {

        if (student.id == id) {

            printf("\nStudent found. Enter new details:\n\n");

            printf("Enter New Name: ");
            scanf(" %[^\n]", student.name);

            printf("Enter New Age: ");
            scanf("%d", &student.age);

            printf("Enter New Course: ");
            scanf(" %[^\n]", student.course);

            printf("Enter New Semester: ");
            scanf("%d", &student.semester);

            printf("Enter New Marks: ");
            scanf("%f", &student.marks);

            // Recalculate grade and status
            student.grade = calculateGrade(student.marks);
            calculateStatus(student.marks, student.status);

            // Move file pointer back to current record
            fseek(file, -sizeof(student), SEEK_CUR);

            fwrite(&student, sizeof(student), 1, file);

            found = 1;

            printf("\n✅ Student updated successfully!\n");

            break;
        }
    }

    fclose(file);

    if (!found)
        printf("\n❌ Student with ID %d not found.\n", id);
}

void deleteStudent() {

    FILE *file;
    FILE *tempFile;

    struct Student student;

    int id;
    int found = 0;

    printf("\n============================================\n");
    printf("             DELETE STUDENT\n");
    printf("============================================\n");

    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("\nNo records found.\n");
        return;
    }

    tempFile = fopen("temp.dat", "wb");

    if (tempFile == NULL) {
        printf("\n❌ Error creating temporary file!\n");
        fclose(file);
        return;
    }

    while (fread(&student, sizeof(student), 1, file)) {

        if (student.id == id) {
            found = 1;
        } else {
            fwrite(&student, sizeof(student), 1, tempFile);
        }
    }

    fclose(file);
    fclose(tempFile);

    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);

    if (found)
        printf("\n✅ Student deleted successfully!\n");
    else
        printf("\n❌ Student with ID %d not found.\n", id);
}

void displayMenu() {

    printf("\n============================================\n");
    printf("         SMART STUDENT RECORD HUB\n");
    printf("       Student Management System\n");
    printf("============================================\n");
    printf("  1. Add Student\n");
    printf("  2. Display All Students\n");
    printf("  3. Search Student\n");
    printf("  4. Update Student\n");
    printf("  5. Delete Student\n");
    printf("  6. Exit\n");
    printf("============================================\n");
}

int main() {

    int choice;

    printf("\n============================================\n");
    printf("       WELCOME TO SMART STUDENT HUB\n");
    printf("============================================\n");
    printf("       Student Record Management System\n");
    printf("============================================\n");

    do {

        displayMenu();

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                displayStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                updateStudent();
                break;

            case 5:
                deleteStudent();
                break;

            case 6:
                printf("\n============================================\n");
                printf("   Thank you for using Smart Student Hub!\n");
                printf("============================================\n");
                break;

            default:
                printf("\n❌ Invalid choice! Please select 1-6.\n");
        }

    } while (choice != 6);

    return 0;
}
