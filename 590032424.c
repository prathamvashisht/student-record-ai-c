
/*
Name: Pratham vashisht
SAP ID: 590032424
Batch No.: 20
Course: B.Tech CSE
Project: AI-Assisted Student Record and Result Management System
*/
#include <ctype.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STUDENTS 100
#define TOTAL_SEMESTERS 8
#define UNAVAILABLE_SGPA -1.0f

/*
 * This structure stores all information related to one student.
 * SGPA values are stored in sgpa[0] to sgpa[7] for Semesters 1 to 8.
 * A value of -1.0 means that the SGPA is not available yet.
 */
struct Student {
    int sapId;
    int rollNumber;
    char name[100];
    char phone[20];
    char email[100];
    int year;
    int semester;
    float sgpa[TOTAL_SEMESTERS];
};

/* The array can store 100 students, which is more than the required five. */
struct Student students[MAX_STUDENTS];
int studentCount = 0;

/* Reads a complete line and removes the newline character. */
void readLine(const char *prompt, char *buffer, size_t size) {
    size_t newlinePosition;
    int ch;

    printf("%s", prompt);

    if (fgets(buffer, size, stdin) == NULL) {
        printf("\nInput ended. The program will now exit.\n");
        exit(0);
    }

    newlinePosition = strcspn(buffer, "\n");

    if (buffer[newlinePosition] == '\n') {
        buffer[newlinePosition] = '\0';
        if (newlinePosition > 0 && buffer[newlinePosition - 1] == '\r') {
            buffer[newlinePosition - 1] = '\0';
        }
    } else {
        /* Remove extra characters when the input is longer than the buffer. */
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* Keep reading until the complete input line is discarded. */
        }
    }
}

/* Returns 1 when text contains only spaces or is empty. */
int isBlank(const char *text) {
    int i;

    for (i = 0; text[i] != '\0'; i++) {
        if (!isspace((unsigned char) text[i])) {
            return 0;
        }
    }

    return 1;
}

/* Reads text that cannot be empty. Names may contain spaces. */
void readRequiredText(const char *prompt, char *buffer, size_t size) {
    do {
        readLine(prompt, buffer, size);

        if (isBlank(buffer)) {
            printf("This field cannot be empty. Please try again.\n");
        }
    } while (isBlank(buffer));
}

/* Reads an integer and rejects extra non-space text. */
int readInt(const char *prompt) {
    char line[100];
    char extra;
    int value;

    while (1) {
        readLine(prompt, line, sizeof(line));

        if (sscanf(line, "%d %c", &value, &extra) == 1) {
            return value;
        }

        printf("Invalid integer. Please enter a whole number.\n");
    }
}

/* Reads an integer within an inclusive range. */
int readIntInRange(const char *prompt, int minimum, int maximum) {
    int value;

    do {
        value = readInt(prompt);

        if (value < minimum || value > maximum) {
            printf("Please enter a value from %d to %d.\n", minimum, maximum);
        }
    } while (value < minimum || value > maximum);

    return value;
}

/* Reads a floating-point number and rejects extra non-space text. */
float readFloat(const char *prompt) {
    char line[100];
    char extra;
    float value;

    while (1) {
        readLine(prompt, line, sizeof(line));

        if (sscanf(line, "%f %c", &value, &extra) == 1) {
            return value;
        }

        printf("Invalid decimal value. Please try again.\n");
    }
}

/* Checks whether a phone number contains a reasonable number of digits. */
int validPhone(const char *phone) {
    int digitCount = 0;
    int i;

    for (i = 0; phone[i] != '\0'; i++) {
        if (isdigit((unsigned char) phone[i])) {
            digitCount++;
        } else if (phone[i] != '+' && phone[i] != '-' && phone[i] != ' '
                   && phone[i] != '(' && phone[i] != ')') {
            return 0;
        }
    }

    return digitCount >= 7 && digitCount <= 15;
}

void readPhone(char *phone, size_t size) {
    do {
        readRequiredText("Enter phone number: ", phone, size);

        if (!validPhone(phone)) {
            printf("Invalid phone number. Use 7 to 15 digits.\n");
        }
    } while (!validPhone(phone));
}

