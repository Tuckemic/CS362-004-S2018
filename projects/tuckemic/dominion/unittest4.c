/* CS 362 Assignment 3 */
/*************************************************************************
 ** Author:                  Michael Tucker
 ** Date Created:            4/24/2018
 ** Last Modification Date:  4/29/2018
 ** Filename:                unittest4.c
 ** 
 ** Overview:  This program implements a Unit Test Suite for testing the
 **            isGameOver function from the dominion.c file. The 
 **            dominion.c file implements a Dominion card game. The test 
 **            suite includes tests for the effect the function has on 
 **            the elements of the Game State as well as the performance
 **            of the function over a range of input arguments.
 **			   The Unit tests include:
 **			   TEST 1: All Supply Piles Have Cards  
 ** 		   TEST 2: One Supply Pile is Empty
 **			   TEST 3: Two Supply Piles are Empty
 **			   TEST 4: Province Card Supply Pile is Empty
 **			   TEST 5: First 4 Supply piles are Empty
 **			   TEST 6: 3 Supply Piles are Empty
 **			   TEST 7: Last 3 Supply Piles are Empty
 ** Input:   None.  The program executes and calls the function from the
 **          dominion.c file, which includes code under test. 
 ** Output:  A new file is created and appended, unittestresults.out
 **          which includes all unit test and coverage results.
 ************************************************************************/
 

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.h"

#include <stdio.h>
#include <string.h>

#define TESTFUNCTIONNAME "isGameOver()"
#define NUMCARDOPTIONS 17

 
/************************************************************************/

// Composition of struct gameState from dominion.h 
/*
struct gameState 
{
    int numPlayers;     //number of players
    int supplyCount[treasure_map+1];  //this is the amount of a specific type of card given a specific number.
    int embargoTokens[treasure_map+1];
    int outpostPlayed;
    int outpostTurn;
    int whoseTurn;
    int phase;
    int numActions;     // Starts at 1 each turn 
    int coins;          // Use as you see fit! 
    int numBuys;        // Starts at 1 each turn 
    int hand[MAX_PLAYERS][MAX_HAND];
    int handCount[MAX_PLAYERS];
    int deck[MAX_PLAYERS][MAX_DECK];
    int deckCount[MAX_PLAYERS];
    int discard[MAX_PLAYERS][MAX_DECK];
    int discardCount[MAX_PLAYERS];
    int playedCards[MAX_DECK];
    int playedCardCount;
};
*/


/*************************************************************************
 ** Function:                assertMsg
 ** 
 ** Description:    Function to use the input condition to determine
 **                 if a Passed or Failed message is output based on the
 **                 result of a unit subtest. This is a generic function
 **                 for displaying the test results. The condition is
 **                 determined outside the function.
 ************************************************************************/
 
void assertMsg(int condition, char* trueMsg, char* falseMsg)
{
    if (condition)
    {
        // printf("PASSED: %s\n", trueMsg);
    }
    
    else
    {
        printf("FAILED: %s\n", falseMsg);
    }  
}


/*************************************************************************
 ** Function:                assertMsgIGO
 ** 
 ** Description:    Function to compare the actual value of the test 
 **                 result produced by a unit subtest to the expected 
 **                 value. If the test fails, a FAIL message and failure 
 **                 results for the test are output. The test inputs
 **                 are specific to the tests run on isGameOver function.
 ************************************************************************/

int assertMsgIGO(char* subTestLabel, int testNum, int actualVal, int expectedVal)
{
    char failMsg[128];
    char tempStr[128];
  
    int resultVal = 0;

    if (actualVal != expectedVal)
    {
        strcpy(failMsg, "FAILED. Test");
		sprintf(tempStr, "%d:  %s:  ", testNum, subTestLabel);
		strcat(failMsg, tempStr);
		sprintf(tempStr, "actual: %d != expected: %d\n", actualVal, expectedVal);
		strcat(failMsg, tempStr);
        printf(failMsg);
        resultVal = -1;
    }

    return resultVal;
}


/************************************************************************/

