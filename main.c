#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define FACULTY_MAX_ACADEMIC_YEAR 5

typedef struct {
    char name[50];
    int id;
    char gender;
    int academicYear;
    float gpa;
} Student;

Student students[MAX_STUDENTS];
int numStudents = 0;

void addStudent() {
    if (numStudents >= MAX_STUDENTS) {
        printf("Maximum number of students reached.\n");
        return;
    }

    Student newStudent;

    printf("Enter student name (First Last): ");
    scanf(" %[^\n]", newStudent.name);

    // Validate student name
    if (strchr(newStudent.name, ' ') == NULL) {
        printf("Invalid student name format. Please enter First and Last names.\n");
        return;
    }

    printf("Enter student ID (7-digit code): ");
    scanf("%d", &newStudent.id);

    // Validate student ID
    if (newStudent.id < 1000000 || newStudent.id > 9999999) {
        printf("Invalid student ID format. Please enter a 7-digit code.\n");
        return;
    }

    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == newStudent.id) {
            printf("Student with the same ID already exists. Please enter a unique ID.\n");
            return;
        }
    }

    printf("Enter student gender (M/F): ");
    scanf(" %c", &newStudent.gender);

    // Validate student gender
    if (newStudent.gender != 'M' && newStudent.gender != 'F') {
        printf("Invalid student gender. Please enter 'M' or 'F'.\n");
        return;
    }

    printf("Enter academic year (1-%d): ", FACULTY_MAX_ACADEMIC_YEAR);
    scanf("%d", &newStudent.academicYear);

    // Validate academic year
    if (newStudent.academicYear < 1 || newStudent.academicYear > FACULTY_MAX_ACADEMIC_YEAR) {
        printf("Invalid academic year. Please enter a value between 1 and %d.\n", FACULTY_MAX_ACADEMIC_YEAR);
        return;
    }

    printf("Enter GPA (0-4.0): ");
    scanf("%f", &newStudent.gpa);

    // Validate GPA
    if (newStudent.gpa < 0 || newStudent.gpa > 4.0) {
        printf("Invalid GPA. Please enter a value between 0 and 4.0.\n");
        return;
    }

    students[numStudents++] = newStudent;
    printf("Student added successfully.\n");
}

void removeStudent(int id) {
    int index = -1;

    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("ID Not Found: Student with ID %d not found.\n", id);
        return;
    }

    for (int i = index; i < numStudents - 1; i++) {
        students[i] = students[i + 1];
    }

    numStudents--;
    printf("Operation Successful: Student with ID %d removed successfully.\n", id);
}

void retrieveStudentDataByName(const char *name) {
    int found = 0;

    for (int i = 0; i < numStudents; i++) {
        if (strcmp(students[i].name, name) == 0) {
            printf("Name: %s\n", students[i].name);
            printf("ID: %d\n", students[i].id);
            printf("Gender: %c\n", students[i].gender);
            printf("Academic Year: %d\n", students[i].academicYear);
            printf("GPA: %.2f\n", students[i].gpa);
            found = 1;
        }
    }

    if (!found) {
        printf("Student Not Found: No student with the name '%s' was found.\n", name);
    }
}

void retrieveStudentDataByID(int id) {
    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            printf("Name: %s\n", students[i].name);
            printf("ID: %d\n", students[i].id);
            printf("Gender: %c\n", students[i].gender);
            printf("Academic Year: %d\n", students[i].academicYear);
            printf("GPA: %.2f\n", students[i].gpa);
            return;
        }
    }

    printf("Student Not Found: No student with the ID %d was found.\n", id);
}

void retrieveStudent() {
    int choice;

    printf("Choose retrieval option:\n");
    printf("1. Search by name\n");
    printf("2. Search by ID\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);
    getchar();

    switch (choice) {
        case 1: {
            char name[50];
            printf("Enter student name to retrieve: ");
            scanf(" %[^\n]", name); // Use %[^\n] to capture the entire line as name
            retrieveStudentDataByName(name);
            break;
        }
        case 2: {
            int id;
            printf("Enter student ID to retrieve: ");
            scanf("%d", &id);
            retrieveStudentDataByID(id);
            break;
        }
        default:
            printf("Invalid choice. Please try again.\n");
    }
}


void updateStudentDataByID(int id, int fieldChoice) {
    for (int i = 0; i < numStudents; i++) {
        if (students[i].id == id) {
            switch (fieldChoice) {
                case 1: {
                    int newAcademicYear;
                    printf("Enter new academic year (1-%d): ", FACULTY_MAX_ACADEMIC_YEAR);
                    scanf("%d", &newAcademicYear);

                    // Validate new academic year
                    if (newAcademicYear < 1 || newAcademicYear > FACULTY_MAX_ACADEMIC_YEAR) {
                        printf("Invalid academic year. Please enter a value between 1 and %d.\n", FACULTY_MAX_ACADEMIC_YEAR);
                        return;
                    }

                    students[i].academicYear = newAcademicYear;
                    printf("Academic year updated successfully.\n");
                    break;
                }
                case 2: {
                    float newGPA;
                    printf("Enter new GPA (0-4.0): ");
                    scanf("%f", &newGPA);

                    // Validate new GPA
                    if (newGPA < 0 || newGPA > 4.0) {
                        printf("Invalid GPA. Please enter a value between 0 and 4.0.\n");
                        return;
                    }

                    students[i].gpa = newGPA;
                    printf("GPA updated successfully.\n");
                    break;
                }
                default:
                    printf("Invalid choice. Please try again.\n");
            }
            return;
        }
    }

    printf("Student Not Found: No student with the ID %d was found.\n", id);
}

void updateStudent() {
    int id;
    printf("Enter student ID to update: ");
    scanf("%d", &id);

    int fieldChoice;
    printf("Choose field to update:\n");
    printf("1. Academic Year\n");
    printf("2. GPA\n");
    printf("Enter your choice: ");
    scanf("%d", &fieldChoice);

    updateStudentDataByID(id, fieldChoice);
}

int main() {
    int choice;
    int studentId;

    do {
        printf("=====================================\n");
        printf("      Student Management System      \n");
        printf("=====================================\n");
        printf("1. Add Student\n");
        printf("2. Remove Student\n");
        printf("3. Retrieve Student\n");
        printf("4. Update Student\n");
        printf("5. Exit\n");
        printf("=====================================\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                printf("Enter student ID to remove: ");
                scanf("%d", &studentId);
                removeStudent(studentId);
                break;
            case 3:
                retrieveStudent();
                break;
            case 4:
                updateStudent();
                break;
            case 5:
                printf("Exiting program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
