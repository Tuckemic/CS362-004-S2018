/* CS 362 Assignment 3 */
/*************************************************************************
 ** Author:                  Michael Tucker
 ** Date Created:            4/17/2018
 ** Last Modification Date:  4/29/2018
 ** Filename:                cardtest1.c
 ** 
 ** Overview:  This program implements a Unit Test Suite for testing the
 **            Smithy card from the Dominion card game. The test 
 **            suite includes tests for the effect the card has on 
 **            the elements of the Game State including the player's 
 **            hand, player's deck and card supply piles. The Unit
 **            test include:
 **			   TEST 1: Player Receives +3 Cards in Hand
 ** 		   TEST 2: 3 Cards Were Drawn from Player's Deck
 **			   TEST 3: No Changes to Victory Card and Kingdom Card 
 **					   Supply Piles
 **			   TEST 4: No State Change Should Occur for Other Players
 ** Input:   None.  The program executes and calls functions from the
 **          dominion.c file, which includes code under test. 
 ** Output:  A new file is created and appended, unittestresults.out
 **          which includes all unit test and coverage results.
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "rngs.h"
#include "dominion.h"
#include "dominion_helpers.h"
#include "interface.h"

#define TESTCARDNAME "Smithy"
#define TESTCARD smithy

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
 ** Function:                assertMsgSm
 ** 
 ** Description:    Function to compare the actual value of the test 
 **                 result produced by a unit subtest to the expected 
 **                 value. If the test fails, a FAIL message and failure 
 **                 results for the test are output. The test inputs
 **                 are specific to the tests run on the Smithy card.
 ************************************************************************/

int assertMsgSm(int player, char* pileLabel, char* subTestLabel, int testNum, int actualVal, int expectedVal)
{
    char failMsg[128];
    char tempStr[128];
  
    int resultVal = 0;

    if (actualVal != expectedVal)
    {
        strcpy(failMsg, "FAILED. Test");
		sprintf(tempStr, "%d: P: %d, %s, %s:  ", testNum, player, pileLabel, subTestLabel);
		strcat(failMsg, tempStr);
		sprintf(tempStr, "actual: %d != expected: %d\n", actualVal, expectedVal);
		strcat(failMsg, tempStr);
        printf(failMsg);
        resultVal = -1;
    }

    return resultVal;
}


/*************************************************************************
 ** Function:                diffSupply
 ** 
 ** Description:    Function to compare the counts of each Supply Piles
 **                 of cards and return the card number if there is
 **                 a difference.
 ************************************************************************/

int diffSupply(struct gameState *testState, struct gameState *baseState)
{
    int i = 0;
    int dResult = -1;

    while (i < treasure_map + 1 && dResult == -1)
    {
        if (testState->supplyCount[i] != baseState->supplyCount[i])
        {
            dResult = i;
        }

        i++;
    }

    return dResult;
}


/************************************************************************/

// smithy card case from original cardEffect() switch-case

/*
	case smithy:
		//+3 Cards
		for (i = 0; i < 3; i++)
		{
			drawCard(currentPlayer, state);
		}
                                      
		//discard card from hand
		discardCard(handPos, currentPlayer, state, 0);
		return 0;
*/


/*************************************************************************
 ** Function:                testSmithyCard
 ** 
 ** Description:    Function to implement the Unit Tests for testing 
 **                 the Dominion Smithy Card.
 ************************************************************************/

