/*----------------------
 *Aaron Peressini
 *CS 362 Winter 2018
 *Assignment 4 : randomtestcard1.c
 *random card test for smithy card
 *
 *Include the following in your makefile:
 *
 *randomtestcard1: randomtestcard1.c dominion.o rngs.o
 *	gcc -o randomtestcard1 randomtestcard1.c -g dominion.o rngs.o $(CFLAGS)
 *
 *discardCard() doesn't actually have any effect on discard pile
 *----------------------
 */

#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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

void generateRandomValues(struct gameState * GS, int * k)
{
	int i;
	int numPlayers = (rand() % 4) + 1; //Returns 1-4 players
        int seed = rand() % RAND_MAX; //Return 0 - RAND_MAX
	memset(GS, 23, sizeof(struct gameState));
	int j = initializeGame(numPlayers, k, seed, GS);
	GS->whoseTurn = rand() % numPlayers;
	GS->playedCardCount = 0;
	GS->handCount[GS->whoseTurn] = (rand() % 10) + 1; //Hand: 1-10 cards
	GS->deckCount[GS->whoseTurn] = (rand() % 11); //Deck: 0-10 cards
	GS->discardCount[GS->whoseTurn] = (rand() % 9) + 3; //Discard: 3-11 cards, make sure there are at least 3 cards to draw
	// Fill hand 
	GS->hand[GS->whoseTurn][0] = smithy;
	for(i = 1; i < GS->handCount[GS->whoseTurn]; i++)
	{
		GS->hand[GS->whoseTurn][i] = rand() % 27;
	}
	updateCoins(GS->whoseTurn, GS, 0);//Match coins with hand treasure count

	// Fill deck
	for(i = 0; i < GS->deckCount[GS->whoseTurn]; i++)
        {
                GS->deck[GS->whoseTurn][i] = rand() % 27;
	}

	//Fill discard
	for(i = 0; i < GS->discardCount[GS->whoseTurn]; i++)
        {
                GS->discard[GS->whoseTurn][i] = rand() % 27;
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

	int failCount = 0, debug1 = 1, debug2 = 1;
	char failMsg[255];
	memset(failMsg, '\0', 255);
	printf("TESTING CARD %s\n", TESTCARD);
	while(count < 10000)
	{
		count++;
		//printf("Entering genRanVal\n");
		generateRandomValues(&GS, k);
		//printf("Entering memcpy\n");
		memcpy(&testGS, &GS, sizeof(struct gameState));
		//printf("Entering cardEffect\n");
		//printf("Test dis count: %d, GS dis count: %d ", testGS.discardCount[testGS.whoseTurn], GS.discardCount[GS.whoseTurn]);
		//printf("BEFORE Test dis count: %d, deck count: %d, GS dis count: %d, deck count: %d  ", testGS.discardCount[testGS.whoseTurn], testGS.deckCount[testGS.whoseTurn], GS.discardCount[GS.whoseTurn], GS.deckCount[GS.whoseTurn]);
		cardEffect(smithy, choice1, choice2, choice3, &testGS, handpos, &bonus);
		//printf("Entering updateCoins\n");
		int failFlag = 0;
		updateCoins(testGS.whoseTurn ,&testGS, 0);
		/*if(testGS.handCount[testGS.whoseTurn] != GS.handCount[GS.whoseTurn] + 2)
		{
			if(debug1)
			{
			    strcat(failMsg, "Exactly one card was not discarded. ");
			    debug1 = 0;
			}
			failCount++;
			failFlag = 1;
		}*/
		//printf("AFTER Test dis count: %d, deck count: %d, GS dis count: %d, deck count: %d \n ", testGS.discardCount[testGS.whoseTurn], testGS.deckCount[testGS.whoseTurn], GS.discardCount[GS.whoseTurn], GS.deckCount[GS.whoseTurn]); 
		if(testGS.discardCount[testGS.whoseTurn] + testGS.deckCount[testGS.whoseTurn] + 3 != GS.discardCount[GS.whoseTurn] + GS.deckCount[GS.whoseTurn])
		{
			if(debug2)
			{
			    strcat(failMsg, "Exactly three cards were not added to hand. ");
			    debug2 = 0;
			}
			if(!failFlag)
			{
			    failCount++;
			    failFlag = 1;
			}
		}
	}
	if(!failCount)
	    strcat(failMsg, "All tests passed!\n");
	printf("%s failed %d of 10000 random tests.\nFailure messages include: %s\n", TESTCARD, failCount, failMsg);

			
	return 0;
}
