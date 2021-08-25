/*
*Title:Assignment - Student Registration System
*Course:CST8234 -C language
*Term :Summer 2021
*

*
*   Status:
*   Requirement #1:{complete}
*   Requirement #2:{complete}
*   Requirement #3:{complete}
*   Requirement #4:{complete}
*   Requirement #5:{complete}
*   Requirement #6:{complete}
*   Requirement #7:{complete}
*   Requirement #8:{complete}
*   Requirement #9:{complete}
**/


/**************************************************************************
Declare include files
***************************************************************************/
#include "studentRgistrationSystem.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**************************************************************************
 Declare MACRO MAX_MESSAGE
**************************************************************************/

#define MAX_COURSE_code 7

/**************************************************************************
 Declare global variables
**************************************************************************/

/*This is the number of students to register */
int numberStudents;
/*This is the number of the offered courses */
int numberCourses;
/*This is the array that holds the studens' IDs*/
int *studentIDs;
/*This is the array that holds the cordes'codes*/
char **courses;
/*This is the array that holds the status of each student*/
int **registrationTable;



/**************************************************************************
 * Main function
 * The students registrations table is a program that allows users to 
 * register students or drop them from the offered courses 
 * 
 * Version: 1.0
 * Author/Student Name: Younes Boutaleb & Jeel  Patel
 **************************************************************************/

int main()
{

  /*this is the return code of the user input*/
  int rc;
  /*this is the index of the outer loops*/
  int index;
  /*this is the index of the inner loops*/
  int i;
  /*this is the action chosen by the user from the main menu*/
  int action;

 
  /**************************************************************************
   Prompt for number of students and allocate memory to studenIDs array
  ***************************************************************************/

  printf("Welcome to the Student Register System (SRS)\n\n");
  printf("How many students would you like to register: ");
  /*Prompt for the number of students and validates the user input*/
  numberStudents = checkIntegerInput();
  /*Allocate enough memory to to studentIDs array*/
  allocateMemoryToStudentIDs();

  /**************************************************************************
   Prompt for students IDs
  ***************************************************************************/

  /*Prompt for ID of each student and validates the user input*/
  for (index = 0; index < numberStudents; index++)
  {
    printf("Please enter the student ID for student %d: ", index + 1);
    /*Prompt for students ID and validate checks for a positive integer*/
    studentIDs[index] = checkIntegerInput();

    /*Checks if the ID is a five digits number which doesn't start with 0*/
    if (studentIDs[index] < 10000 || studentIDs[index] > 99999)
    {
      printf("invalid student ID\n");
      index--;
    } /*end if */

  /*Check for duplicate IDs*/
    for (i = 0; i < index; i++)
    {
      if (studentIDs[i] == studentIDs[index])
      {
        printf("Error: Student IDs are unique (no duplicates). Try again.\n");
        i = index;
        /*If the user enters a duplicate ID it ovewrite it*/
        index--;
      } /*end if */
    }   /*end for */

  } /*end for */

  /*Prints the stuedents' IDs*/
  printIntArray(studentIDs, numberStudents);

  /**************************************************************************
   Prompt for number of courses 
   and allocate memory to courses and registrationTable arrays
  ***************************************************************************/

  printf("How many courses are you offering: ");
  /*Prompt for the number of courses and validates the user input*/
  numberCourses = checkIntegerInput();
  /*Allocate enough memory for the courses and registartion table arrays*/
  allocateMemoryToCourses();
  allocateMemoryToRegistrationTable();

  /**************************************************************************
   Prompt for courses' codes
  ***************************************************************************/

  /*Prompt for THE code of each course and validates the user input*/
  for (index = 0; index < numberCourses; index++)
  {
    printf("Please enter the course code for course %d: ", index + 1);

    rc = 0;

    /*Prompts for course code and checks each character*/
    while (rc != 7)
      {
        char code[7+1];
        scanf(" %8[^\n]s", code);
        /*Returns 7 if all characters are valid "LLLNNNN"*/
        rc = CheckCourseCode(code);

        /*Repromt if not a valid code*/
        if (rc != 7)
        {
          printf("invalid course code\n");
          rc = 0;
        
        }/*end if */
        /*Store valid codes in the courses array*/
        else{

         strcpy(courses[index], code);

        }/*end else */
      }/*end for */

    /*Check for duplicate codes*/
    for (i = 0; i < index; i++)
    {

      if (!strcmp(courses[i], courses[index]))
      {
        printf("Error: course IDs are unique (no duplicates). Try again.\n");
        i = index;
        /*If the user enters a duplicate ID it ovewrite it*/
        index--;
      } /*end if */
    }   /*end for */
    
  } /*end for*/

  /*Prints the courses' codes*/
  printStringArray(courses, numberCourses);

  /**************************************************************************
   Prompt for the action to be performed
  ***************************************************************************/
  
  action=0;
  while (action != 4)
  {
    /*Display menu*/
    menu();

    /*Prompt for the action to be performed and validates the input */
    action = checkIntegerInput();

  /**************************************************************************
   Define all actions
  ***************************************************************************/

    /*This switch statements executes the chosen action */
    switch (action)
    {

    /*Register a student into a course */
    case 1:

      registerOrDrop(1);

      break;

    /*Drop a student from a course */
    case 2:

      registerOrDrop(0);

      break;

    /*Display the registration table */
    case 3:

      print2DArray(*registrationTable, numberStudents, numberCourses);
      break;
    /*Program terminates*/
    case 4:

      break;

    /*Print error message and Re-prompt for a valid action*/
    default:

      printf("Error: unknown action: %d\nTry again...\n", action);
      break;

    } /*end switch*/

  } /*end while*/

/**************************************************************************
  Free memory allocated to datastructures
***************************************************************************/
  
  /*Free memory allocated to studentIDs array*/
  free(studentIDs);

  /*Free memory allocated to courses array*/
  for(index=0; index<numberCourses; index++){

    free(courses[index]);
  }

  free(courses);

  /*Free memory allocated to registrationTable array*/
  for(index=0; index<numberStudents; index++){

    free(registrationTable[index]);
  }

  free(registrationTable);

  return EXIT_SUCCESS;

} /*end main   */



