# AI-Assisted Student Record and Result Management System

## Overview

This is a console-based, menu-driven C project for managing student records and results.

The program stores:

- SAP ID
- Roll number
- Student name
- Phone number
- Email ID
- Academic year
- Current semester
- SGPA values for eight semesters

The program calculates CGPA using only the available SGPA values and provides a simple academic recommendation based on CGPA.

No external AI API is used. The academic advisor is implemented directly in C using if-else statements.

## Files

```text
student-record-ai-c/
├── YOUR_SAP_ID.c
├── README.md
├── AI_USAGE_LOG.md
└── tests/
    ├── sample_input.txt
    └── sample_output.txt
```

Before submitting, rename `YOUR_SAP_ID.c` to the actual SAP ID filename, for example:

```text
40001546.c
```

## Requirements implemented

- Console-based application
- Menu-driven operation
- Capacity for 100 student records
- Add a student record
- Search by SAP ID
- Display one student record
- Display all records
- Delete a record
- Reject duplicate SAP IDs
- Validate year, semester and SGPA
- Handle names containing spaces
- Calculate individual CGPA
- Calculate average CGPA for each academic year
- Sort records by increasing SAP ID
- Sort records alphabetically by name
- Academic advisor using C if-else statements
- Four CGPA recommendation categories
- Sample input and sample output

## CGPA calculation

Each available SGPA is added and divided by the number of available SGPA values.

For example:

```text
Semester 1 = 8.0
Semester 2 = 7.0
Semester 3 = unavailable

CGPA = (8.0 + 7.0) / 2 = 7.50
```

The program uses `-1` to represent an unavailable SGPA. Unavailable values are not included in the calculation. If all eight values are unavailable, CGPA is displayed as unavailable instead of dividing by zero.

## Academic advisor categories

These are simple project-level guidelines, not official university grading rules.

| CGPA range | Category | Advice |
|---|---|---|
| 8.50 to 10.00 | Excellent Performance | Maintain the current study pattern and develop advanced skills |
| 7.00 to 8.49 | Good Performance | Continue the routine and improve weaker subjects |
| 5.00 to 6.99 | Needs Improvement | Focus on lower-SGPA subjects and revise regularly |
| Below 5.00 | Requires Immediate Attention | Meet a faculty mentor and create an improvement plan |

## Compile and run

### GCC on Windows

Open Command Prompt or PowerShell in the project folder:

```bash
gcc -std=c11 -Wall -Wextra -pedantic YOUR_SAP_ID.c -o student_system.exe
.\student_system.exe
```

### GCC on Linux or macOS

```bash
gcc -std=c11 -Wall -Wextra -pedantic YOUR_SAP_ID.c -o student_system
./student_system
```

## Input rules

- Enter a unique positive SAP ID.
- Enter a positive roll number.
- Names may contain spaces.
- Enter academic year from 1 to 4.
- Enter current semester from 1 to 8.
- Enter SGPA from 0.00 to 10.00.
- Enter `-1` when an SGPA is not available.
- Enter a phone number containing 7 to 15 digits.
- Enter an email containing `@` and a dot after the `@`.

## Menu options

1. Add student details
2. Search and display a student
3. Display all student records
4. Display average CGPA by year
5. Delete a student record
6. Display records sorted by SAP ID
7. Display records sorted by name
8. Display individual CGPA
9. Academic advisor
0. Exit

## Testing

The `tests/sample_input.txt` file adds five students and tests:

- Individual CGPA calculation
- Average CGPA by year
- Sorting by SAP ID
- Sorting by name
- All four academic advisor categories
- Searching
- Deleting a record

The `tests/sample_output.txt` file contains selected output from the tested run.

## Important limitation

Records are stored in memory while the program is running. When the program exits, the records are lost. Permanent file storage was not required by the assignment, so this version focuses on the required C concepts.

