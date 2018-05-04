/* CS 362 Random Testing Quiz */
/*************************************************************************
 ** Author:                  Michael Tucker
 ** Date Created:            5/1/2018
 ** Last Modification Date:  5/6/2018
 ** Filename:                testme.c
 ** 
 ** Overview:  This program implements a random tester for the function
 **            testme(). The functions inputChar() and inputString() are
 **            implemented to accomplish this. The coverage goal is 
 **            to execute the testme() function such that the error
 **            message is printed.
 ** 		   This is my random testing quiz submission.
 ** Input:   None.  The program executes and calls the testme() function.
 **          which in turn calls inputChar() and inputString()
 ** Output:  Iteration stats printed to stdout (screen or user console
 ************************************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>


/*************************************************************************
 ** Function:                inputChar
 ** 
 ** Description:    Function to return a random ASCII character within
 **                 the range from Space (32) to '}' (125)
 ************************************************************************/
 
char inputChar()
{
	int randIdx;
    int adjIdx;

    char testChar;
	
	// Range of ASCII characters is Space to '}'
    randIdx = (rand() % 94);
    adjIdx = randIdx + 32;
    
    testChar = adjIdx;
    
    return testChar;
}


/*************************************************************************
 ** Function:                inputString
 ** 
 ** Description:    Function to return a string of 5 random lowercase
 **                 characters in the ranges 'a' to 'h' and 'o' to 'v'
 ************************************************************************/
 
char *inputString()
{
	int randIdx;
    int adjIdx;
    int i;
    
    char* testStr = (char *) malloc(16 * sizeof(char));

	// Construct a 5 character string using random characters
    for (i = 0; i < 5; i++)
    {
        randIdx = (rand() % 9); 
        adjIdx = randIdx + 97;
        if ((i % 2) == 0)
        {
            adjIdx += 14;
        }

        testStr[i] = adjIdx;
    }
    testStr[5] = '\0';
		
    return testStr;
}


/************************************************************************/

void testme()
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
	  
      free(s);
      s = NULL;
	  
      exit(200);
    }
  }
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