/**************************************************************************
* 
* 
* Declare and define helper methodes
*
*
***************************************************************************/


/**************************************************************************
  print any 1D integer array
***************************************************************************/

void printIntArray(int array[], size_t length)
{
  /*This the array index */
  int index;
  printf("[");
  for (index = 0; index < length; index++)
  {
    printf("%d", array[index]);
    if (index < length - 1)
    {
      printf(", ");
    }/*end if */
  }/*end for */
  printf("]\n");
}/*end printIntArray */

/**************************************************************************
  print any 1D char array
  *array[] pointer to a C string
***************************************************************************/

void printStringArray(char *array[], size_t length) 
{
  /*This the array index */
  int index;
  printf("[");
  for (index = 0; index < length; index++)
  {
    printf("%s", array[index]);
    if (index < length - 1)
    {
      printf(", ");
    }/*end if */
  }/*end for */
  printf("]\n");
}/*end printStringArray */


/**************************************************************************
 Initialize any integer 2d array.
 This is important so that the complier correctly reserve the needed space in
 memory. You won't be able to use these arrays otherwise.

 Usage:
 int array[rowSize][columnSize];
 initilaize2DArray((int *)array, rowSize, columnSize);
***************************************************************************/

void init2DArray(int *array, size_t rowSize, size_t columnSize)
{
  /*This the array column and row */
  int row, column;
  for (row = 0; row < rowSize; row++)
  {
    for (column = 0; column < columnSize; column++)
    {
      *(array + row * columnSize + column) = -1;
    }/*end if */
  }/*end for */
}/*end init2DArray */

/**************************************************************************
 Convenience function to print integer 2D arrays

 Usage:
 int array[rowSize][columnSize];
 print2DArray((int *)array, rowSize, columnSize);
***************************************************************************/

void print2DArray(int *array, size_t rowSize, size_t columnSize)
{
  /*This the array column and row */
  int row, column;
  printf("[ ");
  for (row = 0; row < rowSize; row++)
  {
    printf("[ ");
    for (column = 0; column < columnSize; column++)
    {
      printf("%d", *(array + row * columnSize + column));
      if (column < columnSize - 1)
      {
        printf(", ");
    }/*end if */
  }/*end for */
    printf(" ]");
    if (row < rowSize - 1)
    {
      printf(", ");
    }/*end if */
  }/*end for */
  printf(" ]\n");
}/*end print2DArray */

/**************************************************************************
  dynamically memory allocation to data structures
***************************************************************************/

