/* CS 362 Assignment 3 */
/*************************************************************************
 ** Author:                  Michael Tucker
 ** Date Created:            4/24/2018
 ** Last Modification Date:  4/29/2018
 ** Filename:                unittest3.c
 ** 
 ** Overview:  This program implements a Unit Test Suite for testing the
 **            discardCard function from the dominion.c file. The 
 **            dominion.c file implements a Dominion card game. The test 
 **            suite includes tests for the effect the function has on 
 **            the elements of the Game State as well as the performance
 **            of the function over a range of input arguments.
 **			   The Unit tests include:
 **			   TEST 1: Both trashFlag values, 5 cards hands, and last 
 **					   card in hand played
 ** 		   TEST 2: Both trashFlag values, 5 cards hands, and first 
 **					   or third card in hand played
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

#define TESTFUNCTIONNAME "discardCard()"
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
        printf("PASSED: %s\n", trueMsg);
    }
    
    else
    {
        printf("FAILED: %s\n", falseMsg);
    }  
}


/*************************************************************************
 ** Function:                assertMsgDC
 ** 
 ** Description:    Function to compare the actual value of the test 
 **                 result produced by a unit subtest to the expected 
 **                 value. If the test fails, a FAIL message and failure 
 **                 results for the test are output. The test inputs
 **                 are specific to the tests run on discardCard function.
 ************************************************************************/

int assertMsgDC(int player, int trashFlag, int handPos, char* pileLabel, char* subTestLabel, int testNum, int actualVal, int expectedVal)
{
    char failMsg[128];
    char tempStr[128];
  
    int resultVal = 0;

    if (actualVal != expectedVal)
    {
        strcpy(failMsg, "FAILED. Test");
		sprintf(tempStr, "%d: P: %d TF: %d C: %d, %s, %s:  ", testNum, player, trashFlag, handPos, pileLabel, subTestLabel);
		strcat(failMsg, tempStr);
		sprintf(tempStr, "actual: %d != expected: %d\n", actualVal, expectedVal);
		strcat(failMsg, tempStr);
        printf(failMsg);
        resultVal = -1;
    }

    return resultVal;
}

 
/************************************************************************/

// discardCard() function from dominion.c
/*
int discardCard(int handPos, int currentPlayer, struct gameState *state, int trashFlag)
{
	
  //if card is not trashed, added to Played pile 
  if (trashFlag < 1)
  {
      //add card to played pile
      state->playedCards[state->playedCardCount] = state->hand[currentPlayer][handPos]; 
      state->playedCardCount++;
  }
	
  //set played card to -1
  state->hand[currentPlayer][handPos] = -1;
	
  //remove card from player's hand
  if ( handPos == (state->handCount[currentPlayer] - 1) ) 	//last card in hand array is played
  {
      //reduce number of cards in hand
      state->handCount[currentPlayer]--;
  }
  else if ( state->handCount[currentPlayer] == 1 ) //only one card in hand
  {
      //reduce number of cards in hand
      state->handCount[currentPlayer]--;
  }
  else 	
  {
      //replace discarded card with last card in hand
      state->hand[currentPlayer][handPos] = state->hand[currentPlayer][ (state->handCount[currentPlayer] - 1)];
      //set last card to -1
      state->hand[currentPlayer][state->handCount[currentPlayer] - 1] = -1;
      //reduce number of cards in hand
      state->handCount[currentPlayer]--;
  }
	
  return 0;
}
*/ 

 
/*************************************************************************
 ** Function:                testDiscardCard
 ** 
 ** Description:    Function to implement the Unit Tests for testing 
 **                 the discardCard() function in dominion.c
 ************************************************************************/
 