/* Performs a simple email check suitable for this beginner project. */
int validEmail(const char *email) {
    int atPosition = -1;
    int i;

    for (i = 0; email[i] != '\0'; i++) {
        if (isspace((unsigned char) email[i])) {
            return 0;
        }

        if (email[i] == '@') {
            if (atPosition != -1) {
                return 0;
            }
            atPosition = i;
        }
    }

    if (atPosition <= 0) {
        return 0;
    }

    for (i = atPosition + 1; email[i] != '\0'; i++) {
        if (email[i] == '.' && email[i + 1] != '\0' && email[i + 1] != '.') {
            return 1;
        }
    }

    return 0;
}

void readEmail(char *email, size_t size) {
    do {
        readRequiredText("Enter email ID: ", email, size);

        if (!validEmail(email)) {
            printf("Invalid email. Example: student@example.com\n");
        }
    } while (!validEmail(email));
}

/* Returns 1 when a SAP ID is already used by another record. */
int sapIdExists(int sapId) {
    int i;

    for (i = 0; i < studentCount; i++) {
        if (students[i].sapId == sapId) {
            return 1;
        }
    }

    return 0;
}

/* Reads one SGPA value; -1 means that the value is unavailable. */
float readSemesterSGPA(int semesterNumber) {
    char prompt[100];
    float value;

    snprintf(prompt, sizeof(prompt),
             "Enter SGPA for Semester %d (-1 if unavailable): ", semesterNumber);

    while (1) {
        value = readFloat(prompt);

        if (value == UNAVAILABLE_SGPA || (value >= 0.0f && value <= 10.0f)) {
            return value;
        }

        printf("SGPA must be from 0.00 to 10.00, or -1 if unavailable.\n");
    }
}

/* Calculates CGPA using only available SGPA values. */
float calculateCGPA(struct Student student) {
    float total = 0.0f;
    int availableCount = 0;
    int i;

    for (i = 0; i < TOTAL_SEMESTERS; i++) {
        if (student.sgpa[i] >= 0.0f) {
            total += student.sgpa[i];
            availableCount++;
        }
    }

    if (availableCount == 0) {
        return UNAVAILABLE_SGPA;
    }

    return total / availableCount;
}

/* Displays the academic recommendation for a CGPA. */
void displayRecommendation(float cgpa) {
    if (cgpa < 0.0f) {
        printf("Recommendation: CGPA is unavailable. Enter at least one SGPA.\n");
    } else if (cgpa >= 8.5f) {
        printf("Category: Excellent Performance\n");
        printf("Recommendation: Maintain your current study pattern and continue developing advanced skills.\n");
    } else if (cgpa >= 7.0f) {
        printf("Category: Good Performance\n");
        printf("Recommendation: Continue your study routine and work toward improving your weaker subjects.\n");
    } else if (cgpa >= 5.0f) {
        printf("Category: Needs Improvement\n");
        printf("Recommendation: Focus more on subjects with lower SGPA and follow a regular revision plan.\n");
    } else {
        printf("Category: Requires Immediate Attention\n");
        printf("Recommendation: Meet your faculty mentor, identify learning gaps and create an immediate improvement plan.\n");
    }
}

/* Displays every field of one student record. */
void displayStudent(struct Student student) {
    float cgpa = calculateCGPA(student);
    int i;

    printf("\n----------------------------------------\n");
    printf("SAP ID: %d\n", student.sapId);
    printf("Roll Number: %d\n", student.rollNumber);
    printf("Name: %s\n", student.name);
    printf("Phone Number: %s\n", student.phone);
    printf("Email ID: %s\n", student.email);
    printf("Academic Year: %d\n", student.year);
    printf("Current Semester: %d\n", student.semester);

    printf("SGPA Values:\n");
    for (i = 0; i < TOTAL_SEMESTERS; i++) {
        if (student.sgpa[i] < 0.0f) {
            printf("  Semester %d: Not available\n", i + 1);
        } else {
            printf("  Semester %d: %.2f\n", i + 1, student.sgpa[i]);
        }
    }

    if (cgpa < 0.0f) {
        printf("CGPA: Not available\n");
    } else {
        printf("CGPA: %.2f\n", cgpa);
    }
    printf("----------------------------------------\n");
}

