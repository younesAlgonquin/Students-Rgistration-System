#ifndef studentRgistrationSystem_h
#define studentRgistrationSystem_h

#include <stdio.h>

/**
 ** Header (.H) file for Assignment 1 - Student Registration System (SRS)
 **
 ** You are not permitted to add / subtract / alter from this file.
 **
 ** @version 1.0
 **
 ** @author Younes
 **/

/**************************************************************************
  print any 1D integer array 
***************************************************************************/
void printIntArray(int array[], size_t length);


/**************************************************************************
  print any 1D char array
  *array[] pointer to a C string
***************************************************************************/
void printStringArray(char *array[], size_t length);


/**************************************************************************
 Initialize any integer 2d array.
 This is important so that the complier correctly reserve the needed space in
 memory. You won't be able to use these arrays otherwise.

 Usage:
 int array[rowSize][columnSize];
 initilaize2DArray((int *)array, rowSize, columnSize);
***************************************************************************/
void init2DArray(int *array, size_t rowSize, size_t columnSize);


/**************************************************************************
 Convenience function to print integer 2D arrays

 Usage:
 int array[rowSize][columnSize];
 print2DArray((int *)array, rowSize, columnSize);
***************************************************************************/
void print2DArray(int *array, size_t rowSize, size_t columnSize);


/**************************************************************************
  dynamically memory allocation to studentIDs array (Done by Younes)
***************************************************************************/
int allocateMemoryToStudentIDs();


/**************************************************************************
  dynamically memory allocation to courses array (Done by Younes)
***************************************************************************/
int allocateMemoryToCourses();


/**************************************************************************
  dynamically memory allocation to registrationTable array (Done by JEEL)
***************************************************************************/
int allocateMemoryToRegistrationTable();


/**************************************************************************
  check for integer inputs (Done by Younes)
***************************************************************************/
int checkIntegerInput();


/**************************************************************************
  Validating course code inputs (Done by JEEL)
***************************************************************************/
int CheckCourseCode(char code[]);


/**************************************************************************
   Display menu of actions  (Done by JEEL)
***************************************************************************/
void menu();


/**************************************************************************
   Register (1) or Drop a student(0) from a course  (Done by Younes)
***************************************************************************/
void registerOrDrop(int choice);

#endif /* studentRgistrationSystem_h */
