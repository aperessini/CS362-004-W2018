/*----------------------
 *Aaron Peressini
 *CS 362 Winter 2018
 *Assignment 3 : unittest1.c
 *unit test for function numHandCards()
 *
 *Include the following in your makefile:
 *
 *unittest1: unittest1.c dominion.o rngs.o
 *	gcc -o unittest1 unittest1.c -g dominion.o rngs.o $(CFLAGS)
 *
 *----------------------
 */

#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"


//Function being tested
/*int numHandCards(struct gameState *state) {
  return state->handCount[ whoseTurn(state) ];
}*/

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
	int i, j, handCount, passFlag;
	int maxHandCount = 5, seed = 500;
	int k[10] = {adventurer, council_room, embargo, sea_hag, outpost, smithy, village, baron, tribute, great_hall};
	struct gameState GS;

	printf("TESTING FUNCTION numHandCards():\n");

	for(i = 0; i < MAX_PLAYERS; i++)
	{
		for(handCount = -1; handCount < maxHandCount; handCount++)
		{

			//printf("Player %d should have %d cards in their hand.\n", i, handCount);
			memset(&GS, 23, sizeof(struct gameState)); //clear game state
			j = initializeGame(MAX_PLAYERS, k, seed, &GS); //initialize new game
			GS.whoseTurn = i;
			GS.handCount[i] = handCount;
			if(assertTrue(numHandCards(&GS) == handCount))
				passFlag = 1; //printf("Test passed.\n");
			else
				printf("Test failed on player %d with handcount of %d.\n", i, handCount);

		}

	} 
	if(passFlag)
		printf("All tests passed!\n");


	return 0;
}
