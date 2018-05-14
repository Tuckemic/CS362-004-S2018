/* CS 362 Assignment 4 */
/*************************************************************************
 ** Author:                  Michael Tucker
 ** Date Created:            5/7/2018
 ** Last Modification Date:  5/13/2018
 ** Filename:                randomtestcard1.c
 ** 
 ** Overview:  This program implements a random test generator for 
 **            testing the Smithy card from the Dominion card game.
 **            The test generates random inputs and then tests the
 **            effect the card has on elements of the Game State.
 **            The tests include:
 **			   TEST 1: Player Receives +3 Cards in Hand
 ** 		   TEST 2: 3 Cards Were Drawn from Player's Deck
 **			   TEST 3: No Changes to Victory Card and Kingdom Card 
 **					   Supply Piles
 **			   TEST 4: State Change Should Reflect Effect of Smithy 
 **                    Card
 ** Input:   None.  The program executes and calls functions from the
 **          dominion.c file, which includes card code under test. 
 ** Output:  A new file is created and appended, randomtestcard1.out
 **          which includes the test and coverage results.
 ************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
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

void assertMsg(int iteration, int condition, char* trueMsg, char* falseMsg)
{
    if (condition)
    {
        // printf("PASSED: %s\n", trueMsg);
    }
    else
    {
        printf("FAILED: iter: %d  %s\n", iteration, falseMsg);
        // exit(0);
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

int assertMsgSm(int iteration, int player, char* pileLabel, char* subTestLabel, int testNum, int actualVal, int expectedVal)
{
    char failMsg[128];
    char tempStr[128];
  
    int resultVal = 0;

    if (actualVal != expectedVal)
    {
        strcpy(failMsg, "FAILED. iter: ");
		sprintf(tempStr, "%d  Test%d: P: %d, %s, %s:  ", iteration, testNum, player, pileLabel, subTestLabel);
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
 ** Function:                printFinalTestResult
 ** 
 ** Description:    Function to implement printing the final test 
 **                 results message to the user console. This is a 
 **                 tally of failed tests for each of the major test
 **                 groups performed for each random input case, as well
 **                 as a test results summary message.
 ************************************************************************/

void printFinalTestResult(int result, int *failTestCounts)
{
    int i;

	// Test Failure Tally Results
    printf("\nTest Failure Totals:\n"); 
    for (i = 0; i < 4; i++)
    {
        printf("TEST %d Fail Count: %d\n", i + 1, failTestCounts[i]);
    }
    printf("\n");
	

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
}
 
 	
/*************************************************************************
 ** Function:                checkHandPlus3
 ** 
 ** Description:    Function to implement Test 1: Player Receives +3 
 **                 Cards in Hand. Test result (pass or fail for this 
 **                 test group) is returned.
 ************************************************************************/  
 
