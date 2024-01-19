# Data Structures - Student Information System Project

This C++ project focuses on creating a robust Student Information System (SIS) for a University, leveraging data structures for efficient management of student enrollment and course information. The SIS empowers registered students to log in, review their course schedule, add/drop courses, and swap courses seamlessly. The system also facilitates new students in signing up for accounts, while maintaining comprehensive lists of enrolled students and university courses.

## Project Overview

- **Student Management:**
  - Students are uniquely identified by Student ID, First Name, Last Name, Email Address, and a doubly linked list managing their enrolled courses.

- **Course Management:**
  - Courses are uniquely identified by Course ID, Course Name, Instructor Name, Time Schedule, Course Capacity, and a singly linked list tracking enrolled students.

- **University Courses:**
  - The university courses are organized as a doubly linked list for effective navigation.

- **Data Structures Used:**
  - Singly and doubly linked lists.

## File Management

- The system efficiently reads a static list of university courses from a file.
- Student information is seamlessly read from and written back to a file, ensuring persistent storage of changes.

## Notable Achievements

Upon meeting the basic project requirements, notable features have been incorporated to enrich the system:

- **Instructor Features:**
  - Instructors can log in to access a comprehensive list of courses they teach.

- **Attendance Management:**
  - Instructors can conveniently take class attendance.

- **Grade Handling:**
  - Instructors have the ability to input grades for courses, and students can easily access and review their grades.

- **Dynamic Functionalities:**
  - Various other useful functionalities have been integrated for an enhanced user experience.

## Database

- **Data Storage:**
  - The system utilizes CSV format for efficient storage and retrieval of student and course information.

## Note

- **Array Usage:**
   - Arrays are strictly avoided, except for character arrays for names and email addresses (Strings).
