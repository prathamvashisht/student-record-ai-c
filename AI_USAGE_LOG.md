# AI Usage Log

## Purpose

ChatGPT was used as a learning assistant while developing this C project. It was not connected to the C program, and no external AI API was used at runtime.

I reviewed, simplified and tested the suggestions before using them.

## AI assistance record

| AI Tool | Prompt or question asked | How I used and verified the response |
|---|---|---|
| ChatGPT | Suggest four simple academic-advice categories based on a 0 to 10 CGPA for a beginner C project. | I used the categories Excellent Performance, Good Performance, Needs Improvement and Requires Immediate Attention. I selected clear thresholds of 8.50, 7.00 and 5.00 for this project and implemented them using C if-else statements. |
| ChatGPT | Explain how to calculate CGPA from available SGPA values when some semester values are missing. | I used -1 to represent an unavailable SGPA. I checked that unavailable values are ignored and that the program does not divide by zero when no SGPA is available. |
| ChatGPT | Suggest test cases for student records, searching, deletion, sorting and CGPA calculation. | I created a test input containing five students, different academic years, missing SGPA values and four CGPA categories. I checked the expected CGPA values manually and ran the program using the sample input. |
| ChatGPT | Explain beginner-friendly ways to handle student names containing spaces in C. | I used fgets() with a fixed-size character array and removed the newline character. I tested the program with names such as Asha Sharma and Chetan Singh. |
| ChatGPT | Explain how to sort complete student records without mixing fields. | I used a temporary structure variable to swap complete records. I also sort a copy of the array so that the original insertion order is not changed. |

## Verification performed

I checked the following points before using the ideas:

1. CGPA is calculated only from SGPA values that are not -1.
2. A record with SGPA values 9.0 and 9.0 produces a CGPA of 9.00.
3. A record with SGPA values 7.5 and 7.5 produces a CGPA of 7.50.
4. A record with four SGPA values of 6.2 produces a CGPA of 6.20.
5. A record with six SGPA values of 4.0 produces a CGPA of 4.00.
6. The academic advisor produces four different recommendations.
7. Duplicate SAP IDs are rejected.
8. Year, semester and SGPA ranges are checked.
9. Names containing spaces are accepted.
10. The program was compiled using GCC with warnings enabled and was run using the sample input file.

## Personal responsibility

ChatGPT helped me understand concepts, plan logic, prepare test cases and improve documentation. I am responsible for reading and understanding the final C source code, testing it and explaining it during the viva.

