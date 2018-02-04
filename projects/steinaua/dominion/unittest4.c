/*----------------------
 *Aaron Peressini
 *CS 362 Winter 2018
 *Assignment 3 : unittest4.c
 *unit test for function supplyCount()
 *
 *Include the following in your makefile:
 *
 *unittest4: unittest4.c dominion.o rngs.o
 *	gcc -o unittest4 unittest4.c -g dominion.o rngs.o $(CFLAGS)
 *
 *----------------------
 */

#include "dominion.h"
#include "dominion_helpers.h"
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
	int i, j, c, supplycount, passFlag;
	int maxSupplyCount = 10, seed = 500;
	int k[10] = {adventurer, council_room, embargo, sea_hag, outpost, smithy, village, baron, tribute, great_hall};
	struct gameState GS;

	printf("TESTING FUNCTION supplyCount():\n");

	for(supplycount = 0; supplycount < maxSupplyCount; supplycount++)
	{
		for(c = curse; c < treasure_map; c++)
		{

			//printf("Supply count of card %d should be %d.\n", c, supplycount);
			memset(&GS, 23, sizeof(struct gameState)); //clear game state
			j = initializeGame(MAX_PLAYERS, k, seed, &GS); //initialize new game
			GS.whoseTurn = i;
			GS.supplyCount[c] = supplycount;
			if(assertTrue(supplyCount(c, &GS) == supplycount))
				passFlag = 1; //printf("Test passed.\n");
			else{
				printf("Test failed on card %d and supply count %d\n", c, supplycount);
				break;
			}

		}

	} 

	if(passFlag)
	{
		printf("All tests passed!\n");
	}

	return 0;
}
