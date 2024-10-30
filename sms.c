#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define FILE_NAME "FILE_gogo"

// Define the Student structure
struct Student {
    int id;
    char name[50];
    int age;
    char grade[10];
};

// Function prototypes
void addStudent();
void viewStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
void menu();

int main() {
    menu();
    return 0;
}

void menu() {
    int choice;
    do {
        printf("\n--- Student Management System ---\n");
        printf("1. Add Student\n");
        printf("2. View Students\n");
        printf("3. Search Student\n");
        printf("4. Update Student\n");
        printf("5. Delete Student\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: printf("Exiting...\n"); exit(0);
            default: printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 6);
}

void addStudent() {
    struct Student student;
    FILE *file = fopen(FILE_NAME, "ab");

    if (file == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Student ID: ");
    scanf("%d", &student.id);
    printf("Enter Name: ");
    scanf(" %[^\n]", student.name); // To allow spaces in the name
    printf("Enter Age: ");
    scanf("%d", &student.age);
    printf("Enter Grade: ");
    scanf("%s", student.grade);

    fwrite(&student, sizeof(struct Student), 1, file);
    fclose(file);

    printf("Student added successfully!\n");
}

void viewStudents() {
    struct Student student;
    FILE *file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("\n--- Student Records ---\n");
    printf("ID\tName\t\tAge\tGrade\n");
    printf("-------------------------------------\n");
    while (fread(&student, sizeof(struct Student), 1, file)) {
        printf("%d\t%s\t\t%d\t%s\n", student.id, student.name, student.age, student.grade);
    }
    fclose(file);
}

void searchStudent() {
    struct Student student;
    int id, found = 0;
    FILE *file = fopen(FILE_NAME, "rb");

    if (file == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Student ID to search: ");
    scanf("%d", &id);

    while (fread(&student, sizeof(struct Student), 1, file)) {
        if (student.id == id) {
            printf("\nStudent found:\n");
            printf("ID: %d\nName: %s\nAge: %d\nGrade: %s\n", student.id, student.name, student.age, student.grade);
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }
}

void updateStudent() {
    struct Student student;
    int id, found = 0;
    FILE *file = fopen(FILE_NAME, "rb+");

    if (file == NULL) {
        printf("No records found!\n");
        return;
    }

    printf("Enter Student ID to update: ");
    scanf("%d", &id);

    while (fread(&student, sizeof(struct Student), 1, file)) {
        if (student.id == id) {
            printf("\nUpdating Student with ID %d\n", id);
            printf("Enter New Name: ");
            scanf(" %[^\n]", student.name);
            printf("Enter New Age: ");
            scanf("%d", &student.age);
            printf("Enter New Grade: ");
            scanf("%s", student.grade);

            fseek(file, -sizeof(struct Student), SEEK_CUR);
            fwrite(&student, sizeof(struct Student), 1, file);
            printf("Student updated successfully!\n");
            found = 1;
            break;
        }
    }
    fclose(file);

    if (!found) {
        printf("Student with ID %d not found.\n", id);
    }
}

void deleteStudent() {
    struct Student student;
    int id, found = 0;
    FILE *file = fopen(FILE_NAME, "rb");
    FILE *tempFile = fopen("temp.dat", "wb");

    if (file == NULL || tempFile == NULL) {
        printf("Error opening file!\n");
        return;
    }

    printf("Enter Student ID to delete: ");
    scanf("%d", &id);

    while (fread(&student, sizeof(struct Student), 1, file)) {
        if (student.id == id) {
            found = 1;
        } else {
            fwrite(&student, sizeof(struct Student), 1, tempFile);
        }
    }
    fclose(file);
    fclose(tempFile);
    remove(FILE_NAME);
    rename("temp.dat", FILE_NAME);
    if (found) {
        printf("Student deleted successfully!\n");
    } else {
        printf("Student with ID %d not found.\n", id);
    }
}

