/*----------------------
 *Aaron Peressini
 *CS 362 Winter 2018
 *Assignment 3 : unittest3.c
 *unit test for function getWinners()
 *
 *Include the following in your makefile:
 *
 *unittest3: unittest3.c dominion.o rngs.o
 *	gcc -o unittest3 unittest3.c -g dominion.o rngs.o $(CFLAGS)
 *
 *----------------------
 */

#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"



int assertTrue(int statement)
{
	if(!statement)
	{
		//printf("Statement is false!\n");
		return 0;
	}

	else
	{	
		//printf("Statement is true!\n");
		return 1;
	}
}

int main()
{	
	int i, j, handCount = 5, deckCount = 5, discardCount = 5;
	int maxScore = 80, seed = 500;
	int players[MAX_PLAYERS];
	int k[10] = {adventurer, council_room, embargo, sea_hag, outpost, smithy, village, baron, tribute, great_hall};
	struct gameState GS;

	printf("TESTING FUNCTION getWinners():\n");

	for(i = 0; i < MAX_PLAYERS; i++)
	{
		printf("Player %d should win this game.\n\n", i);
		memset(&GS, 23, sizeof(struct gameState)); //clear game state
		j = initializeGame(MAX_PLAYERS, k, seed, &GS); //initialize new game
		
		GS.whoseTurn = i;
		GS.handCount[i] = handCount;
		GS.deckCount[i] = deckCount;
		GS.discardCount[i] = discardCount;
		for(j = 0; j < handCount; j++)
		{
			GS.hand[i][j] = province;
			GS.deck[i][j] = province;
			GS.discard[i][j] = province;
		}
		getWinners(players, &GS);
		for(j = 0; j < MAX_PLAYERS; j++)
		{
			if(assertTrue(players[j]))
				printf("Player %d is a great winner.\n", j);
			else
				printf("Player %d is a total loser.\n", j);
			
		}
		//assertTrue(players[i]);
		printf("\n\n");
		
	}
	return 0;
}
