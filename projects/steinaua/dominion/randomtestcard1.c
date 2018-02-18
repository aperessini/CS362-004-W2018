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
 * 
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
	while(count < 1000)
	{
		count++;
		//printf("Entering genRanVal\n");
		generateRandomValues(&GS, k);
		//printf("Entering memcpy\n");
		memcpy(&testGS, &GS, sizeof(struct gameState));
		//printf("Entering cardEffect\n");
		cardEffect(smithy, choice1, choice2, choice3, &testGS, handpos, &bonus);
		//printf("Entering updateCoins\n");
		updateCoins(testGS.whoseTurn ,&testGS, 0);
		if(testGS.handCount[testGS.whoseTurn] != GS.handCount[GS.whoseTurn] + 3)
		{
			if(debug1)
			{
			    strcat(failMsg, "Exactly three cards were not added to hand. ");
			    debug1 = 0;
			}
			failCount++;
		} 
		else if(testGS.discardCount[testGS.whoseTurn] <= GS.discardCount[GS.whoseTurn])
		{
			if(debug2)
			{
			    strcat(failMsg, "One card was not added to discard pile. ");
			    debug2 = 0;
			}
			failCount++;
		}
	}
	printf("%s failed %d of 1000 random tests.\nFailure messages include: %s\n", TESTCARD, failCount, failMsg);

	/*printf("TESTING CARD %s\n", TESTCARD);

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
	*/
	return 0;
}
