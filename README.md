# Library Management System

This project implements a simplified library management system to curate and manage a collection of books. It allows users to add, search, remove, load, and output library entries, as well as display checkout statistics and invalid entries.

## Overview

Each library entry consists of:

- **Book Title**: Must not contain commas.
- **ISBN Number**: A 13-digit, hyphen-separated number.
- **Checkout Status**: An integer where:
  - 0 = In Library
  - 1 = Checked Out
  - 2 = On Loan
  - 3 = Unknown State
  - Any other value indicates an invalid state.

## Functionalities

The system supports the following commands (case-insensitive):

- **A**: Add Item To Library
- **C**: Clear the Library Of All Entries
- **D**: Display Library Entries
- **I**: List Invalid Library Entries
- **L**: Load Library From File
- **O**: Output Library To File
- **P**: Print Out Checkout Stats
- **R**: Remove A Library Entry
- **S**: Search For A Library Entry
- **X**: Exit Program

## Project Milestones

1. **Milestone 0**: Starter Files & Strategies
2. **Milestone 1**: Data Structures & Exiting
3. **Milestone 2**: Add Entry to the Library
4. **Milestone 3**: Display the Library
5. **Milestone 4**: Clear the Library
6. **Milestone 5**: Load Library From File
7. **Milestone 6**: Output Library To A File
8. **Milestone 7**: Print Out Checkout Stats
9. **Milestone 8**: Search the Library
10. **Milestone 9**: Remove an Entry
11. **Milestone 10**: Print Out Invalid Entries

## Submission Guidelines

- **Files to Submit**:
  - `library.cpp` on zyBooks for functionality testing.
  - `library.cpp` on Gradescope for manual grading.
- **Restrictions**:
  - Use only provided libraries (output streams, file streams, vectors, and strings).
  - **Do not use**: structs, pointers, dynamic memory allocation, or any containers other than vectors.
  - **Do not change** any provided code lines or menu text to ensure autograder compatibility.

## Policies

- **Collaboration Policy**:  
  This project must be completed individually. Assistance is only allowed from the CS 251 teaching staff.
- **Late Policy**:  
  A 24-hour grace period is allowed. Continued reliance on this grace period may indicate falling behind the course pace.

## Execution

Run the program and use the menu options to interact with the library system. Input redirection can be used for testing, and the program must produce the exact output specified in the assignment description.

Happy coding!