int checkHandPlus3(int *failTestCounts, int iteration, int player, int handPos, struct gameState *testG, struct gameState *baseG)
{
	// ----------- TEST 1: Player Receives +3 Cards in Hand --------------

    char msgPfx[128];
    char msgSfx[128];
    char passMsg[128];
    char failMsg[128];

    int i;
	int assertCondition = 0;
	int assertRetVal = 0;
    int result = 0;
	
    int testNum;
    int newCards = 0;
    int discardedCount = 1; // This is 1 because card discarded after use
	
	int testHandCount = 0;
    int baseHandCount = 0;
    int adjBaseHandCount = 0;

	int actualVal;
	int expectedVal;
	
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
	
    strcpy(msgPfx, "TEST 1: Player Receives +3 Cards in Hand");
    // printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 1");
    strcpy(failMsg, "N/A");    

	testNum = 1;
	newCards = 3;
	
	
	// Test: Check that the new handCount is correct
   
    if (baseG->deckCount[player] > 2)
    {
	    testHandCount = testG->handCount[player];
        baseHandCount = baseG->handCount[player];
        adjBaseHandCount = baseHandCount + newCards - discardedCount;
    }
    
    if ((baseG->deckCount[player] + baseG->discardCount[player]) > 2)
    {
	    testHandCount = testG->handCount[player];
        baseHandCount = baseG->handCount[player];
        adjBaseHandCount = baseHandCount + newCards - discardedCount;
    }

    else
    {
        adjBaseHandCount = testHandCount;
    }

    /* 
    // Introduce a bug to fail test
    if (iteration == 1 || iteration == 4)
    {
        adjBaseHandCount++;
    }
    */

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

    if (assertCondition == 0)
    {
        failTestCounts[0]++;
    }
    
    assertMsg(iteration, assertCondition, passMsg, failMsg);

	
    // Test: Check that new cards at last and second to last hand positions are correct
	
	for (i = 0; i < 2; i++)
	{
        if (baseG->deckCount[player] > 2)
        {
		    expectedVal = baseG->deck[player][baseG->deckCount[player] - 1 - i];
        }
        
        else if (baseG->deckCount[player] == 1 && i == 1)
        {
		    expectedVal = 0; 
        }
        
        else if (baseG->deckCount[player] == 0)
        {
            expectedVal = 0;
        }

        else
        {
		    expectedVal = baseG->deck[player][baseG->deckCount[player] - 1 - i];
            // expectedVal = 0; 
        }
		
        actualVal = testG->hand[player][testG->handCount[player] - 2 + i];
        	
        assertRetVal = assertMsgSm(iteration, player, handLabel, cardTestLabel, testNum, actualVal, expectedVal);
		if (assertRetVal == -1)
		{
			result = assertRetVal;
		}
	
        if (assertRetVal == -1)
        {   
            failTestCounts[0]++;
        }
    }
    
    
    // Test: Third (last) card drawn was relocated to original Smithy hand position in hand during discard of Smithy

    if (baseG->deckCount[player] > 2)
    {
	    expectedVal = baseG->deck[player][baseG->deckCount[player] - 3];
    }

    else
    {
        expectedVal = 0;
    }
    
    actualVal = testG->hand[player][handPos];

    /* 
    // Introduce a bug to fail test
    if (iteration == 1 || iteration == 4)
    {
        actualVal = 9999;
    }
    */

    assertRetVal = assertMsgSm(iteration, player, handLabel, cardTestLabel, testNum, actualVal, expectedVal);
	if (assertRetVal == -1)
	{
		result = assertRetVal;
	}
	
    if (assertRetVal == -1)
    {
        failTestCounts[0]++;
    }
	
    return result;
}

	
/*************************************************************************
 ** Function:                checkDeckMinus3
 ** 
 ** Description:    Function to implement TEST 2: 3 Cards Were Drawn 
 **					from Player's Deck. Test result (pass or fail for 
 **					this test group) is returned.
 ************************************************************************/  
 