/* Adds a new student after validating the entered information. */
void addStudent(void) {
    struct Student newStudent;
    int i;

    if (studentCount == MAX_STUDENTS) {
        printf("The student list is full.\n");
        return;
    }

    do {
        newStudent.sapId = readIntInRange("Enter SAP ID: ", 1, INT_MAX);

        if (sapIdExists(newStudent.sapId)) {
            printf("This SAP ID already exists. Enter a different SAP ID.\n");
        }
    } while (sapIdExists(newStudent.sapId));

    newStudent.rollNumber = readIntInRange("Enter roll number: ", 1, INT_MAX);
    readRequiredText("Enter student name: ", newStudent.name, sizeof(newStudent.name));
    readPhone(newStudent.phone, sizeof(newStudent.phone));
    readEmail(newStudent.email, sizeof(newStudent.email));
    newStudent.year = readIntInRange("Enter academic year (1-4): ", 1, 4);
    newStudent.semester = readIntInRange("Enter current semester (1-8): ", 1, 8);

    for (i = 0; i < TOTAL_SEMESTERS; i++) {
        newStudent.sgpa[i] = readSemesterSGPA(i + 1);
    }

    students[studentCount] = newStudent;
    studentCount++;

    printf("Student record added successfully.\n");
}

/* Returns the array index of a SAP ID, or -1 when it is not found. */
int findStudentIndex(int sapId) {
    int i;

    for (i = 0; i < studentCount; i++) {
        if (students[i].sapId == sapId) {
            return i;
        }
    }

    return -1;
}

void searchStudent(void) {
    int sapId;
    int index;

    if (studentCount == 0) {
        printf("No student records are available.\n");
        return;
    }

    sapId = readIntInRange("Enter SAP ID to search: ", 1, INT_MAX);
    index = findStudentIndex(sapId);

    if (index == -1) {
        printf("No student was found with SAP ID %d.\n", sapId);
    } else {
        displayStudent(students[index]);
    }
}

void displayAllStudents(void) {
    int i;

    if (studentCount == 0) {
        printf("No student records are available.\n");
        return;
    }

    printf("\nALL STUDENT RECORDS\n");
    for (i = 0; i < studentCount; i++) {
        displayStudent(students[i]);
    }
}

void displayAverageCGPAByYear(void) {
    int year;

    if (studentCount == 0) {
        printf("No student records are available.\n");
        return;
    }

    printf("\nAVERAGE CGPA BY ACADEMIC YEAR\n");

    for (year = 1; year <= 4; year++) {
        float total = 0.0f;
        int cgpaCount = 0;
        int i;

        for (i = 0; i < studentCount; i++) {
            if (students[i].year == year) {
                float cgpa = calculateCGPA(students[i]);

                if (cgpa >= 0.0f) {
                    total += cgpa;
                    cgpaCount++;
                }
            }
        }

        if (cgpaCount == 0) {
            printf("Year %d: No available CGPA data\n", year);
        } else {
            printf("Year %d: %.2f\n", year, total / cgpaCount);
        }
    }
}

void deleteStudent(void) {
    int sapId;
    int index;
    int i;

    if (studentCount == 0) {
        printf("No student records are available.\n");
        return;
    }

    sapId = readIntInRange("Enter SAP ID to delete: ", 1, INT_MAX);
    index = findStudentIndex(sapId);

    if (index == -1) {
        printf("No student was found with SAP ID %d.\n", sapId);
        return;
    }

    /* Shift later records one position to the left. */
    for (i = index; i < studentCount - 1; i++) {
        students[i] = students[i + 1];
    }

    studentCount--;
    printf("Student record deleted successfully.\n");
}

/* Makes a copy so sorting does not change the original insertion order. */
void copyStudents(struct Student sortedStudents[]) {
    int i;

    for (i = 0; i < studentCount; i++) {
        sortedStudents[i] = students[i];
    }
}

