/*----------------------
 *Aaron Peressini
 *CS 362 Winter 2018
 *Assignment 3 : cardtest3.c
 *card test for sea_hag card
 *
 *Include the following in your makefile:
 *
 *cardtest3: cardtest3.c dominion.o rngs.o
 *	gcc -o cardtest3 cardtest3.c -g dominion.o rngs.o $(CFLAGS)
 *
 *----------------------
 */

#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#define TESTCARD "sea_hag"

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
		printf("All players except player %d should have a curse card at the top of their deck.\n", i);
		memset(&GS, 23, sizeof(struct gameState)); //clear game state
		j = initializeGame(MAX_PLAYERS, k, seed, &GS); //initialize new game
		GS.handCount[i] = 0;
		for(x = 0; x < 5; x++)
		{
			gainCard(x, &GS, 1, 0);
			gainCard(x, &GS, 1, 1);
			gainCard(x, &GS, 1, 2);
			gainCard(x, &GS, 1, 3);
			gainCard(x, &GS, 2, 0);
			gainCard(x, &GS, 2, 1);
			gainCard(x, &GS, 2, 2);
			gainCard(x, &GS, 2, 3);
		}
		GS.whoseTurn = i;
		memcpy(&testGS, &GS, sizeof(struct gameState));
				
		cardEffect(sea_hag, choice1, choice2, choice3, &testGS, handpos, &bonus);
		int passFlag;
		for(x = 0; x < MAX_PLAYERS; x++)
		{
			if((x == i && testGS.deck[x][testGS.deckCount[x] - 1] == curse) || (x != i && testGS.deck[x][testGS.deckCount[x] - 1] != curse))
			{
				//printf("In cardtest3: deck top Card expected number:0, actual:%d\n", testGS.deck[x][testGS.deckCount[x] - 1]);
				passFlag = 0;
				break;
			}
			else
			{
				passFlag = 1;
			}
		}
		
		if(passFlag)
			printf("Test passed.\n\n");
		else{
			printf("Test failed. Player %d had the incorrect card, no. %d, on top of their deck, instead of card no. 0.\n\n", x, testGS.deckCount[x]-1);
		}
	
	} 

	return 0;
}