int checkDeckMinus3(int *failTestCounts, int iteration, int player, int handPos, struct gameState *testG, struct gameState *baseG)
{
	// ----------- TEST 2: 3 Cards Were Drawn from Player's Deck --------------

	char msgPfx[128];
    char msgSfx[128];
    char passMsg[128];
    char failMsg[128];

    int i;
	int assertCondition = 0;
	int assertRetVal = 0;
    int result = 0;
	
    int testNum;
    int newCards = 0;
    int shuffledCards = 0;
	
	int testDeckCount = 0;
    int baseDeckCount = 0;
    int adjBaseDeckCount = 0;

	int actualVal = 0;
	int expectedVal = 0;
    int testResult = 0;
	
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
	
    strcpy(msgPfx, "TEST 2: 3 Cards Were Drawn from Player's Deck");
    // printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 2");
    strcpy(failMsg, "N/A");
	
	testNum = 2;
	newCards = 3;

    // Adjust base game state for comparison, if a shuffle had occurred
    if (testG->discardCount[player] == 0 && baseG->deckCount[player] < 3)
    {
        for (i = 0; i < 10; i++)
        {
            baseG->deck[player][i] = 0;
        }
    
        baseG->deckCount[player] = testG->deckCount[player] + 3;
    }
	
	
    // Test: Compare the deck cards between test and base game states
	
	for (i = 0; i < testG->deckCount[player]; i++)
    {
		if (testG->deck[player][i] != baseG->deck[player][i])
        {
            testResult = i;
        }
    }

	actualVal = testResult;
	expectedVal = 0;

    /* 
    // Introduce a bug to fail test
    if (iteration == 1 || iteration == 4)
    {
        expectedVal = 9999; 
    }
	*/

    assertRetVal = assertMsgSm(iteration, player, deckLabel, cardTestLabel, testNum, actualVal, expectedVal);
	if (assertRetVal == -1)
	{
		result = assertRetVal;
	}
	
    if (assertRetVal == -1)
    {
        failTestCounts[1]++;
    }
	
	
	// Test: Compare the deck counts between test and base game states
    
	testDeckCount = testG->deckCount[player];
    baseDeckCount = baseG->deckCount[player];
    adjBaseDeckCount = baseDeckCount - newCards + shuffledCards;

    /* 
    // Introduce a bug to fail test
    if (iteration == 1 || iteration == 4)
    {
        adjBaseDeckCount++;
    }
    */ 
    
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

    if (assertCondition == 0)
    {
        failTestCounts[1]++;
    }
    
    assertMsg(iteration, assertCondition, passMsg, failMsg);

	return result;
}	


/*************************************************************************
 ** Function:                checkSupplyCounts
 ** 
 ** Description:    Function to implement TEST 3: No Changes to Victory 
 **					Card and Kingdom Card Supply Piles. Test result 
 **					(pass or fail for this test group) is returned.
 ************************************************************************/  
 
int checkSupplyCounts(int *failTestCounts, int iteration, int player, int handPos, struct gameState *testG, struct gameState *baseG)
{
	// ----------- TEST 3: No Changes to Victory Card and Kingdom Card Supply Piles --------------

	char msgPfx[128];
    char msgSfx[128];
    char passMsg[128];
    char failMsg[128];

	int assertCondition = 0;
    int result = 0;
    int diffResult;
	
    strcpy(msgPfx, "TEST 3: No Changes to Victory Card and Kingdom Card Supply Piles");
    // printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 3");
    strcpy(failMsg, "N/A");    
 

	// Test: Compare supply pile data from game states before and after playing 
	//       card in cardEffect function.    

    diffResult = diffSupply(testG, baseG);  
    
    /* 
    // Introduce a bug to fail test
    if (iteration == 1 || iteration == 4)
    {
        diffResult = 9999; 
    }
    */

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

    if (assertCondition == 0)
    {
        failTestCounts[2]++;
    }
    
    assertMsg(iteration, assertCondition, passMsg, failMsg);
 
	return result;
}
 
 
/*************************************************************************
 ** Function:                checkGameState
 ** 
 ** Description:    Function to implement TEST 4: Game State after 
 **					playing Smithy Card should reflect Smithy Card 
 **					Effect. Test result (pass or fail for this test 
 **					group) is returned.
 ************************************************************************/  
 
