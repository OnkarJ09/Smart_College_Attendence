#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 50
#define MAX_NAME_LENGTH 50

typedef struct {
    char name[MAX_NAME_LENGTH];
    int present;
} Student;

void saveAttendance(Student students[], int numStudents) {
    FILE *file = fopen("attendance.dat", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "Attendance:\n");
    fprintf(file, "Name\t\tPresent\n");
    for (int i = 0; i < numStudents; i++) {
        fprintf(file, "%s\t\t%s\n", students[i].name, students[i].present ? "Yes" : "No");
    }
    fclose(file);
    printf("Attendance saved to file: attendance.dat\n");
}

int main() {
    Student students[MAX_STUDENTS];
    int numStudents;
    int presentCount = 0, absentCount = 0;
    char searchName[MAX_NAME_LENGTH];
    int choice;
    int stu_count;

    printf("Welcome to Attendance Management System\n");

    // Load student data from file if available
    FILE *file = fopen("students.dat", "rb");
    if (file != NULL) {
        fread(&numStudents, sizeof(int), 1, file);
        fread(students, sizeof(Student), numStudents, file);
        fclose(file);
    } else {
        numStudents = 0;
    }

    do {
        printf("\nMenu:\n");
        printf("1. Add Student\n");
        printf("2. Mark Attendance\n");
        printf("3. Search Student\n");
        printf("4. Display Attendance\n");
        printf("5. Save Attendance\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                printf("Enter the number of students you want to add: ");
                scanf("%d", &stu_count);
                for (int i=1; i<=stu_count; i++)
                {
                    if (numStudents < MAX_STUDENTS) {
                        printf("Enter the name of the student: ");
                        scanf("%s", students[numStudents].name);
                        students[numStudents].present = 0;
                        numStudents++;
                    } else {
                        printf("Maximum number of students reached.\n");
                    }
                }
                break;
            case 2:
                printf("Mark attendance:\n");
                for (int i = 0; i < numStudents; i++) {
                    printf("Is %s present? (1 for yes, 0 for no): ", students[i].name);
                    scanf("%d", &students[i].present);
                    if (students[i].present)
                        presentCount++;
                    else
                        absentCount++;
                }
                break;
            case 3:
                printf("Enter the name of the student to search: ");
                scanf("%s", searchName);
                for (int i = 0; i < numStudents; i++) {
                    if (strcmp(searchName, students[i].name) == 0) {
                        printf("Found %s. Present: %s\n", students[i].name, students[i].present ? "Yes" : "No");
                    }
                }
                printf("Student not found.\n");
                break;
            case 4:
                printf("\nAttendance:\n");
                printf("Name\t\tPresent\n\n");
                for (int i = 0; i < numStudents; i++) {
                    printf("%s\t\t%s\n", students[i].name, students[i].present ? "Yes" : "No");
                }
                printf("\nTotal Present: %d\n", presentCount);
                printf("Total Absent: %d\n", absentCount);
                break;
            case 5:
                saveAttendance(students, numStudents);
                break;
            case 6:
                // Save student data to file before exiting
                file = fopen("student.dat", "wb");
                if (file != NULL) {
                    fwrite(&numStudents, sizeof(int), 1, file);
                    fwrite(students, sizeof(Student), numStudents, file);
                    fclose(file);
                } else {
                    printf("Error saving data to file.\n");
                }
                printf("\nSaving Attendence...");
                printf("\n Now,Exiting...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    } while (choice != 6);

    return 0;
}
