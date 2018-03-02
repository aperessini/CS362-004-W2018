/*----------------------
 *Aaron Peressini
 *CS 362 Winter 2018
 *Assignment 3 : unittest2.c
 *unit test for function fullDeckCount()
 *
 *Include the following in your makefile:
 *
 *unittest2: unittest2.c dominion.o rngs.o
 *	gcc -o unittest2 unittest2.c -g dominion.o rngs.o $(CFLAGS)
 *
 *----------------------
 */

#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include "rngs.h"


//Function being tested
/*int fullDeckCount(int player, int card, struct gameState *state) {
  int i;
  int count = 0;

  for (i = 0; i < state->deckCount[player]; i++)
    {
      if (state->deck[player][i] == card) count++;
    }

  for (i = 0; i < state->handCount[player]; i++)
    {
      if (state->hand[player][i] == card) count++;
    }

  for (i = 0; i < state->discardCount[player]; i++)
    {
      if (state->discard[player][i] == card) count++;
    }

  return count;
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
	int i, j, a, c, handCount, deckCount, discardCount, passFlag;
	int maxHandCount = 5, maxDeckCount = 5, maxDiscardCount = 5, seed = 500;
	int k[10] = {adventurer, council_room, embargo, sea_hag, outpost, smithy, village, baron, tribute, great_hall};
	struct gameState GS;

	printf("TESTING FUNCTION fullDeckCount():\n");

	for(i = 0; i < 1; i++)
	{
	  for(deckCount = 0; deckCount < maxDeckCount; deckCount++)
	  {
	    for(discardCount = 0; discardCount < maxDiscardCount; discardCount++)
	    {
	      for(handCount = 0; handCount < maxHandCount; handCount++)
	      {
		for(c = curse; c < treasure_map; c++)
		{
			//int k[10] = {c, c, c, c, c, c, c, c, c, c};
			//printf("Player %d should have %d of card %d combined in their hand, deck, and discard pile.\n", i, handCount+deckCount+discardCount, c);
			memset(&GS, 23, sizeof(struct gameState)); //clear game state
			//printf("Initializing Game\n");
			j = initializeGame(MAX_PLAYERS, k, seed, &GS); //initialize new game
			//printf("Setting player turn\n");
			GS.whoseTurn = i;
			//printf("Setting handcount\n");
			GS.handCount[i] = handCount;
			memset(GS.hand[i], 0, handCount * sizeof(int));
			for(a = 0; a < GS.handCount[i]; a++)
			{
				GS.hand[i][a] = c;
			}
			//printf("Setting deckcount\n");
			GS.deckCount[i] = deckCount;
			memset(GS.deck[i], 0, deckCount * sizeof(int));
			for(a = 0; a < GS.deckCount[i]; a++)
                        {
                                GS.deck[i][a] = c;
                        }
			//printf("Setting discardcount\n");
			GS.discardCount[i] = discardCount;
			memset(GS.discard[i], 0, discardCount * sizeof(int));
			for(a = 0; a < GS.discardCount[i]; a++)
                        {
                                GS.discard[i][a] = c;
                        }
			//printf("Testing fullDeckCount()\n");
			
			
			if(assertTrue(fullDeckCount(i, c, &GS) == handCount + deckCount + discardCount))
				passFlag = 1;//printf("Test passed.\n");
			else{
				printf("Test for player %d w/ deckCount %d, handCount %d, discardCount %d and card no. %d failed.\n", i, deckCount, handCount, discardCount, c);
				break;
			}
			//free(GS);
		}
	      }
	    }
	  }
	} 

	if(passFlag)
		printf("All tests passed!\n");
	return 0;
}
