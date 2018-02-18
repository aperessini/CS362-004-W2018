/*----------------------
 *Aaron Peressini
 *CS 362 Winter 2018
 *Assignment 3 : cardtest4.c
 *card test for council_room card
 *
 *Include the following in your makefile:
 *
 *cardtest4: cardtest4.c dominion.o rngs.o
 *	gcc -o cardtest4 cardtest4.c -g dominion.o rngs.o $(CFLAGS)
 *
 *----------------------
 */

#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"
#define TESTCARD "council_room"

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
	int i, j, x, y, cardsDrawn = 4, cardsDiscarded = 1;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int seed = 500;
	int k[10] = {adventurer, council_room, embargo, sea_hag, outpost, smithy, village, baron, tribute, great_hall};
	struct gameState GS, testGS;

	printf("TESTING CARD %s\n", TESTCARD);

	for(i = 0; i < MAX_PLAYERS; i++)
	{
		printf("Player %d should draw %d cards and gain 1 buy and all other players should draw 1 card.\n", i, cardsDrawn);
		memset(&GS, 23, sizeof(struct gameState)); //clear game state
		j = initializeGame(MAX_PLAYERS, k, seed, &GS); //initialize new game
		GS.handCount[0] = 0;
		for(x = 0; x < MAX_PLAYERS; x++)
		{
			for(y = 0; y < 5; y++)
			{
				gainCard(y, &GS, 1, x);
				gainCard(y, &GS, 2, x);
			}
			printf("Before playing council room: Player %d handcount is %d\n", x, GS.handCount[x]);
		}
		GS.whoseTurn = i;
		memcpy(&testGS, &GS, sizeof(struct gameState));
		//printf("Player %d handcount before smithy: testGS %d, GS %d\n", i, testGS.handCount[i], GS.handCount[i]);
		printf("Number of buys before council room is %d\n", testGS.numBuys);
		cardEffect(council_room, choice1, choice2, choice3, &testGS, handpos, &bonus);
		printf("Number of buys after council room is %d\n", testGS.numBuys);
		int passFlag;
		for(y = 0; y < MAX_PLAYERS; y++)
		{
			printf("After playing council room: Player %d handcount is %d\n", y, testGS.handCount[y]);
			if(assertTrue((y == i && testGS.handCount[y] == GS.handCount[y] + cardsDrawn - cardsDiscarded && testGS.numBuys == GS.numBuys + 1) || y!=i && testGS.handCount[y] == GS.handCount[y] + 1))
				passFlag = 1; //printf("Test passed.\n");
			else{
				passFlag = 0;
				break; //printf("Test failed. Player %d testGS handcount: %d, GS handcount: %d\n", i, testGS.handCount[i], GS.handCount[i] + cardsDrawn - cardsDiscarded);
			}
		}
		if(passFlag)
		{
			printf("Test passed!\n\n");
		}
		else
		{
			printf("Test failed. Player %d has incorrect number of cards in hand or buys.\n\n", y); 
		}
	
	} 

	return 0;
}