int testDiscardCard()
{
    char msgPfx[128];
    char passMsg[128];
    char failMsg[128];
    char passMsg2[128];

    char handLabel[64];
    char deckLabel[64];
    char discardLabel[64];
	char playedCardsLabel[64];
    char retValLabel[64];
    char countTestLabel[64];
    char cardTestLabel[64];
    char retValTestLabel[64];

    int i;
    int testNum;
	int result = 0;
	int actualVal;
    int expectedVal;
    int assertRetVal; 
	
	int numPlayers = 2;
    int randSeed = 1000;
    
	int player, handPos, trashFlag;
    int discardCount = 0; 
				 
	int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
				 // Kingdom Card numbers: 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
				 // Victory Card numbers: 0, 1, 2, 3
				 // Treasure Card numbers: 4, 5, 6
    
    struct gameState baseGst, testGst, initialGst, tempGst;
	
    strcpy(handLabel, "hand");
    strcpy(deckLabel, "deck");
    strcpy(discardLabel, "discard");
	strcpy(playedCardsLabel, "playedCards");
    strcpy(countTestLabel, "count test");
    strcpy(cardTestLabel, "card test");
    strcpy(retValLabel, "retVal");
    strcpy(retValTestLabel, "return value test");
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
	
	// ----------- TEST 1: Both trashFlag values, 5 cards hands, and last card in hand played --------------
	
	strcpy(msgPfx, "TEST 1: Both trashFlag values, 5 card hands, and last card in hand played");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");
    strcpy(passMsg, "TEST 1");
    strcpy(failMsg, "N/A");

    testNum = 1;
	
	
	// Initialize hand and deck for second player (index 1)
	
	testGst.hand[1][0] = 1;
	testGst.hand[1][1] = 4;
	testGst.hand[1][2] = 7;
	testGst.hand[1][3] = 8;
	testGst.hand[1][4] = 13;
	
	testGst.handCount[1] = 5;
	
	for (i = 5; i < 10; i++)
	{
		testGst.deck[1][i] = -1;
	}
	
	testGst.deckCount[1] = 5;
	
	// Copy the changed test game state to base case game state for later comparison
	memcpy(&baseGst, &testGst, sizeof(struct gameState));

	
	// Run the Test
    
	for (player = 0; player < numPlayers; player++)
    {
		for (trashFlag = 0; trashFlag < 2; trashFlag++)	// check each trashFlag 0, 1
		{
			for (handPos = 4; handPos >= 0; handPos--)
			{
				strcpy(msgPfx, "TEST 1: Both trashFlag values, 5 card hands, and last card in hand played");
				strcat(msgPfx, ":  ");

				// Call the discardCard function for each input combination
				discardCard(handPos, player, &testGst, trashFlag);
				discardCount++;

				
				/************************************************************************/
				
				// If card is not trashed, added to Played pile. trashFlag = 0
				// If trashFlag = 1, card is trashed, effectively removed from the current game
				
				if (trashFlag < 1)
				{
					// Card is not trashed, and added to playedCards pile
					
					// Test: Card in playedCards pile is same as previous card in hand at handPos
					actualVal = testGst.playedCards[testGst.playedCardCount - 1]; 
					expectedVal = baseGst.hand[player][handPos];
					assertRetVal = assertMsgDC(player, trashFlag, handPos, playedCardsLabel, cardTestLabel, testNum, actualVal, expectedVal);
					if (assertRetVal == -1)
					{
						result = assertRetVal;
					}

					// Test: playedCardCount increased by 1
					actualVal = testGst.playedCardCount; 
					expectedVal = baseGst.playedCardCount + discardCount;
					assertRetVal = assertMsgDC(player, trashFlag, handPos, playedCardsLabel, countTestLabel, testNum, actualVal, expectedVal);
					if (assertRetVal == -1)
					{
						result = assertRetVal;
					}
					
					// Test: discardCount increased by 1
					actualVal = testGst.discardCount[player]; 
					expectedVal = baseGst.discardCount[player] + discardCount;
					assertRetVal = assertMsgDC(player, trashFlag, handPos, discardLabel, countTestLabel, testNum, actualVal, expectedVal);
					if (assertRetVal == -1)
					{
						result = assertRetVal;
					}
				}
				
				else  // trashFlag == 1, so card is trashed
				{
					// Test: playedCardCount is the same as before
					actualVal = testGst.playedCardCount;
					expectedVal = baseGst.playedCardCount;
					assertRetVal = assertMsgDC(player, trashFlag, handPos, playedCardsLabel, countTestLabel, testNum, actualVal, expectedVal);
					if (assertRetVal == -1)
					{
						result = assertRetVal;
					}

					// Test: discardCount is the same as before
					actualVal = testGst.discardCount[player]; 
					expectedVal = baseGst.discardCount[player];
					assertRetVal = assertMsgDC(player, trashFlag, handPos, discardLabel, countTestLabel, testNum, actualVal, expectedVal);
					if (assertRetVal == -1)
					{
						result = assertRetVal;
					}					
				}
				
				
				// Test: Card in hand at handPos is now set to -1
				actualVal = testGst.hand[player][handPos];
				expectedVal = -1;
				assertRetVal = assertMsgDC(player, trashFlag, handPos, handLabel, cardTestLabel, testNum, actualVal, expectedVal);
				if (assertRetVal == -1)
				{
					result = assertRetVal;
				}
				
				// Test: handCount decreased by 1
				actualVal = testGst.handCount[player];
				expectedVal = baseGst.handCount[player] - discardCount;
				assertRetVal = assertMsgDC(player, trashFlag, handPos, handLabel, countTestLabel, testNum, actualVal, expectedVal);
				if (assertRetVal == -1)
				{
					result = assertRetVal;
				}
			}	
			
			// Reset the test game state
			memcpy(&testGst, &baseGst, sizeof(struct gameState));
		    discardCount = 0;	
		}		
	}
    
    if (result == 0)
    {
        printf(passMsg2);
        printf("%d\n", testNum);
    }


	/************************************************************************/
	
	// ----------- TEST 2: Both trashFlag values, 5 cards hands, and first or third card in hand played --------------

	strcpy(msgPfx, "TEST 2: Both trashFlag values, 5 cards hands, and first or third card in hand played");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 2");
    strcpy(failMsg, "N/A");

    testNum = 2;
	
	
	// Initialize hand and deck for second player (index 1)

	testGst.hand[1][0] = 1;
	testGst.hand[1][1] = 4;
	testGst.hand[1][2] = 7;
	testGst.hand[1][3] = 8;
	testGst.hand[1][4] = 13;
	
	testGst.handCount[1] = 5;
	
	for (i = 5; i < 10; i++)
	{
		testGst.deck[1][i] = -1;
	}
	
	testGst.deckCount[1] = 5;
	
	// Copy the changed test game state to base case game state for later comparison
	memcpy(&baseGst, &testGst, sizeof(struct gameState));

	
	// Run the Test
    
	for (player = 0; player < numPlayers; player++)
    {
		for (trashFlag = 0; trashFlag < 2; trashFlag++)	// Check each trashFlag 0, 1
		{
			for (i = 0; i < 5; i++)  // Iterate through the 5 cards in the hand
			{
				// Make sure handPos is not the last card in hand (last index)
                if (i < 2)
				{
					handPos = 2;
				}
				
				else
				{
					handPos = 0;
				}
                
                // The hand changes with each iteration compared to baseGst, so need 
                // an updated game state tempGst for comparison
	            memcpy(&tempGst, &testGst, sizeof(struct gameState));
				
				strcpy(msgPfx, "TEST 2: Both trashFlag values, 5 cards hands, and first or third card in hand played");
				strcat(msgPfx, ":  ");

				// Call the discardCard function for each input combination
				discardCard(handPos, player, &testGst, trashFlag);
				discardCount++;

				/************************************************************************/
				
				// if card is not trashed, added to Played pile. trashFlag = 0
				// If trashFlag = 1, card is trashed, effectively removing it from the current game
	
				if (trashFlag < 1)
				{
					// Card is not trashed, and added to playedCards pile
					
					// Test: Card in playedCards pile is same as previous card in hand at handPos
					actualVal = testGst.playedCards[testGst.playedCardCount - 1]; 
					expectedVal = tempGst.hand[player][handPos];
					assertRetVal = assertMsgDC(player, trashFlag, handPos, playedCardsLabel, cardTestLabel, testNum, actualVal, expectedVal);
					if (assertRetVal == -1)
					{
						result = assertRetVal;
					}

					// Test: playedCardCount increased by 1
					actualVal = testGst.playedCardCount; 
					expectedVal = baseGst.playedCardCount + discardCount;
					assertRetVal = assertMsgDC(player, trashFlag, handPos, playedCardsLabel, countTestLabel, testNum, actualVal, expectedVal);
					if (assertRetVal == -1)
					{
						result = assertRetVal;
					}
					
					// Test: discardCount increased by 1
					actualVal = testGst.discardCount[player]; 
					expectedVal = baseGst.discardCount[player] + discardCount;
					assertRetVal = assertMsgDC(player, trashFlag, handPos, discardLabel, countTestLabel, testNum, actualVal, expectedVal);
					if (assertRetVal == -1)
					{
						result = assertRetVal;
					}
				}
				
				else  // trashFlag == 1, so card is trashed
				{
					// Test: playedCardCount is same as before
					actualVal = testGst.playedCardCount;
					expectedVal = baseGst.playedCardCount;
					assertRetVal = assertMsgDC(player, trashFlag, handPos, playedCardsLabel, countTestLabel, testNum, actualVal, expectedVal);
					if (assertRetVal == -1)
					{
						result = assertRetVal;
					}	
					
					// Test: discardCount is the same as before
					actualVal = testGst.discardCount[player]; 
					expectedVal = baseGst.discardCount[player];
					assertRetVal = assertMsgDC(player, trashFlag, handPos, discardLabel, countTestLabel, testNum, actualVal, expectedVal);
					if (assertRetVal == -1)
					{
						result = assertRetVal;
					}	
				}
				
				// Test: Previous last card in hand before discard is now set to -1
				actualVal = testGst.hand[player][baseGst.handCount[player] - 1];
				expectedVal = -1;
				assertRetVal = assertMsgDC(player, trashFlag, handPos, handLabel, cardTestLabel, testNum, actualVal, expectedVal);
				if (assertRetVal == -1)
				{
					result = assertRetVal;
				}
				
				// Test: Card in hand at handPos is now set to previous last card in hand
                // However, if this was the only card in hand, the card at handPos will
                // be set to -1.
				actualVal = testGst.hand[player][handPos];
                if (testGst.handCount[player] == 0)
                {
                    expectedVal = -1;
                }

                else
                {
				    expectedVal = tempGst.hand[player][tempGst.handCount[player] - 1];
                }

				assertRetVal = assertMsgDC(player, trashFlag, handPos, handLabel, cardTestLabel, testNum, actualVal, expectedVal);
				if (assertRetVal == -1)
				{
					result = assertRetVal;
				}
								
				// Test: handCount decreased by 1
				actualVal = testGst.handCount[player];
				expectedVal = baseGst.handCount[player] - discardCount;
				assertRetVal = assertMsgDC(player, trashFlag, handPos, handLabel, countTestLabel, testNum, actualVal, expectedVal);
				if (assertRetVal == -1)
				{
					result = assertRetVal;
				}
			}	
			
			// Reset the test game state
			memcpy(&testGst, &baseGst, sizeof(struct gameState));
		    discardCount = 0;
		}		
	}

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
 ** Function:           main() method for unittest3 program
 ** 
 ** Description:    main() method for program to unit test the 
 **                 discardCard function from dominion.c
 ** Parameters:     none
 ** Return Value:   0 - conventional for success of int main() method
 ************************************************************************/
 
int main(int argc, char *argv[])
{
    testDiscardCard();
    return 0;
}