int checkGameState(int *failTestCounts, int iteration, int player, int handPos, struct gameState *testG, struct gameState *baseG)
{
	// ----------- TEST 4: Game State after playing Smithy Card should reflect Smithy Card Effect --------------

	char msgPfx[128];
    char msgSfx[128];
    char passMsg[128];
    char failMsg[128];

    int assertCondition = 0;
    int result = 0;
	
	struct gameState modBaseGst;
	
    strcpy(msgPfx, "TEST 4: Game State after playing Smithy Card should reflect Smithy Card Effect");
    // printf("%s\n", msgPfx);
    strcat(msgPfx, ":  ");

    strcpy(passMsg, "TEST 4");
    strcpy(failMsg, "N/A");  
 
	memcpy(&modBaseGst, baseG, sizeof(struct gameState));
	
 
    // Manually modify the modBaseGst game state for comparison
		
	// handCount for player increased by net +2
	if (baseG->deckCount[player] > 2)
	{
		modBaseGst.handCount[player] += 2;
		modBaseGst.hand[player][modBaseGst.handCount[player] - 2] = baseG->deck[player][baseG->deckCount[player] - 1];
		modBaseGst.hand[player][modBaseGst.handCount[player] - 1] = baseG->deck[player][baseG->deckCount[player] - 2];
		modBaseGst.hand[player][handPos] = baseG->deck[player][baseG->deckCount[player] - 3];
		modBaseGst.hand[player][modBaseGst.handCount[player]] = -1; 
	}   

    else if (baseG->discardCount[player] > 2)
    {
        modBaseGst.handCount[player] += 2;
	    
        memcpy(modBaseGst.hand[player], testG->hand[player], sizeof(int) * MAX_HAND);
    }

    else
    {
        modBaseGst.handCount[player] = testG->handCount[player];
        memcpy(modBaseGst.hand[player], testG->hand[player], sizeof(int) * MAX_HAND);
    }

	// playedCards array includes Smithy
	// playedCardCount increased by 1
    modBaseGst.playedCards[modBaseGst.playedCardCount] = smithy;
    modBaseGst.playedCardCount++;

    // If a shuffle occurred, then more modifications needed
    if (baseG->deckCount[player] < 3)
    {
        modBaseGst.deckCount[player] = testG->deckCount[player];
        
        memcpy(modBaseGst.deck[player], testG->deck[player], sizeof(int) * MAX_DECK);

        memcpy(modBaseGst.discard[player], testG->discard[player], sizeof(int) * MAX_DECK);

        modBaseGst.discardCount[player] = 0;
    }
    
    else
    {
		modBaseGst.deckCount[player] -= 3;
    }


    // Test: Compare test game state to base game state for differences
	
    if (memcmp(testG, &modBaseGst, sizeof(struct gameState)) == 0)
    {
        assertCondition = 1;
    }

    else
    {
        assertCondition = 0;
        sprintf(msgSfx, "Game state is incorrect.");
        strcat(msgPfx, msgSfx);
        strcpy(failMsg, msgPfx);
        result = -1;
    }

    if (assertCondition == 0)
    {
        failTestCounts[3]++;
    }

    assertMsg(iteration, assertCondition, passMsg, failMsg);
	
	return result;
} 
 
 
/*************************************************************************
 ** Function:                checkSmithyCard
 ** 
 ** Description:    Function to implement the test oracle for testing
 **                 the Smithy Card effect with random inputs. This 
 **                 function calls other functions above to perform each
 **                 specific test or test group.
 ************************************************************************/ 

int checkSmithyCard(int *failTestCounts, int iteration, int player, int handPos, struct gameState *testGameState)
{
    int choice1 = 0, choice2 = 0, choice3 = 0,  bonus = 0;
	int result;
	int finalResult = 0;

    struct gameState preGameState, preBaseGameState;
    
    memcpy(&preGameState, testGameState, sizeof(struct gameState));
    memcpy(&preBaseGameState, testGameState, sizeof(struct gameState));

    
    // Run the cardEffect function for Smithy card
    cardEffect(TESTCARD, choice1, choice2, choice3, testGameState, handPos, &bonus); 

	
    // TEST 1: Player Receives +3 Cards in Hand
	result = checkHandPlus3(failTestCounts, iteration, player, handPos, testGameState, &preGameState);
	if (result != 0)
	{
		finalResult = result;
	}

	
    memcpy(&preGameState, &preBaseGameState, sizeof(struct gameState));

    // TEST 2: 3 Cards Were Drawn from Player's Deck
	result = checkDeckMinus3(failTestCounts, iteration, player, handPos, testGameState, &preGameState);
	if (result != 0)
	{
		finalResult = result;
	}

	
    memcpy(&preGameState, &preBaseGameState, sizeof(struct gameState));
	
    // TEST 3: No Changes to Victory Card and Kingdom Card Supply Piles
	result = checkSupplyCounts(failTestCounts, iteration, player, handPos, testGameState, &preGameState);
	if (result != 0)
	{
		finalResult = result;
	}

    
    memcpy(&preGameState, &preBaseGameState, sizeof(struct gameState));

	// TEST 4: Game State after playing Smithy Card should reflect Smithy Card Effect
	result = checkGameState(failTestCounts, iteration, player, handPos, testGameState, &preGameState);
    
    if (result != 0)
	{
		finalResult = result;
	}

    return finalResult;
}	
 
 
/*************************************************************************
 ** Function:                randomTestSmithyCard
 ** 
 ** Description:    Function to implement the random test generator for
 **                 testing the Smithy Card. A random game state is 
 **                 generated and adjusted such that some parameters
 **                 have random values falling within a valid range.
 ************************************************************************/

