/*
    Name: Jorge Guzman Nader
    Date: 4/29/18
    CS 362 
    Assignment 3
*/
#include "dominion.h"
#include "test_utils.h"
#include <stdio.h>
#include <stdlib.h>

void asserttrue (char *s, int b)
{
	printf("---------------------------------\n");
	printf("TEST NAME: %s\n", s);
	printf("TEST STATUS.........................");
	if (b)
	{
		printf("PASS\n");
	}
	else
	{
		printf("FAIL\n");
	}
	printf("---------------------------------\n");
	return;
}

void randomizeGame ( struct gameState *g )
{
	int i, j;

	/* random state for game */
	memset( g, 0, sizeof(struct gameState) );
	g->numPlayers = 2;
	g->outpostPlayed = rand();
	g->outpostTurn = rand();
	g->whoseTurn = rand() % 2;
	g->phase = 0;
	g->numActions = (rand() % 100) + 1;
	g->coins = rand() % 101;
	g->numBuys = rand() % 101;
	for ( i = 0; i < g->numPlayers; i++ )
	{
		/* Player has one card in hand */
		g->handCount[i] = (rand() % MAX_HAND) + 1;
		for ( j = 0; j < g->handCount[i]; j++ )
		{
			g->hand[i][j] = rand() % (treasure_map + 1);
		}

		/* Random cards fill deck*/
		g->deckCount[i] = rand() % (MAX_DECK + 1);
		for ( j = 0; j < g->deckCount[i]; j++ )
		{
			g->deck[i][j] = rand() % (treasure_map + 1);
		}

		/* Discard pile gets fill discard with random cards */
		g->discardCount[i] = rand() % (MAX_DECK + 1);
		for ( j = 0; j < g->discardCount[i]; j++ )
		{
			g->discard[i][j] = rand() % (treasure_map + 1);
		}

		/* Played gets random cards */
		g->playedCardCount = rand() % (MAX_DECK + 1);
		for ( j = 0; j < g->playedCardCount; j++ )
		{
			g->playedCards[j] = rand() % (treasure_map + 1);
		}
	}

	return;
}