/* 
studentIDs array:  dynamically allocate an 1-D array of pointers to int  and initialize it to 0 
*/
int allocateMemoryToStudentIDs()
{
  studentIDs = (int *)malloc(sizeof(int) * numberStudents);

  /* Return an error message if no enough memory */
  if (NULL == studentIDs)
  {
    fprintf(stderr, "Error - could not allocate memory for the array of studentIDs");
    return EXIT_FAILURE;
  }

  /* Initialize studentIDs array to 0  */
  memset(studentIDs, 0, sizeof(int) * numberStudents);

  return EXIT_SUCCESS;

} /* end allocateMemoryToStudentIDs */


/* 
courses array: dynamically allocate an 2-D array of pointers to char (C strings) and initialize it to '\0' character 
*/
int allocateMemoryToCourses(){

  /*This the array index */
  int index;
  courses = malloc(numberCourses * sizeof(char *));

  /* Return an error message if no enough memory */
  if (NULL == courses)
  {
    fprintf(stderr, "Error - could not allocate memory for the array of courses");
    return EXIT_FAILURE;
  } /*end if    */

  /* Initialize memory to null character */
  memset(courses, '\0', numberCourses * sizeof(char *));

  /* Dynamically allocate enough memory for courses codes and initialize them to '\0' character */
  for (index = 0; index < numberCourses; index++)
  {

    courses[index] = (char *)malloc(MAX_COURSE_code * sizeof(char));

    /* Return an error message if no enough memory */
    if (courses[index] == NULL)
    {
      fprintf(stderr, "Error - could not allocate memory for the course code");
      return EXIT_FAILURE;
    } /*end if    */

    /* Initialize memory to '\0' character */
    memset(courses[index], '\0', sizeof(char) * MAX_COURSE_code);
  } /*end for */

  return EXIT_SUCCESS;

}/* end allocateMemoryToCourses */

 /* registrationTable array: dynamically allocate an 2-D array of pointers to int and initialize it to '\0' */
int allocateMemoryToRegistrationTable(){

  /*This the array index */
  int index;

  registrationTable = malloc(numberStudents * sizeof(int *));
  /* Return an error message if no enough memory */
  if (NULL == registrationTable)
  {
    fprintf(stderr, "Error - could not allocate memory for the registration Table");
    return EXIT_FAILURE;
  } /*end if    */
  /* Initialize memory to '\0' character */
  memset(registrationTable, '\0', sizeof(int *) * numberStudents);

  /* Dynamically allocate enough memory for table cells and initialize it to 0 */
  for (index = 0; index < numberStudents; index++)
  {
    registrationTable[index] = (int *)malloc(numberCourses * sizeof(int));

    /* Return an error message if no enough memory */
    if (registrationTable[index] == NULL)
    {
      fprintf(stderr, "Error - could not allocate memory for the table cells");
      return EXIT_FAILURE;
    } /*end if  */

    /* memset(registrationTable[index], -1, sizeof(int) * numberCourses); */

    init2DArray(*registrationTable, numberStudents, numberCourses);

  } /*end for */

  return EXIT_SUCCESS;

} /*end allocateMemoryToRegistrationTable */

/**************************************************************************
  Check for integer inputs
***************************************************************************/

int checkIntegerInput()
{

  /*This is the user input */
  int number;
  /*This the return code */
  int rc = 0;
  /*This the next char after scanf() terminates */
  char nextChar;

  /*Loops untill the user enter a valid input */
  while (rc != 1)
  {
    /*it takes 1 if scanf reads an integer*/
    rc = scanf(" %d", &number);
    /*Read the next character in stdin after scanf is executed*/
    nextChar = getchar();

    /*Checks for clrt-d input which stands for the end of input EOF
    Exits the game with failure if the user enters the EOF character*/
    if (nextChar == -1)
    {
      puts("Program shutdown.\n");
      return EXIT_FAILURE;
    } /*end if*/

    /*Prints an error message if the user enters an invalid input (strings/float/negative integer)
    and goes back to the while loop*/
    else if (rc != 1 || nextChar != '\n' || number < 0)
    {
      rc = 0;
      printf("Error - enter a positive integer number: ");

      /*if not a valid input clear the stdin*/
      if (nextChar != '\n')
      {

        while (getchar() != '\n')
        {
          /*chomp stdin*/
        } /*end while*/
      }   /*end  if*/
    }     /*end else if*/
  }

  /*return valid input*/
  return number;

} /* end checkIntegerInput */