int randomTestSmithyCard()
{
    int i;
    int numCycles;
	int result = 0;
    int finalResult = 0;
    
    int handPos = 0;
    int numPlayers = 0;
	int player = 0;
    int numActions = 0;
    int playerHandCount = 0;
    int randSeed = 0; 

    int k[10] = {adventurer, council_room, feast, gardens, mine,
                 remodel, smithy, village, baron, great_hall};

    int failTestCounts[4];

    struct gameState testGst, initialGst; 
    
	
	printf("----------------- Testing Card: %s ----------------\n", TESTCARDNAME);
	printf ("RANDOM TESTS starting.\n");

    numPlayers = 4;
    randSeed = 1000;

    initializeGame(numPlayers, k, randSeed, &initialGst); 

    memset(failTestCounts, 0, sizeof(failTestCounts));

    // Generate Random Inputs for each cycle of the outer for loop
	// and run the Smithy test oracle for each case of random inputs
    
	for (numCycles = 0; numCycles < 2000; numCycles++)
	{
        memcpy(&testGst, &initialGst, sizeof(struct gameState));

        // Adjust game state for certain parameters with random values
        // with valid range
		
        numActions = (rand() % 256);
        testGst.numActions = numActions;
        
        testGst.numPlayers = numPlayers;	
        
        player = (rand() % numPlayers); 
        testGst.whoseTurn = player;
       
        for (i = 0; i < numPlayers; i++)
        {
            testGst.deckCount[i] = (rand() % (MAX_DECK + 1));
            
            testGst.discardCount[i] = (rand() % (MAX_DECK + 1));

            testGst.handCount[i] = (rand() % (MAX_HAND + 1));
        }
        
        testGst.playedCardCount = (rand() % (MAX_HAND + 1));

	    // Replace a card in player hand at a random handpos with Smithy card
        playerHandCount = testGst.handCount[player];
           
        if (playerHandCount != 0)
        {
            handPos = (rand() % playerHandCount);  	
	    }
        else
        {
            handPos = 10;
        }
        
        testGst.hand[player][handPos] = TESTCARD;
        
        // Inputs have been randomized
        // Check the Smithy Card effect with the random inputs for this iteration

        result = checkSmithyCard(failTestCounts, numCycles, player, handPos, &testGst);

        if (result != 0)
        {
            finalResult = result;
        }
	}

  
	/************************************************************************/
    // Final Result Message

	printFinalTestResult(finalResult, failTestCounts);
    	
	return finalResult;
} 
 
 
/************************************************************************/

/************************************************************************/

/*************************************************************************
 ** Function:           main() method for randomtestcard1 program
 ** 
 ** Description:    main() method for program to random test the 
 **                 Smithy Card from the Dominion Card Game.
 ** Parameters:     none
 ** Return Value:   0 - conventional for success of int main() method
 ************************************************************************/

int main(int argc, char *argv[])
{
    srand(time(NULL));
    randomTestSmithyCard();
    return 0;
}

