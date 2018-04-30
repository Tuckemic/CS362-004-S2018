/* CS 362 Assignment 3 */
/*************************************************************************
 ** Author:                  Michael Tucker
 ** Date Created:            4/24/2018
 ** Last Modification Date:  4/29/2018
 ** Filename:                unittest1.c
 ** 
 ** Overview:  This program implements a Unit Test Suite for testing the
 **            fullDeckCount function from the dominion.c file. The 
 **            dominion.c file implements a Dominion card game. The test 
 **            suite includes tests for the effect the function has on 
 **            the elements of the Game State as well as the performance
 **            of the function over a range of input arguments.
 **			   The Unit tests include:
 **			   TEST 1: Deck, Hand, and Discard all have cards
 ** 		   TEST 2: Deck, Hand, and Discard all have 0 cards
 **			   TEST 3: Hand and Discard have cards, Deck has 0 cards
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

#define TESTFUNCTIONNAME "fullDeckCount()"
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

 
/************************************************************************/

// fullDeckCount() function from dominion.c
/*
int fullDeckCount(int player, int card, struct gameState *state) 
{
  int i;
  int count = 0;

  for (i = 0; i < state->deckCount[player]; i++)
    {
      if (state->deck[player][i] == card) count++;
    }

  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == card) count++;
    }

  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == card) count++;
    }

  return count;
}
*/ 

 
/*************************************************************************
 ** Function:                testFullDeckCount
 ** 
 ** Description:    Function to implement the Unit Tests for testing 
 **                 the fullDeckCount() function in dominion.c
 ************************************************************************/
 
