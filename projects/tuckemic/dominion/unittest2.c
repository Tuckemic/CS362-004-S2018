/* CS 362 Assignment 3 */
/*************************************************************************
 ** Author:                  Michael Tucker
 ** Date Created:            4/24/2018
 ** Last Modification Date:  4/29/2018
 ** Filename:                unittest2.c
 ** 
** Overview:  This program implements a Unit Test Suite for testing the
 **            gainCard function from the dominion.c file. The 
 **            dominion.c file implements a Dominion card game. The test 
 **            suite includes tests for the effect the function has on 
 **            the elements of the Game State as well as the performance
 **            of the function over a range of input arguments.
 **			   The Unit tests include:
 **			   TEST 1: All possible toFlag values for all cards available 
 **					   in supply piles
 ** 		   TEST 2: All supply piles are empty
 **			   TEST 3: Select cards not available in current game
 ** Input:   None.  The program executes and calls the function from the
 **          dominion.c file, which includes code under test. 
 ** Output:  A new file is created and appended, unittestresults.out
 **          which includes all unit test and coverage results.
 ************************************************************************/


#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include "interface.c"

#include <stdio.h>
#include <string.h>

#define TESTFUNCTIONNAME "gainCard()"
#define NUMCARDOPTIONS 17
#define NUMTOFLAGS 3
 
 
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
 ** Function:                assertMsgGc
 ** 
 ** Description:    Function to compare the actual value of the test 
 **                 result produced by a unit subtest to the expected 
 **                 value. If the test fails, a FAIL message and failure 
 **                 results for the test are output. The test inputs
 **                 are specific to the tests run on the gainCard 
 **					function.
 ************************************************************************/
 
int assertMsgGC(int player, int toFlag, int card, char* pileLabel, char* subTestLabel, int testNum, int actualVal, int expectedVal)
{
    char failMsg[128];
    char tempStr[128];
  
    int resultVal = 0;

    if (actualVal != expectedVal)
    {
        strcpy(failMsg, "FAILED. Test");
		sprintf(tempStr, "%d: P: %d TF: %d C: %d, %s, %s:  ", testNum, player, toFlag, card, pileLabel, subTestLabel);
		strcat(failMsg, tempStr);
		sprintf(tempStr, "actual: %d != expected: %d\n", actualVal, expectedVal);
		strcat(failMsg, tempStr);
        printf(failMsg);
        resultVal = -1;
    }

    return resultVal;
}

 
/************************************************************************/

// gainCard() function from dominion.c
/*
int gainCard(int supplyPos, struct gameState *state, int toFlag, int player)
{
  //Note: supplyPos is enum of choosen card
	
  //check if supply pile is empty (0) or card is not used in game (-1)
  if ( supplyCount(supplyPos, state) < 1 )
    {
      return -1;
    }
	
  //added card for [whoseTurn] current player:
  // toFlag = 0 : add to discard
  // toFlag = 1 : add to deck
  // toFlag = 2 : add to hand

  if (toFlag == 1)
    {
      state->deck[ player ][ state->deckCount[player] ] = supplyPos;
      state->deckCount[player]++;
    }
  else if (toFlag == 2)
    {
      state->hand[ player ][ state->handCount[player] ] = supplyPos;
      state->handCount[player]++;
    }
  else
    {
      state->discard[player][ state->discardCount[player] ] = supplyPos;
      state->discardCount[player]++;
    }
	
  //decrease number in supply pile
  state->supplyCount[supplyPos]--;
	 
  return 0;
}

int supplyCount(int card, struct gameState *state) 
{
  return state->supplyCount[card];
}
*/

 
/*************************************************************************
 ** Function:                testGainCard
 ** 
 ** Description:    Function to implement the Unit Tests for testing 
 **                 the gainCard() function in dominion.c
 ************************************************************************/
 