void displaySortedBySAP(void) {
    struct Student sortedStudents[MAX_STUDENTS];
    struct Student temporary;
    int i;
    int j;

    if (studentCount == 0) {
        printf("No student records are available.\n");
        return;
    }

    copyStudents(sortedStudents);

    for (i = 0; i < studentCount - 1; i++) {
        for (j = 0; j < studentCount - i - 1; j++) {
            if (sortedStudents[j].sapId > sortedStudents[j + 1].sapId) {
                temporary = sortedStudents[j];
                sortedStudents[j] = sortedStudents[j + 1];
                sortedStudents[j + 1] = temporary;
            }
        }
    }

    printf("\nSTUDENTS SORTED BY INCREASING SAP ID\n");
    for (i = 0; i < studentCount; i++) {
        displayStudent(sortedStudents[i]);
    }
}

void displaySortedByName(void) {
    struct Student sortedStudents[MAX_STUDENTS];
    struct Student temporary;
    int i;
    int j;

    if (studentCount == 0) {
        printf("No student records are available.\n");
        return;
    }

    copyStudents(sortedStudents);

    for (i = 0; i < studentCount - 1; i++) {
        for (j = 0; j < studentCount - i - 1; j++) {
            if (strcmp(sortedStudents[j].name, sortedStudents[j + 1].name) > 0) {
                temporary = sortedStudents[j];
                sortedStudents[j] = sortedStudents[j + 1];
                sortedStudents[j + 1] = temporary;
            }
        }
    }

    printf("\nSTUDENTS SORTED IN ALPHABETICAL ORDER OF NAME\n");
    for (i = 0; i < studentCount; i++) {
        displayStudent(sortedStudents[i]);
    }
}

void displayIndividualCGPA(void) {
    int sapId;
    int index;
    float cgpa;

    if (studentCount == 0) {
        printf("No student records are available.\n");
        return;
    }

    sapId = readIntInRange("Enter SAP ID: ", 1, INT_MAX);
    index = findStudentIndex(sapId);

    if (index == -1) {
        printf("No student was found with SAP ID %d.\n", sapId);
        return;
    }

    cgpa = calculateCGPA(students[index]);
    if (cgpa < 0.0f) {
        printf("CGPA is not available because no SGPA has been entered.\n");
    } else {
        printf("CGPA of %s: %.2f\n", students[index].name, cgpa);
    }
}

void academicAdvisor(void) {
    int sapId;
    int index;
    float cgpa;

    if (studentCount == 0) {
        printf("No student records are available.\n");
        return;
    }

    sapId = readIntInRange("Enter SAP ID for academic advice: ", 1, INT_MAX);
    index = findStudentIndex(sapId);

    if (index == -1) {
        printf("No student was found with SAP ID %d.\n", sapId);
        return;
    }

    cgpa = calculateCGPA(students[index]);
    printf("\nACADEMIC ADVISOR\n");
    printf("Student: %s\n", students[index].name);

    if (cgpa < 0.0f) {
        printf("CGPA: Not available\n");
    } else {
        printf("CGPA: %.2f\n", cgpa);
    }

    displayRecommendation(cgpa);
}

void displayMenu(void) {
    printf("\n========================================\n");
    printf("AI-ASSISTED STUDENT RECORD SYSTEM\n");
    printf("========================================\n");
    printf("1. Add student details\n");
    printf("2. Search and display a student\n");
    printf("3. Display all student records\n");
    printf("4. Display average CGPA by year\n");
    printf("5. Delete a student record\n");
    printf("6. Display records sorted by SAP ID\n");
    printf("7. Display records sorted by name\n");
    printf("8. Display individual CGPA\n");
    printf("9. Academic advisor\n");
    printf("0. Exit\n");
    printf("========================================\n");
}

int main(void) {
    int choice;

    printf("Welcome to the AI-Assisted Student Record and Result Management System\n");

    do {
        displayMenu();
        choice = readInt("Enter your choice: ");

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                searchStudent();
                break;
            case 3:
                displayAllStudents();
                break;
            case 4:
                displayAverageCGPAByYear();
                break;
            case 5:
                deleteStudent();
                break;
            case 6:
                displaySortedBySAP();
                break;
            case 7:
                displaySortedByName();
                break;
            case 8:
                displayIndividualCGPA();
                break;
            case 9:
                academicAdvisor();
                break;
            case 0:
                printf("Thank you for using the system.\n");
                break;
            default:
                printf("Invalid choice. Please select a menu option.\n");
        }
    } while (choice != 0);

    return 0;
}