int testFullDeckCount()
{
    char msgPfx[128];
    char msgSfx[128];
    char passMsg[128];
    char failMsg[128];
    char passMsg2[128];

	int result = 0;
	int assertCondition = 0;
	
	int numPlayers = 2;
    int randSeed = 1000;
    
	int currPlayer = 0;
	int player, card;

	int startCard = 0;
	int testCount = 0;
    int testNum;

    int expectedCounts[NUMCARDOPTIONS] = {0};
				 
	int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
				 // Kingdom Card numbers: 7, 8, 9, 10, 11, 12, 13, 14, 15, 16
				 // Victory Card numbers: 0, 1, 2, 3
				 // Treasure Card numbers: 4, 5, 6
    
    struct gameState baseGst, testGst, initialGst;
	
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
	
	// ----------- TEST 1: Deck, Hand, and Discard all have cards --------------
	
	strcpy(msgPfx, "TEST 1: Deck, Hand, and Discard all have cards");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");
    strcpy(passMsg, "TEST 1");
    strcpy(failMsg, "N/A");

    testNum = 1;
	
	// Initialize hand, deck, and discard for currPlayer
    // Also set values in expectedCounts array based on initializations 
	currPlayer = 0;	
    
    // Deck
	startCard = 0;	// Victory cards start at 0
	for (card = startCard; card < NUMCARDOPTIONS; card++)
	{
		testGst.deck[currPlayer][card - startCard] = card;
        expectedCounts[card] += 1;
	}
	
	testGst.deckCount[currPlayer] = NUMCARDOPTIONS - startCard;
	
	
	// Hand
	startCard = 4;	// Province card. Victory cards start at 0
	for (card = startCard; card < testGst.handCount[currPlayer] + startCard; card++)
	{
		testGst.hand[currPlayer][card - startCard] = card;
        expectedCounts[card] += 1;
	}	

	
	// Discard
	startCard = 6;	// Victory cards start at 0
	for (card = startCard; card < NUMCARDOPTIONS; card++)
	{
		testGst.discard[currPlayer][card - startCard] = card;
        expectedCounts[card] += 1; 
	}
	
	testGst.discardCount[currPlayer] = NUMCARDOPTIONS - startCard;

	// Copy the changed test game state to base case game state for later comparison
	memcpy(&baseGst, &testGst, sizeof(struct gameState));
	
    
	// Run the Test
    
	for (player = 0; player < numPlayers; player++)
    {
        for (card = 0; card < NUMCARDOPTIONS; card++) // check counts for all cards 0 - 16
		{
	        strcpy(msgPfx, "TEST 1: Deck, Hand, and Discard all have cards");
            strcat(msgPfx, ":  ");

			// Call the fullDeckCount function for each input combination
			testCount = fullDeckCount(player, card, &testGst);

			
            // Test: Compare testCount returned by function to expected count for the card.
			
	        if (testCount == expectedCounts[card])
            {
                assertCondition = 1;
            }

            else
            {
                assertCondition = 0;
                sprintf(msgSfx, "player: %d  card: %d  testCount: %d != expectedCounts[%d]: %d", player, card, testCount, card, expectedCounts[card]);
                strcat(msgPfx, msgSfx);
                strcpy(failMsg, msgPfx);
                result = -1;
            }

			
            assertMsg(assertCondition, passMsg, failMsg);
            
			
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
                sprintf(msgSfx, "Game State has changed after running test. player: %d  card: %d", player, card);
                strcat(msgPfx, msgSfx);
                strcpy(failMsg, msgPfx);
                result = -1;
            }
   
            assertMsg(assertCondition, passMsg, failMsg);
		}

        // Reset expectedCounts for comparison with next player data
        memset(expectedCounts, 0, sizeof expectedCounts);
        expectedCounts[1] = 3;
        expectedCounts[4] = 7;
	}

    if (result == 0)
    {
        printf(passMsg2);
        printf("%d\n", testNum);
    }

	
	/************************************************************************/
	
	// ----------- TEST 2: Deck, Hand, and Discard all have 0 cards --------------
	
	strcpy(msgPfx, "TEST 2: Deck, Hand, and Discard all have 0 cards");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");
    strcpy(passMsg, "TEST 2");
    strcpy(failMsg, "N/A");

    testNum = 2;

    // Reset values for next test	
	
    memset(expectedCounts, 0, sizeof expectedCounts);
	memcpy(&baseGst, &initialGst, sizeof(struct gameState));
	memcpy(&testGst, &initialGst, sizeof(struct gameState));
	
	
	// Initialize hand, deck, and discard for currPlayer
	// All card groups will have 0 cards.
    // Also set values in expectedCounts array based on initializations 
	currPlayer = 0;	
    
    // Deck
	startCard = 0;	// Victory cards start at 0
	for (card = startCard; card < NUMCARDOPTIONS; card++)
	{
		testGst.deck[currPlayer][card - startCard] = -1;
	}
	
	testGst.deckCount[currPlayer] = 0; 
	
	
	// Hand
	startCard = 4;	// Province card. Victory cards start at 0
	for (card = startCard; card < testGst.handCount[currPlayer] + startCard; card++)
	{
		testGst.hand[currPlayer][card - startCard] = -1;
	}	
	
	testGst.handCount[currPlayer] = 0; 
	
	
	// Discard
	startCard = 6;	// Victory cards start at 0
	for (card = startCard; card < NUMCARDOPTIONS; card++)
	{
		testGst.discard[currPlayer][card - startCard] = -1;
	}
	
	testGst.discardCount[currPlayer] = 0;
	
	// Copy the changed test game state to base case game state for later comparison
	memcpy(&baseGst, &testGst, sizeof(struct gameState));
	
	
	// Run the Test
    
	for (player = 0; player < numPlayers; player++)
    {
        for (card = 0; card < NUMCARDOPTIONS; card++) // check counts for all cards 0 - 16
		{
	        strcpy(msgPfx, "TEST 2: Deck, Hand, and Discard all have 0 cards");
            strcat(msgPfx, ":  ");

			// Call the fullDeckCount function for each input combination
			testCount = fullDeckCount(player, card, &testGst);

			
            // Test: Compare testCount returned by function to expected count for the card.
			
	        if (testCount == expectedCounts[card])
            {
                assertCondition = 1;
            }

            else
            {
                assertCondition = 0;
                sprintf(msgSfx, "player: %d  card: %d  testCount: %d != expectedCounts[%d]: %d", player, card, testCount, card, expectedCounts[card]);
                strcat(msgPfx, msgSfx);
                strcpy(failMsg, msgPfx);
                result = -1;
            }

            assertMsg(assertCondition, passMsg, failMsg);

			
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
                sprintf(msgSfx, "Game State has changed after running test. player: %d  card: %d", player, card);
                strcat(msgPfx, msgSfx);
                strcpy(failMsg, msgPfx);
                result = -1;
            }
   
            assertMsg(assertCondition, passMsg, failMsg);
		}

        // Reset expectedCounts for comparison with next player data
        memset(expectedCounts, 0, sizeof expectedCounts);
        expectedCounts[1] = 3;
        expectedCounts[4] = 7;
	}

    if (result == 0)
    {
        printf(passMsg2);
        printf("%d\n", testNum);
    }

	
	/************************************************************************/
	
	// ----------- TEST 3: Hand and Discard have cards, Deck has 0 cards --------------
	
	strcpy(msgPfx, "TEST 3: Hand and Discard have cards, Deck has 0 cards");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");
    strcpy(passMsg, "TEST 3");
    strcpy(failMsg, "N/A");

    testNum = 3;

    // Reset values for next test	
	
    memset(expectedCounts, 0, sizeof expectedCounts);
	memcpy(&baseGst, &initialGst, sizeof(struct gameState));
	memcpy(&testGst, &initialGst, sizeof(struct gameState));

	
	// Initialize hand, deck, and discard for currPlayer
    // Also set values in expectedCounts array based on initializations 
	currPlayer = 0;	

    // Deck
	startCard = 0;	// Victory cards start at 0
	for (card = startCard; card < NUMCARDOPTIONS; card++)
	{
		testGst.deck[currPlayer][card - startCard] = -1;
	}
	
	testGst.deckCount[currPlayer] = 0; 
    
	// Hand
	startCard = 4;	// Province card. Victory cards start at 0
	for (card = startCard; card < testGst.handCount[currPlayer] + startCard; card++)
	{
		testGst.hand[currPlayer][card - startCard] = card;
        expectedCounts[card] += 1;
	}	

	// Discard
	startCard = 6;	// Victory cards start at 0
	for (card = startCard; card < NUMCARDOPTIONS; card++)
	{
		testGst.discard[currPlayer][card - startCard] = card;
        expectedCounts[card] += 1; 
	}
	
	testGst.discardCount[currPlayer] = NUMCARDOPTIONS - startCard;


	// Copy the changed test game state to base case game state for later comparison
	memcpy(&baseGst, &testGst, sizeof(struct gameState));
	
    
	// Run the Test
    
	for (player = 0; player < numPlayers; player++)
    {
        for (card = 0; card < NUMCARDOPTIONS; card++) // check counts for all cards 0 - 16
		{
	        strcpy(msgPfx, "TEST 3: Hand and Discard have cards, Deck has 0 cards");
            strcat(msgPfx, ":  ");

			// Call the fullDeckCount function for each input combination
			testCount = fullDeckCount(player, card, &testGst);

			
            // Test: Compare testCount returned by function to expected count for the card.			
			
	        if (testCount == expectedCounts[card])
            {
                assertCondition = 1;
            }

            else
            {
                assertCondition = 0;
                sprintf(msgSfx, "player: %d  card: %d  testCount: %d != expectedCounts[%d]: %d", player, card, testCount, card, expectedCounts[card]);
                strcat(msgPfx, msgSfx);
                strcpy(failMsg, msgPfx);
                result = -1;
            }

            assertMsg(assertCondition, passMsg, failMsg);

            
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
                sprintf(msgSfx, "Game State has changed after running test. player: %d  card: %d", player, card);
                strcat(msgPfx, msgSfx);
                strcpy(failMsg, msgPfx);
                result = -1;
            }
   
            assertMsg(assertCondition, passMsg, failMsg);
		}

        // Reset expectedCounts for comparison with next player data
        memset(expectedCounts, 0, sizeof expectedCounts);
        expectedCounts[1] = 3;
        expectedCounts[4] = 7;  // *#*#* Comment this out to introduce a failure
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
 ** Function:           main() method for unittest1 program
 ** 
 ** Description:    main() method for program to unit test the 
 **                 fullDeckCount function from dominion.c
 ** Parameters:     none
 ** Return Value:   0 - conventional for success of int main() method
 ************************************************************************/
 
int main(int argc, char *argv[])
{
    testFullDeckCount();
    return 0;
}