/**************************************************************************
  Validating course code inputs
***************************************************************************/

int CheckCourseCode(char code[])
{

  /*This the return code */
  int rc=0;
  /*This the array index */
  int index;

    /*Display error message if not a 7 charachetrs string input and returns 0*/
    if (strlen(code) != 7)
    {
      printf("invalid course code\n");
      rc = 0;
      while (getchar() != '\n')
      {
        /* chomp stdin */
      }/*end  while*/
    } /*end if*/

    /*Counts the number of valid characters in the code*/
    else
    {
      for (index = 0; index < strlen(code); index++)
      {

        if (index < 3 && isalpha(code[index]))
        {
          ++rc;
        } /*end  if*/
        else if (index >= 3 && isdigit(code[index]))
        {
          ++rc;
        } /*end  else if*/
      } /*end for*/
    }/*end  else*/

  /*Return the number of valid characters in the code entered*/
  return rc;

} /* end CheckCourseCode */

/**************************************************************************
   Display menu of actions
***************************************************************************/

void menu()
{

  printf("Please choose one of the following actions:\n");
  printf("1- Register a student in a course\n");
  printf("2- Drop a student's course\n");
  printf("3- Print registration table\n");
  printf("4- Quit\n");
  printf("Please enter action number: \n");
}/* end menu() */


/**************************************************************************
   Register (1) or Drop a student(0) from a course
***************************************************************************/

void registerOrDrop(int choice)
{
  /* THis is the array index */
  int index;
  /* THis is the return code */
  int rc;
  /* This is the code of the course to be registered/dropped */
  char coursecode[7+1];
  /* Index of the entered student ID if exists */
  int indexOfValidID=-1;
  /* Index of the entered course code if exists */
  int indexOfValidCourse=-1;
  /* This is the entered student ID */
  int ID=0;

  /* Loops until users enters an existing Student ID */
  while (indexOfValidID == -1)
  {

    printf("Please enter the student ID: ");
    /* prompts for Student ID and validate integer input*/
    ID = checkIntegerInput();

    /* Compare ID with existing IDs*/
    for (index = 0; index < numberStudents; index++)
    {
      /* assign the current index to indexOfValidID and breaks for loop if ID is found*/
      if (ID == studentIDs[index])
      {
        indexOfValidID = index;
        index = numberStudents;
      } /*end if */
      else
      {
        indexOfValidID = -1;

      } /*end else */
    }   /*end for */

    /* Display error message if ID not found*/
    if (indexOfValidID == -1)
    {
      printf("Error: student ID %d not found. Try again.\n", ID);
    } /*end if */
  }   /*end while */

  /* Loops until users enters an existing course code */
    while (indexOfValidCourse == -1)
  {

    printf("Please enter the course code: ");
        rc = 0;

    /* Loops until users enters a valid course code */
    while (rc != 7)
      {
        /* This is the course to be registered to/dropped*/
        char code[8+1];
        /* Promps the course code and checks input*/
        scanf(" %8[^\n]s", code);
        rc = CheckCourseCode(code);

        /* Display error message if the course code is not valid */
        if (rc != 7)
        {
          printf("invalid course code\n");
          rc = 0;
        }else{

         strcpy(coursecode, code);

    } /*end else */
  }   /*end while */

     /* Compare ID with existing couses' codes*/
    for (index = 0; index < numberCourses; index++)
    {
      /* assign the current index to indexOfValidCourse and breaks for loop if course code is found*/
      if (!strcmp(coursecode, courses[index]))
      {
        indexOfValidCourse = index;
        index = numberCourses;
      } /*end if */


      else
      {
        indexOfValidCourse = -1;
      } /*end else */
    }   /*end for */

    /* Display error message if the course code is not valid */
    if (indexOfValidCourse == -1)
    {
      printf("Error: course code %s not found. Try again.\n", coursecode);
    }/*end if */

  } /*end while */

  /*Put the user choice in the registration table */
  *(*registrationTable + indexOfValidID * numberCourses + indexOfValidCourse) = choice;

  /*print the current student status */
  print2DArray(*registrationTable, numberStudents, numberCourses);

} /*end registerOrDrop */