// isGameOver() function from dominion.c

/*

int isGameOver(struct gameState *state) 
{
  int i;
  int j;
	
  //if stack of Province cards is empty, the game ends
  if (state->supplyCount[province] == 0)
  {
     return 1;
  }

  //if three supply pile are at 0, the game ends
  j = 0;
  for (i = 0; i < 25; i++)
  {
    if (state->supplyCount[i] == 0)
	{
	  j++;
	}
  }
  if ( j >= 3)
  {
      return 1;
  }

  return 0;
}
*/ 
 
 
/*************************************************************************
 ** Function:                testIsGameOver
 ** 
 ** Description:    Function to implement the Unit Tests for testing 
 **                 the isGameOver() function in dominion.c
 ************************************************************************/
 
int testIsGameOver()
{
    char msgPfx[128];
    char msgSfx[128];
    char passMsg[128];
    char failMsg[128];
    char passMsg2[128];

    char supplyTestLabel[64];

    int testNum;
	int result = 0;
    int retVal;
	int actualVal;
    int expectedVal;
    int assertRetVal; 
    int assertCondition = 0;
	
	int numPlayers = 2;
    int randSeed = 1000;
    			 
	int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
				 // Kingdom Card numbers: 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
				 // Victory Card numbers: 0, 1, 2, 3
				 // Treasure Card numbers: 4, 5, 6
    
    struct gameState baseGst, testGst, initialGst;
	
    strcpy(supplyTestLabel, "supply test");
    strcpy(passMsg2, "PASSED: TEST ");

	
	/************************************************************************/

	printf("----------------- Testing Function: %s ----------------\n", TESTFUNCTIONNAME);
	
    // Pre-testing setup of game states	
	
	// Initialize a Game: set initial game state 
	initializeGame(numPlayers, k, randSeed, &initialGst);

	// Copy the initial game state to a base case and a test case game state
	memcpy(&baseGst, &initialGst, sizeof(struct gameState));
	memcpy(&testGst, &initialGst, sizeof(struct gameState));

	
	/************************************************************************/	
	// Test with no supply piles empty
	
	// ----------- TEST 1: All Supply Piles Have Cards --------------
	
	strcpy(msgPfx, "TEST 1: All Supply Piles Have Cards");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 1");
    strcpy(failMsg, "N/A");

    testNum = 1;

	
	// Run the Test
	
    // Call the isGameOver function for this input combination
	retVal = isGameOver(&testGst);

	
	/************************************************************************/	
	
	// Test: Return value indicates Game Over Status. 1 = Game Over. 0 = Game Continues
	actualVal = retVal;
	expectedVal = 0;
	assertRetVal = assertMsgIGO(supplyTestLabel, testNum, actualVal, expectedVal);
	if (assertRetVal == -1)
	{
		result = assertRetVal;
	}
	
	// Test: Compare base game state to test game state for any changes.
               
    strcpy(msgPfx, "TEST 1");
    strcat(msgPfx, ":  ");

    if (memcmp(&testGst, &baseGst, sizeof(struct gameState)) == 0)
    {
		assertCondition = 1;  
    }
         
    else
    {
		assertCondition = 0;
		sprintf(msgSfx, "Game State has changed after running test.");
		strcat(msgPfx, msgSfx);
		strcpy(failMsg, msgPfx);
		result = -1;
    } 
                
    assertMsg(assertCondition, passMsg, failMsg);
	
    if (result == 0)
    {
        printf(passMsg2);
        printf("%d\n", testNum);
    }
	
	
	/************************************************************************/
	
	// Test with one supply pile empty -- 13
	
	// ----------- TEST 2: One Supply Pile is Empty --------------

	strcpy(msgPfx, "TEST 2: One Supply Pile is Empty");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 2");
    strcpy(failMsg, "N/A");

    testNum = 2;
	
	
	// Initialize game state for number of empty piles
	testGst.supplyCount[smithy] = 0;
	
	// Copy the changed test game state to base case game state for later comparison
	memcpy(&baseGst, &testGst, sizeof(struct gameState));

	
	// Run the Test
	
    // Call the isGameOver function for this input combination
	retVal = isGameOver(&testGst);

	
	/************************************************************************/
	
	// Test: Return value indicates Game Over Status. 1 = Game Over. 0 = Game Continues
	actualVal = retVal;
	expectedVal = 0;
	assertRetVal = assertMsgIGO(supplyTestLabel, testNum, actualVal, expectedVal);
	if (assertRetVal == -1)
	{
		result = assertRetVal;
	}
	
	// Test: Compare base game state to test game state for any changes.
               
    strcpy(msgPfx, "TEST 2");
    strcat(msgPfx, ":  ");

    if (memcmp(&testGst, &baseGst, sizeof(struct gameState)) == 0)
    {
		assertCondition = 1;  
    }
         
    else
    {
		assertCondition = 0;
		sprintf(msgSfx, "Game State has changed after running test.");
		strcat(msgPfx, msgSfx);
		strcpy(failMsg, msgPfx);
		result = -1;
    } 
                
    assertMsg(assertCondition, passMsg, failMsg);
	
    if (result == 0)
    {
        printf(passMsg2);
        printf("%d\n", testNum);
    }
	
	
	/************************************************************************/
	
	// Test with only two supply piles empty -- 11, 12
	
	// ----------- TEST 3: Two Supply Piles are Empty --------------

	strcpy(msgPfx, "TEST 3: Two Supply Piles are Empty");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 3");
    strcpy(failMsg, "N/A");

    testNum = 3;
	
	// Reset game states
	memcpy(&baseGst, &initialGst, sizeof(struct gameState));
	memcpy(&testGst, &initialGst, sizeof(struct gameState));
	
	// Initialize game state for number of empty piles (index 1)
	testGst.supplyCount[mine] = 0;
	testGst.supplyCount[remodel] = 0;
		
	// Copy the changed test game state to base case game state for later comparison
	memcpy(&baseGst, &testGst, sizeof(struct gameState));
	
	
	// Run the Test
	
    // Call the isGameOver function for this input combination
	retVal = isGameOver(&testGst);

	
	/************************************************************************/
	
	// Test: Return value indicates Game Over Status. 1 = Game Over. 0 = Game Continues
	actualVal = retVal;
	expectedVal = 0;
	assertRetVal = assertMsgIGO(supplyTestLabel, testNum, actualVal, expectedVal);
	if (assertRetVal == -1)
	{
		result = assertRetVal;
	}
	
	// Test: Compare base game state to test game state for any changes.
               
    strcpy(msgPfx, "TEST 3");
    strcat(msgPfx, ":  ");

    if (memcmp(&testGst, &baseGst, sizeof(struct gameState)) == 0)
    {
		assertCondition = 1;  
    }
         
    else
    {
		assertCondition = 0;
		sprintf(msgSfx, "Game State has changed after running test.");
		strcat(msgPfx, msgSfx);
		strcpy(failMsg, msgPfx);
		result = -1;
    } 
                
    assertMsg(assertCondition, passMsg, failMsg);
	
    if (result == 0)
    {
        printf(passMsg2);
        printf("%d\n", testNum);
    }
	
	
	/************************************************************************/
	
	// Test with province pile empty -- 3
	
	// ----------- TEST 4: Province card supply pile is Empty --------------

	strcpy(msgPfx, "TEST 4: Province card supply pile is Empty");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 4");
    strcpy(failMsg, "N/A");

    testNum = 4;
	
	// Reset game states
	memcpy(&baseGst, &initialGst, sizeof(struct gameState));
	memcpy(&testGst, &initialGst, sizeof(struct gameState));
	
	// Initialize game state for number of empty piles (index 1)
	testGst.supplyCount[province] = 0;
	
	// Copy the changed test game state to base case game state for later comparison
	memcpy(&baseGst, &testGst, sizeof(struct gameState));

	
	// Run the Test
    
	// Call the isGameOver function for this input combination
	retVal = isGameOver(&testGst);
	
	
	/************************************************************************/
	
	// Test: Return value indicates Game Over Status. 1 = Game Over. 0 = Game Continues
	actualVal = retVal;
	expectedVal = 1;
	assertRetVal = assertMsgIGO(supplyTestLabel, testNum, actualVal, expectedVal);
	if (assertRetVal == -1)
	{
		result = assertRetVal;
	}
	
	
	// Test: Compare base game state to test game state for any changes.
               
    strcpy(msgPfx, "TEST 4");
    strcat(msgPfx, ":  ");

    if (memcmp(&testGst, &baseGst, sizeof(struct gameState)) == 0)
    {
		assertCondition = 1;  
    }
         
    else
    {
		assertCondition = 0;
		sprintf(msgSfx, "Game State has changed after running test.");
		strcat(msgPfx, msgSfx);
		strcpy(failMsg, msgPfx);
		result = -1;
    } 
                
    assertMsg(assertCondition, passMsg, failMsg);
	
    if (result == 0)
    {
        printf(passMsg2);
        printf("%d\n", testNum);
    }
	
	
	/************************************************************************/
	
	// Test with cards 0, 1, 2, 4 empty
	
	// ----------- TEST 5: First 4 supply piles are Empty --------------

	strcpy(msgPfx, "TEST 5: First 4 supply piles are Empty");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 5");
    strcpy(failMsg, "N/A");

    testNum = 5;
	
	// Reset game states
	memcpy(&baseGst, &initialGst, sizeof(struct gameState));
	memcpy(&testGst, &initialGst, sizeof(struct gameState));
	
	// Initialize game state for number of empty piles (index 1)
	testGst.supplyCount[curse] = 0;
	testGst.supplyCount[estate] = 0;
	testGst.supplyCount[duchy] = 0;
	testGst.supplyCount[copper] = 0;
	
	// Copy the changed test game state to base case game state for later comparison
	memcpy(&baseGst, &testGst, sizeof(struct gameState));

	
	// Run the Test
    
	// Call the isGameOver function for this input combination
	retVal = isGameOver(&testGst);
	
	
	/************************************************************************/
	
	// Test: Return value indicates Game Over Status. 1 = Game Over. 0 = Game Continues
	actualVal = retVal;
	expectedVal = 1;
	assertRetVal = assertMsgIGO(supplyTestLabel, testNum, actualVal, expectedVal);
	if (assertRetVal == -1)
	{
		result = assertRetVal;
	}
	
	
	// Test: Compare base game state to test game state for any changes.
               
    strcpy(msgPfx, "TEST 5");
    strcat(msgPfx, ":  ");

    if (memcmp(&testGst, &baseGst, sizeof(struct gameState)) == 0)
    {
		assertCondition = 1;  
    }
         
    else
    {
		assertCondition = 0;
		sprintf(msgSfx, "Game State has changed after running test.");
		strcat(msgPfx, msgSfx);
		strcpy(failMsg, msgPfx);
		result = -1;
    } 
                
    assertMsg(assertCondition, passMsg, failMsg);
	
    if (result == 0)
    {
        printf(passMsg2);
        printf("%d\n", testNum);
    }
	
	/************************************************************************/
	
	// Test with cards 6, 7, 8 empty
	
	// ----------- TEST 6: 3 supply piles are Empty --------------

	strcpy(msgPfx, "TEST 6: 3 supply piles are Empty");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 6");
    strcpy(failMsg, "N/A");

    testNum = 6;
	
	// Reset game states
	memcpy(&baseGst, &initialGst, sizeof(struct gameState));
	memcpy(&testGst, &initialGst, sizeof(struct gameState));
	
	// Initialize game state for number of empty piles (index 1)
	testGst.supplyCount[gold] = 0;
	testGst.supplyCount[adventurer] = 0;
	testGst.supplyCount[council_room] = 0;
	
	// Copy the changed test game state to base case game state for later comparison
	memcpy(&baseGst, &testGst, sizeof(struct gameState));

	
	// Run the Test
    
	// Call the isGameOver function for this input combination
	retVal = isGameOver(&testGst);
	
	
	/************************************************************************/
	
	// Test: Return value indicates Game Over Status. 1 = Game Over. 0 = Game Continues
	actualVal = retVal;
	expectedVal = 1;
	assertRetVal = assertMsgIGO(supplyTestLabel, testNum, actualVal, expectedVal);
	if (assertRetVal == -1)
	{
		result = assertRetVal;
	}
	
	
	// Test: Compare base game state to test game state for any changes.
               
    strcpy(msgPfx, "TEST 6");
    strcat(msgPfx, ":  ");

    if (memcmp(&testGst, &baseGst, sizeof(struct gameState)) == 0)
    {
		assertCondition = 1;  
    }
         
    else
    {
		assertCondition = 0;
		sprintf(msgSfx, "Game State has changed after running test.");
		strcat(msgPfx, msgSfx);
		strcpy(failMsg, msgPfx);
		result = -1;
    } 
                
    assertMsg(assertCondition, passMsg, failMsg);
	
    if (result == 0)
    {
        printf(passMsg2);
        printf("%d\n", testNum);
    }
	
	
	/************************************************************************/
	
	// Test with cards 24, 25, 26 empty
	
	// ----------- TEST 7: Last 3 supply piles are Empty --------------

	strcpy(msgPfx, "TEST 7: Last 3 supply piles are Empty");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 7");
    strcpy(failMsg, "N/A");

    testNum = 7;
	
	// Reset game states
	memcpy(&baseGst, &initialGst, sizeof(struct gameState));
	memcpy(&testGst, &initialGst, sizeof(struct gameState));
	
	// Initialize game state for number of empty piles (index 1)
	testGst.supplyCount[salvager] = 0;
	testGst.supplyCount[sea_hag] = 0;
	testGst.supplyCount[treasure_map] = 0;
	
	// Copy the changed test game state to base case game state for later comparison
	memcpy(&baseGst, &testGst, sizeof(struct gameState));

	
	// Run the Test
    
	// Call the isGameOver function for this input combination
	retVal = isGameOver(&testGst);
	
	
	/************************************************************************/
	
	// Test: Return value indicates Game Over Status. 1 = Game Over. 0 = Game Continues
	actualVal = retVal;
	expectedVal = 1;
	assertRetVal = assertMsgIGO(supplyTestLabel, testNum, actualVal, expectedVal);
	if (assertRetVal == -1)
	{
		result = assertRetVal;
	}
	
	
	// Test: Compare base game state to test game state for any changes.
               
    strcpy(msgPfx, "TEST 7");
    strcat(msgPfx, ":  ");

    if (memcmp(&testGst, &baseGst, sizeof(struct gameState)) == 0)
    {
		assertCondition = 1;  
    }
         
    else
    {
		assertCondition = 0;
		sprintf(msgSfx, "Game State has changed after running test.");
		strcat(msgPfx, msgSfx);
		strcpy(failMsg, msgPfx);
		result = -1;
    } 
                
    assertMsg(assertCondition, passMsg, failMsg);

    if (result == 0)
    {
        printf(passMsg2);
        printf("%d\n", testNum);
    }


	/************************************************************************/
    // Final Result Message
	
    if (result == 0)
    {
        printf(" >>>>>  SUCCESS: Testing Complete for function %s  All Tests Passed.  <<<<<\n", TESTFUNCTIONNAME);
    }
                        
    else
    {
		printf(" ******* Testing Complete for function %s  There were one or more Failed Tests. *******\n", TESTFUNCTIONNAME);
    }
    
    printf("\n");
	return result;
}


/************************************************************************/ 

/************************************************************************/

/*************************************************************************
 ** Function:           main() method for unittest4 program
 ** 
 ** Description:    main() method for program to unit test the 
 **                 isGameOver function from dominion.c
 ** Parameters:     none
 ** Return Value:   0 - conventional for success of int main() method
 ************************************************************************/
 
int main(int argc, char *argv[])
{
    testIsGameOver();
    return 0;
}