int testGainCard()
{
    char msgPfx[128];
    char msgSfx[128];
    char passMsg[128];
    char failMsg[128];
    char passMsg2[128];
    
    char handLabel[64];
    char deckLabel[64];
    char discardLabel[64];
    char supplyLabel[64];
    char retValLabel[64];
    char countTestLabel[64];
    char cardTestLabel[64];
    char supplyTestLabel[64];
    char retValTestLabel[64];

    int testNum;
	int result = 0;
    int retVal;
	int actualVal;
    int expectedVal;
    int assertRetVal; 
    int assertCondition = 0;
	
	int numPlayers = 2;
    int randSeed = 1000;
    
	int player, card, toFlag;
    int gainCount = 0; 
				 
	int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
				 // Kingdom Card numbers: 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
				 // Victory Card numbers: 0, 1, 2, 3
				 // Treasure Card numbers: 4, 5, 6
    
    struct gameState baseGst, testGst, initialGst;
	
    strcpy(handLabel, "hand");
    strcpy(deckLabel, "deck");
    strcpy(discardLabel, "discard");
    strcpy(countTestLabel, "count test");
    strcpy(cardTestLabel, "card test");
    strcpy(supplyLabel, "supply");
    strcpy(supplyTestLabel, "supply test");
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
	
	// ----------- TEST 1: All possible toFlag values for all cards available in supply piles --------------
	
	strcpy(msgPfx, "TEST 1: All possible toFlag values for all cards available in supply piles");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 1");
    strcpy(failMsg, "N/A");

    testNum = 1;

	
	// Run the Test
    
	for (player = 0; player < numPlayers; player++)
    {
		for (toFlag = 0; toFlag < NUMTOFLAGS; toFlag++)	// check each toFlag 0, 1, 2
		{
			
			for (card = 0; card < NUMCARDOPTIONS; card++) // check all cards used in current game 0 - 16
			{
				strcpy(msgPfx, "TEST 1: All possible toFlag values for all cards available in supply piles");
				strcat(msgPfx, ":  ");
				
				// Call the gainCard function for each input combination
				retVal = gainCard(card, &testGst, toFlag, player);
				gainCount++;

				/************************************************************************/
				
                // Test for expected return value from gainCard()
                // In this case, it should be 0.
                              
                actualVal = retVal; 
                expectedVal = 0;
                assertRetVal = assertMsgGC(player, toFlag, card, retValLabel, retValTestLabel, testNum, actualVal, expectedVal);
                if (assertRetVal == -1)
                {
                    result = assertRetVal;
                }

				/************************************************************************/
				
                // Test supply pile count for card gained
               
                actualVal = testGst.supplyCount[card];
                expectedVal = baseGst.supplyCount[card] - 1;
                assertRetVal = assertMsgGC(player, toFlag, card, supplyLabel, supplyTestLabel, testNum, actualVal, expectedVal);
                if (assertRetVal == -1)
                {
                    result = assertRetVal;
                }

				/************************************************************************/


                // Tests related to toFlag = 1
				// toFlag = 1 : add to deck

				if (toFlag == 1)
				{
					
					// Tests: deckCount for player passed in is incremented by 1 from before
					//        new card added to deck at position new deckCount - 1
                    actualVal = testGst.deckCount[player];
                    expectedVal = baseGst.deckCount[player] + gainCount;
                    assertRetVal = assertMsgGC(player, toFlag, card, deckLabel, countTestLabel, testNum, actualVal, expectedVal);
                    if (assertRetVal == -1)
                    {
                        result = assertRetVal;
                    }

					/************************************************************************/
					
                    actualVal = testGst.deck[player][testGst.deckCount[player] - 1];
				    expectedVal = card;	
                     assertRetVal = assertMsgGC(player, toFlag, card, deckLabel, cardTestLabel, testNum, actualVal, expectedVal);
                    if (assertRetVal == -1)
                    {
                        result = assertRetVal;
                    }

					/************************************************************************/

					// Hand and Discard should not change
                    
                    // Hand -- Testing handCount
                    actualVal = testGst.handCount[player];
                    expectedVal = baseGst.handCount[player];
                    assertRetVal = assertMsgGC(player, toFlag, card, handLabel, countTestLabel, testNum, actualVal, expectedVal);
                    if (assertRetVal == -1)
                    {
                        result = assertRetVal;
                    }
					
					/************************************************************************/
					
                    // Hand -- Testing hand card absence 
                    actualVal = testGst.hand[player][testGst.handCount[player] - 1];
                    expectedVal = baseGst.hand[player][baseGst.handCount[player] - 1];
                     assertRetVal = assertMsgGC(player, toFlag, card, handLabel, cardTestLabel, testNum, actualVal, expectedVal);
                    if (assertRetVal == -1)
                    {
                        result = assertRetVal;
                    }
		
					/************************************************************************/
					
                    // Discard -- Testing discardCount
                    actualVal = testGst.discardCount[player];
                    expectedVal = baseGst.discardCount[player];
                    assertRetVal = assertMsgGC(player, toFlag, card, discardLabel, countTestLabel, testNum, actualVal, expectedVal);
                    if (assertRetVal == -1)
                    {
                        result = assertRetVal;
                    }
					
                    /************************************************************************/
					
                    // Discard -- Testing discard card absence
                    actualVal = testGst.discard[player][testGst.discardCount[player] - 1];
                    expectedVal = baseGst.discard[player][baseGst.discardCount[player] - 1];
                    assertRetVal = assertMsgGC(player, toFlag, card, discardLabel, cardTestLabel, testNum, actualVal, expectedVal);
                    if (assertRetVal == -1)
                    {
                        result = assertRetVal;
                    }
				}
				
				/************************************************************************/
				
				
				// Tests related to toFlag = 2
				// toFlag = 2 : add to hand

				else if (toFlag == 2)
				{
					// Tests: handCount for player passed in is incremented by 1 from before
					//        new card added to hand at position new handCount - 1
					
					// Hand -- Testing handCount
                    actualVal = testGst.handCount[player];
                    expectedVal = baseGst.handCount[player] + gainCount;
                    assertRetVal = assertMsgGC(player, toFlag, card, handLabel, countTestLabel, testNum, actualVal, expectedVal);
                    if (assertRetVal == -1)
                    {
                        result = assertRetVal;
                    }
					
					/************************************************************************/
					
				    // Hand -- Testing hand card presence 
                    actualVal = testGst.hand[player][testGst.handCount[player] - 1];
				    expectedVal = card;	
                    assertRetVal = assertMsgGC(player, toFlag, card, handLabel, cardTestLabel, testNum, actualVal, expectedVal);
                    if (assertRetVal == -1)
                    {
                        result = assertRetVal;
                    }

					/************************************************************************/	

					// Deck and Discard should not change
                    
                    // Deck -- Testing deckCount
                    actualVal = testGst.deckCount[player];
                    expectedVal = baseGst.deckCount[player];
                    assertRetVal = assertMsgGC(player, toFlag, card, deckLabel, countTestLabel, testNum, actualVal, expectedVal);
                    if (assertRetVal == -1)
                    {
                        result = assertRetVal;
                    }
					
					/************************************************************************/
                    
					// Deck -- Testing deck card absence 
                    actualVal = testGst.deck[player][testGst.deckCount[player] - 1];
                    expectedVal = baseGst.deck[player][baseGst.deckCount[player] - 1];
                    assertRetVal = assertMsgGC(player, toFlag, card, deckLabel, cardTestLabel, testNum, actualVal, expectedVal);
                    if (assertRetVal == -1)
                    {
                        result = assertRetVal;
                    }
		
					/************************************************************************/
					
                    // Discard -- Testing discardCount
                    actualVal = testGst.discardCount[player];
                    expectedVal = baseGst.discardCount[player];
                    assertRetVal = assertMsgGC(player, toFlag, card, discardLabel, countTestLabel, testNum, actualVal, expectedVal);
                    if (assertRetVal == -1)
                    {
                        result = assertRetVal;
                    }
                    
					/************************************************************************/
					
                    // Discard -- Testing discard card absence
                    actualVal = testGst.discard[player][testGst.discardCount[player] - 1];
                    expectedVal = baseGst.discard[player][baseGst.discardCount[player] - 1];
                    assertRetVal = assertMsgGC(player, toFlag, card, discardLabel, cardTestLabel, testNum, actualVal, expectedVal);
                    if (assertRetVal == -1)
                    {
                        result = assertRetVal;
                    }
				}
				
				/************************************************************************/

				
				// Tests related to toFlag = 0
				// toFlag = 0 : add to discard

				else  // toFlag == 0
				{
					// Tests: discardCount for player passed in is incremented by 1 from before
					//        new card added to discard at position new discardCount - 1
				
					// Discard -- Testing discardCount
                    actualVal = testGst.discardCount[player];
                    expectedVal = baseGst.discardCount[player] + gainCount;
                    assertRetVal = assertMsgGC(player, toFlag, card, discardLabel, countTestLabel, testNum, actualVal, expectedVal);
                    if (assertRetVal == -1)
                    {
                        result = assertRetVal;
                    }
					
					/************************************************************************/
					
                    actualVal = testGst.discard[player][testGst.discardCount[player] - 1];
				    expectedVal = card;	
                    assertRetVal = assertMsgGC(player, toFlag, card, discardLabel, cardTestLabel, testNum, actualVal, expectedVal);
                    if (assertRetVal == -1)
                    {
                        result = assertRetVal;
                    }

					/************************************************************************/

					// Deck and Hand should not change
                    
                    // Deck -- Testing deckCount
                    actualVal = testGst.deckCount[player];
                    expectedVal = baseGst.deckCount[player];
                    assertRetVal = assertMsgGC(player, toFlag, card, deckLabel, countTestLabel, testNum, actualVal, expectedVal);
                    if (assertRetVal == -1)
                    {
                        result = assertRetVal;
                    }
					
					/************************************************************************/
					
                    // Deck -- Testing deck card absence 
                    actualVal = testGst.deck[player][testGst.deckCount[player] - 1];
                    expectedVal = baseGst.deck[player][baseGst.deckCount[player] - 1];
                    assertRetVal = assertMsgGC(player, toFlag, card, deckLabel, cardTestLabel, testNum, actualVal, expectedVal);
                    if (assertRetVal == -1)
                    {
                        result = assertRetVal;
                    }
		
					/************************************************************************/
					
                    // Hand -- Testing handCount
                    actualVal = testGst.handCount[player];
                    expectedVal = baseGst.handCount[player];
                    assertRetVal = assertMsgGC(player, toFlag, card, handLabel, countTestLabel, testNum, actualVal, expectedVal);
                    if (assertRetVal == -1)
                    {
                        result = assertRetVal;
                    }
					
                    /************************************************************************/
					
                    // Hand -- Testing hand card absence
                    actualVal = testGst.hand[player][testGst.handCount[player] - 1];
                    expectedVal = baseGst.hand[player][baseGst.handCount[player] - 1];
                    assertRetVal = assertMsgGC(player, toFlag, card, handLabel, cardTestLabel, testNum, actualVal, expectedVal);
                    if (assertRetVal == -1)
                    {
                        result = assertRetVal;
                    }
				}
			}

            // Reset values for next toFlag iteration
            gainCount = 0;
		    memcpy(&testGst, &initialGst, sizeof(struct gameState));
		}
	}

    if (result == 0)
    {
        printf(passMsg2);
        printf("%d\n", testNum);
    }


	/************************************************************************/
	
	// ----------- TEST 2: All supply piles are empty --------------
	
	strcpy(msgPfx, "TEST 2: All supply piles are empty");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 2");
    strcpy(failMsg, "N/A");

    testNum = 2;
	
	// Reset the base case and a test case game states to initial values
	memcpy(&baseGst, &initialGst, sizeof(struct gameState));
	memcpy(&testGst, &initialGst, sizeof(struct gameState));


    // Initialize all supply piles to empty for test game state
    memset(testGst.supplyCount, 0, sizeof testGst.supplyCount);

    // Copy changed testGst to baseGst for later comparison
	memcpy(&baseGst, &testGst, sizeof(struct gameState));


	// Run the Test
    
	for (player = 0; player < numPlayers; player++)
    {
		for (toFlag = 0; toFlag < NUMTOFLAGS; toFlag++)	// check each toFlag 0, 1, 2
		{
			
			for (card = 0; card < NUMCARDOPTIONS; card++) // check all cards used in current game 0 - 16
			{
				strcpy(msgPfx, "TEST 2: All supply piles are empty");
				strcat(msgPfx, ":  ");

				// Call the gainCard function for each input combination
				retVal = gainCard(card, &testGst, toFlag, player);


				/************************************************************************/
				
                // Test for expected return value from gainCard()
                // In this case, it should be -1.
                              
                actualVal = retVal; 
                expectedVal = -1;
                assertRetVal = assertMsgGC(player, toFlag, card, retValLabel, retValTestLabel, testNum, actualVal, expectedVal);
                if (assertRetVal == -1)
                {
                    result = assertRetVal;
                }

				/************************************************************************/
				
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
                    sprintf(msgSfx, "Game State has changed after running test. player: %d  toFlag: %d  card: %d", player, toFlag, card);
                    strcat(msgPfx, msgSfx);
                    strcpy(failMsg, msgPfx);
                    result = -1;
                } 
                
                assertMsg(assertCondition, passMsg, failMsg);
            }
        }
    }

    if (result == 0)
    {
        printf(passMsg2);
        printf("%d\n", testNum);
    }


	/************************************************************************/
	
	// ----------- TEST 3: Select cards not available in current game --------------
	
	strcpy(msgPfx, "TEST 3: Select cards not available in current game");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 3");
    strcpy(failMsg, "N/A");

    testNum = 3;
	
	// Reset the base case and a test case game states to initial values
	memcpy(&baseGst, &initialGst, sizeof(struct gameState));
	memcpy(&testGst, &initialGst, sizeof(struct gameState));


	// Run the Test
    
	for (player = 0; player < numPlayers; player++)
    {
		for (toFlag = 0; toFlag < NUMTOFLAGS; toFlag++)	// check each toFlag 0, 1, 2
		{
			for (card = 17; card < 27; card++) // check all cards not used in current game 17 - 26 
            {
				strcpy(msgPfx, "TEST 3: Select cards not available in current game");
				strcat(msgPfx, ":  ");

				// Call the gainCard function for each input combination
				retVal = gainCard(card, &testGst, toFlag, player);


				/************************************************************************/
				
                // Test for expected return value from gainCard()
                // In this case, it should be -1.
                              
                actualVal = retVal; 
                expectedVal = -1;
                assertRetVal = assertMsgGC(player, toFlag, card, retValLabel, retValTestLabel, testNum, actualVal, expectedVal);
                if (assertRetVal == -1)
                {
                    result = assertRetVal;
                }

				/************************************************************************/
				
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
                    sprintf(msgSfx, "Game State has changed after running test. player: %d  toFlag: %d  card: %d", player, toFlag, card);
                    strcat(msgPfx, msgSfx);
                    strcpy(failMsg, msgPfx);
                    result = -1;
                } 
                
                assertMsg(assertCondition, passMsg, failMsg);
            }
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
 ** Function:           main() method for unittest2 program
 ** 
 ** Description:    main() method for program to unit test the 
 **                 gainCard function from dominion.c
 ** Parameters:     none
 ** Return Value:   0 - conventional for success of int main() method
 ************************************************************************/
 
int main(int argc, char *argv[])
{
    testGainCard();
    return 0;
}