int testSmithyCard()
{
    char msgPfx[128];
    char msgSfx[128];
    char passMsg[128];
    char failMsg[128];

    int i;
    int result = 0;
    int assertCondition = 0;
	int assertRetVal = 0;
	int testNum;

    int newCards = 0;
    int shuffledCards = 0;
    int discardedCount = 1; // This is 1 because card discarded after use

    int choice1 = 0, choice2 = 0, choice3 = 0, handpos = 0, bonus = 0;

    int numPlayers = 2;
    int randSeed = 1000;
    
    int currPlayer = 0;

    int testHandCount = 0;
    int baseHandCount = 0;
    int adjBaseHandCount = 0;

    int testDeckCount = 0;
    int baseDeckCount = 0;
    int adjBaseDeckCount = 0;

    int diffResult = 0;
    int testResult = 0;
	
	int actualVal;
	int expectedVal;
	
    struct gameState baseGst, testGst, modBaseGst;
	
    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};
				 
	char handLabel[64];
    char deckLabel[64];
    char discardLabel[64];
    char countTestLabel[64];
    char cardTestLabel[64];
	
	strcpy(handLabel, "hand");
    strcpy(deckLabel, "deck");
    strcpy(discardLabel, "discard");
    strcpy(countTestLabel, "count test");
    strcpy(cardTestLabel, "card test");


	printf("----------------- Testing Card: %s ----------------\n", TESTCARDNAME);
	
    // Initialize a Game: set base game state and first turn player cards
	initializeGame(numPlayers, k, randSeed, &baseGst);

    // Replace a card in player hand with Smithy card
    if (baseGst.hand[currPlayer][handpos] == copper)
    {
        baseGst.coins -= 1;
        baseGst.supplyCount[copper] += 1;
    }
    else
    {
        baseGst.supplyCount[estate] += 1;
    }
    
    baseGst.hand[currPlayer][handpos] = TESTCARD;
    baseGst.supplyCount[TESTCARD] -= 1;   

	
	// Replace cards near top of deck
    baseGst.deck[currPlayer][baseGst.deckCount[currPlayer] - 3] = feast;
    baseGst.deck[currPlayer][baseGst.deckCount[currPlayer] - 2] = gardens;
    baseGst.deck[currPlayer][baseGst.deckCount[currPlayer] - 1] = mine;


	// Copy the base game state to a test case game state
	memcpy(&testGst, &baseGst, sizeof(struct gameState));
	memcpy(&modBaseGst, &baseGst, sizeof(struct gameState));

	
	/************************************************************************/

	// ----------- TEST 1: Player Receives +3 Cards in Hand --------------
    
    strcpy(msgPfx, "TEST 1: Player Receives +3 Cards in Hand");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 1");
    strcpy(failMsg, "N/A");    
	
	testNum = 1;
	
    newCards = 3;
	
	
	// Run the cardEffect function for Smithy card
	cardEffect(TESTCARD, choice1, choice2, choice3, &testGst, handpos, &bonus);

	
	// Test: Check that the new handCount is correct
    
	testHandCount = testGst.handCount[currPlayer];
    baseHandCount = baseGst.handCount[currPlayer];
    adjBaseHandCount = baseHandCount + newCards - discardedCount;

    if (testHandCount == adjBaseHandCount)
    {
        assertCondition = 1;
    }

    else
    {
        assertCondition = 0;
        sprintf(msgSfx, "testHandCount: %d != adjBaseHandCount: %d", testHandCount, adjBaseHandCount);
        strcat(msgPfx, msgSfx);
        strcpy(failMsg, msgPfx);
        result = -1;
    }

    assertMsg(assertCondition, passMsg, failMsg);

	
    // Test: Check that new cards at last and second to last hand positions are correct
	
	for (i = 0; i < 2; i++)
	{
		expectedVal = baseGst.deck[currPlayer][baseGst.deckCount[currPlayer] - 1 - i];
		actualVal = testGst.hand[currPlayer][testGst.handCount[currPlayer] - 2 + i];
		assertRetVal = assertMsgSm(currPlayer, handLabel, cardTestLabel, testNum, actualVal, expectedVal);
		if (assertRetVal == -1)
		{
			result = assertRetVal;
		}
	}
	
    // Test: Third (last) card drawn was relocated to first position in hand during discard of Smithy
	
	expectedVal = baseGst.deck[currPlayer][baseGst.deckCount[currPlayer] - 3];
	actualVal = testGst.hand[currPlayer][0];
	assertRetVal = assertMsgSm(currPlayer, handLabel, cardTestLabel, testNum, actualVal, expectedVal);
	if (assertRetVal == -1)
	{
		result = assertRetVal;
	}

	
	/************************************************************************/	
	
	// ----------- TEST 2: 3 Cards Were Drawn from Player's Deck --------------
    
    strcpy(msgPfx, "TEST 2: 3 Cards Were Drawn from Player's Deck");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 2");
    strcpy(failMsg, "N/A");
	
	testNum = 2;

	newCards = 3;
	
	// Reset the test case game state
	memcpy(&testGst, &modBaseGst, sizeof(struct gameState));
	memcpy(&baseGst, &modBaseGst, sizeof(struct gameState));


	// Run the cardEffect function for Smithy card
	cardEffect(TESTCARD, choice1, choice2, choice3, &testGst, handpos, &bonus);
	
	
	// Test: Compare the deck cards between test and base game states
	
	for (i = 0; i < testGst.deckCount[currPlayer]; i++)
    {
		if (testGst.deck[currPlayer][i] != baseGst.deck[currPlayer][i])
        {
            testResult = i;
        }
    }

	actualVal = testResult;
	expectedVal = 0;

	assertRetVal = assertMsgSm(currPlayer, deckLabel, cardTestLabel, testNum, actualVal, expectedVal);
	if (assertRetVal == -1)
	{
		result = assertRetVal;
	}
	
	
	// Test: Compare the deck counts between test and base game states
    
	testDeckCount = testGst.deckCount[currPlayer];
    baseDeckCount = baseGst.deckCount[currPlayer];
    adjBaseDeckCount = baseDeckCount - newCards + shuffledCards;

    if (testDeckCount == adjBaseDeckCount)
    {
        assertCondition = 1;
    }

    else
    {
        assertCondition = 0;
        sprintf(msgSfx, "testDeckCount: %d != adjBaseDeckCount: %d", testDeckCount, adjBaseDeckCount);
        strcat(msgPfx, msgSfx);
        strcpy(failMsg, msgPfx);
        result = -1;
    }

    assertMsg(assertCondition, passMsg, failMsg);
	

	/************************************************************************/

	// ----------- TEST 3: No Changes to Victory Card and Kingdom Card Supply Piles --------------
    
    strcpy(msgPfx, "TEST 3: No Changes to Victory Card and Kingdom Card Supply Piles");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 3");
    strcpy(failMsg, "N/A");    

	// Test: Compare supply pile data from game states before and after playing 
	//       card in cardEffect function.    

    diffResult = diffSupply(&testGst, &baseGst);  

    if (diffResult == -1)
    {
        assertCondition = 1;
    }

    else
    {
        assertCondition = 0;
        sprintf(msgSfx, "Supply Card Count Changed for Card: %d", diffResult);
        strcat(msgPfx, msgSfx);
        strcpy(failMsg, msgPfx);
        result = -1;
    }

    assertMsg(assertCondition, passMsg, failMsg);

	
	/************************************************************************/
	
	// ----------- TEST 4: No State Change Should Occur for Other Players --------------
    
    strcpy(msgPfx, "TEST 4: No State Change Should Occur for Other Players");
    printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 4");
    strcpy(failMsg, "N/A");    

    // No state change should occur for other players.
    // Manually modify the modBaseGst for currPlayer for comparison

    for (i = 0; i < MAX_HAND; i++)
    {
        modBaseGst.hand[currPlayer][i] = testGst.hand[currPlayer][i];
    }
    
    for (i = 0; i < MAX_DECK; i++)
    {
        modBaseGst.deck[currPlayer][i] = testGst.deck[currPlayer][i];
    }    
        
	for (i = 0; i < MAX_DECK; i++)
    {
        modBaseGst.discard[currPlayer][i] = testGst.discard[currPlayer][i];
    }  
	
    modBaseGst.handCount[currPlayer] = testGst.handCount[currPlayer]; 
    modBaseGst.deckCount[currPlayer] = testGst.deckCount[currPlayer];
    modBaseGst.discardCount[currPlayer] = testGst.discardCount[currPlayer];
	
    modBaseGst.playedCards[modBaseGst.playedCardCount] = smithy;
    modBaseGst.playedCardCount++;

	
    // Test: Compare test game state to base game state for differences
	
    if (memcmp(&testGst, &modBaseGst, sizeof(struct gameState)) == 0)
    {
        assertCondition = 1;
    }

    else
    {
        assertCondition = 0;
        sprintf(msgSfx, "Game state has changed for other player.");
        strcat(msgPfx, msgSfx);
        strcpy(failMsg, msgPfx);
        result = -1;
    } 

    assertMsg(assertCondition, passMsg, failMsg);

 	
	/************************************************************************/
    // Final Result Message
	   
	if (result == 0)
    {
	    printf(" >>>>>  SUCCESS: Testing Complete for %s card. All Tests Passed.  <<<<<\n", TESTCARDNAME);
    }
    
    else
    {
        printf(" ******* Testing Complete for %s card. There were one or more Failed Tests. *******\n", TESTCARDNAME);
    }

    printf("\n");
    return result;
}


/************************************************************************/

/************************************************************************/

/*************************************************************************
 ** Function:           main() method for cardtest1 program
 ** 
 ** Description:    main() method for program to unit test the 
 **                 Smithy Card from the Dominion Card Game.
 ** Parameters:     none
 ** Return Value:   0 - conventional for success of int main() method
 ************************************************************************/

int main(int argc, char *argv[])
{
    testSmithyCard();
    return 0;
}
