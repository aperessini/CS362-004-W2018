/*----------------------
 *Aaron Peressini
 *CS 362 Winter 2018
 *Assignment 4 : randomtestadventurer.c
 *random card test for adventurer card
 *
 *Include the following in your makefile:
 *
 *randomtestadventurer: randomtestadventurer.c dominion.o rngs.o
 *	gcc -o randomtestadventurer randomtestadventurer.c -g dominion.o rngs.o $(CFLAGS)
 *
 *
 * Since adventurer will (incorrectly) enter an infinite loop if there are not 
 * treasure cards total in the deck + discard, I opted to ensure there are at 
 * least 2 total treasure cards. Also, calling shuffle is useless in the fnctn
 *----------------------
 */

#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

void generateRandomValues(struct gameState * GS, int * k, int * treasureCount)
{
	int i;
	int numPlayers = (rand() % 4) + 1; //Returns 1-4 players
        int seed = rand() % RAND_MAX; //Return 0 - RAND_MAX
	memset(GS, 23, sizeof(struct gameState));
	int j = initializeGame(numPlayers, k, seed, GS);
	GS->whoseTurn = rand() % numPlayers;
	GS->handCount[GS->whoseTurn] = (rand() % 10) + 1; //Hand: 1-10 cards
	GS->deckCount[GS->whoseTurn] = (rand() % 11); //Deck: 0-10 cards
	GS->discardCount[GS->whoseTurn] = (rand() % 9) + 2; //Discard: 2-10 cards
	// Fill hand 
	GS->hand[GS->whoseTurn][0] = adventurer;
	for(i = 1; i < GS->handCount[GS->whoseTurn]; i++)
	{
		GS->hand[GS->whoseTurn][i] = rand() % 27;
	}
	updateCoins(GS->whoseTurn, GS, 0);//Match coins with hand treasure count

	// Fill deck
	int val;
	*treasureCount = 0;
	for(i = 0; i < GS->deckCount[GS->whoseTurn]; i++)
        {
                val = GS->deck[GS->whoseTurn][i] = rand() % 27;
		if(val > 3 && val < 7)
			*treasureCount++;
	}
	//Fill discard
	for(i = 0; i < GS->discardCount[GS->whoseTurn]; i++)
        {
                val = GS->discard[GS->whoseTurn][i] = rand() % 27;
		if(val > 3 && val < 7)
                        *treasureCount++;
		if(i > GS->discardCount[GS->whoseTurn]-3 && *treasureCount < 2)
                {
                        //Make sure there are at least 2 treasure cards total
                        GS->discard[GS->whoseTurn][i] = (rand() % 3) + 4;
                }
        }

}

int main()
{	
	time_t t;
	srand((unsigned) time(&t));
	int count = 0;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int k[10] = {adventurer, council_room, embargo, sea_hag, outpost, smithy, village, baron, tribute, great_hall};
	struct gameState GS, testGS;

	int failCount = 0, treasureCount, debug1 = 1, debug2 = 1;
	char failMsg[255];
	memset(failMsg, '\0', 255);
	printf("TESTING CARD %s\n", TESTCARD);
	while(count < 10000)
	{
		count++;
		generateRandomValues(&GS, k, &treasureCount);
		memcpy(&testGS, &GS, sizeof(struct gameState));
		cardEffect(adventurer, choice1, choice2, choice3, &testGS, handpos, &bonus);
		updateCoins(testGS.whoseTurn ,&testGS, 0);
		int failFlag = 0;
		if(testGS.handCount[testGS.whoseTurn] != GS.handCount[GS.whoseTurn] + 2)
		{
			if(debug1)
			{
			    strcat(failMsg, "Exactly two cards were not added to the current player's hand. ");
			    debug1 = 0;
			}
			failCount++;
			failFlag = 1;
		} 
		if(testGS.coins < GS.coins + 2)
		{
			if(debug2)
			{
			    strcat(failMsg, "Two treasure cards were not added to the current player's hand. ");
			    debug2 = 0;
			}
			if(!failFlag)
			{
			    failCount++;
			    failFlag = 1;
			}
			
		}
	}
	printf("%s failed %d of 10000 random tests.\nFailure messages include: %s\n", TESTCARD, failCount, failMsg);

	
	return 0;
}
