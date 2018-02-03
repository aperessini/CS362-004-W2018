/*----------------------
 *Aaron Peressini
 *CS 362 Winter 2018
 *Assignment 3 : cardtest1.c
 *card test for smithy card
 *
 *Include the following in your makefile:
 *
 *cardtest1: cardtest1.c dominion.o rngs.o
 *	gcc -o cardtest1 cardtest1.c -g dominion.o rngs.o $(CFLAGS)
 *
 *----------------------
 */

#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#define TESTCARD "smithy"

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
	int i, j, x, cardsDrawn = 3, cardsDiscarded = 1;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 500;
	int k[10] = {adventurer, council_room, embargo, sea_hag, outpost, smithy, village, baron, tribute, great_hall};
	struct gameState GS, testGS;

	printf("TESTING CARD %s\n", TESTCARD);

	for(i = 0; i < MAX_PLAYERS; i++)
	{
		printf("Player %d should draw %d cards.\n", i, cardsDrawn);
		memset(&GS, 23, sizeof(struct gameState)); //clear game state
		j = initializeGame(MAX_PLAYERS, k, seed, &GS); //initialize new game
		for(x = 0; x < 10; x++)
		{
			gainCard(1, &GS, 1, i );
		}
		GS.whoseTurn = i;
		GS.handCount[i] = 5;
		memcpy(&testGS, &GS, sizeof(struct gameState));
		//printf("Player %d handcount before smithy: testGS %d, GS %d\n", i, testGS.handCount[i], GS.handCount[i]);
		cardEffect(smithy, choice1, choice2, choice3, &testGS, handpos, &bonus);
		
		if(assertTrue(testGS.handCount[i] == GS.handCount[i] + cardsDrawn - cardsDiscarded))
			printf("Test passed.\n");
		else{
			printf("Test failed. Player %d testGS handcount: %d, GS handcount: %d\n", i, testGS.handCount[i], GS.handCount[i] + cardsDrawn - cardsDiscarded);
		}
	
	} 

	return 0;
}
