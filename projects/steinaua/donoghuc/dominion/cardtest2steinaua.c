/*----------------------
 *Aaron Peressini
 *CS 362 Winter 2018
 *Assignment 3 : cardtest2.c
 *card test for adventurer card
 *
 *Include the following in your makefile:
 *
 *cardtest1: cardtest2.c dominion.o rngs.o
 *	gcc -o cardtest2 cardtest2.c -g dominion.o rngs.o $(CFLAGS)
 *
 *----------------------
 */

#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#define TESTCARD "adventurer"

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
	int i, j, x, coinCard;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 500;
	int k[10] = {adventurer, council_room, embargo, sea_hag, outpost, smithy, village, baron, tribute, great_hall};
	struct gameState GS, testGS;

	printf("TESTING CARD %s\n", TESTCARD);

	for(i = 0; i < MAX_PLAYERS; i++)
	{
		for(coinCard = 4; coinCard < 7; coinCard++)
		{
			printf("Player %d should have %d coins.\n", i, 7*(coinCard-3));
			memset(&GS, 23, sizeof(struct gameState)); //clear game state
			j = initializeGame(MAX_PLAYERS, k, seed, &GS); //initialize new game
			GS.deckCount[i] = 0;
			GS.handCount[i] = 0;
			for(x = 0; x < 5; x++)
			{
				gainCard(coinCard, &GS, 1, i);
				gainCard(coinCard, &GS, 2, i);
			}
			GS.whoseTurn = i;
			updateCoins(i, &GS, 0);
			//GS.handCount[i] = 5;
			memcpy(&testGS, &GS, sizeof(struct gameState));
			//printf("Player %d handcount before smithy: testGS %d, GS %d\n", i, testGS.handCount[i], GS.handCount[i]);
			cardEffect(adventurer, choice1, choice2, choice3, &testGS, handpos, &bonus);
			updateCoins(i, &testGS, 0);
			if(assertTrue(testGS.coins == GS.coins + 2*(coinCard-3)))
				printf("Test passed.\n\n");
			else{
				printf("Test failed. Player %d testGS coins: %d, GS coins: %d\n\n", i, testGS.coins, GS.coins + 2*(coinCard-3));
			}
	
		}	 
	}
	return 0;
}
