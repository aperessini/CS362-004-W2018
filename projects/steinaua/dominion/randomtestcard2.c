/*----------------------
 *Aaron Peressini
 *CS 362 Winter 2018
 *Assignment 4 : randomtestcard2.c
 *random card test for council_room card
 *
 *Include the following in your makefile:
 *
 *randomtestcard2: randomtestcard2.c dominion.o rngs.o
 *	gcc -o randomtestcard2 randomtestcard2.c -g dominion.o rngs.o $(CFLAGS)
 * 
 *----------------------
 */

#include "dominion.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "rngs.h"
#define TESTCARD "council room"

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
	int i, y;
	int numPlayers = (rand() % 3) + 2; //Returns 1-4 players
        int seed = rand() % RAND_MAX; //Return 0 - RAND_MAX
	memset(GS, 23, sizeof(struct gameState));
	int j = initializeGame(numPlayers, k, seed, GS);
	GS->whoseTurn = rand() % numPlayers;
	//printf("Num players is %d, GS->whoseTurn is %d\n", numPlayers, GS->whoseTurn);
	GS->playedCardCount = 0;
	/*for(i = 0; i < numPlayers; i++)
        {
	    
	    GS->handCount[i] = 5;
            GS->deckCount[i] = 5;
            GS->discardCount[i] = 5;
	    for(y = 0; y < 5; y++)
            {
	        gainCard(y, &GS, 0, i);
	        gainCard(y, &GS, 1, i);
	        gainCard(y, &GS, 2, i);
            }
	    
	}
        */
	//printf("%d\n", GS->handCount);
	GS->handCount[GS->whoseTurn] = (rand() % 10) + 1; //Hand: 1-10 cards
	//printf("Handcount: %d\n", GS->handCount[GS->whoseTurn]);
	GS->deckCount[GS->whoseTurn] = (rand() % 9) + 12; //Deck: 2-10 cards
	//printf("Handcount: %d\n", GS->deckCount[GS->whoseTurn]);
	GS->discardCount[GS->whoseTurn] = (rand() % 9) + 12; //Discard: 2-10 cards
	//printf("Handcount: %d\n", GS->discardCount[GS->whoseTurn]);
	// Fill hand 
	GS->hand[GS->whoseTurn][0] = council_room;
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
	int count = 0, i;
	int handpos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	int k[10] = {adventurer, council_room, embargo, sea_hag, outpost, smithy, village, baron, tribute, great_hall};
	struct gameState GS, testGS;

	int failCount = 0, debug1 = 1, debug2 = 1, debug3 = 1;
	char failMsg[255];
	memset(failMsg, '\0', 255);
	printf("TESTING CARD %s\n", TESTCARD);
	while(count < 10000)
	{
		count++;
		generateRandomValues(&GS, k);
		memcpy(&testGS, &GS, sizeof(struct gameState));
  		//printf("Player 1 handcount: %d deckCount: %d\n", GS.handCount[1], GS.deckCount[1]);
		//printf("Handcount before council room %d", testGS.handCount[testGS.whoseTurn]);
		cardEffect(council_room, choice1, choice2, choice3, &testGS, handpos, &bonus);
		updateCoins(testGS.whoseTurn ,&testGS, 0);
		//printf("Handcount after council room %d", testGS.handCount[testGS.whoseTurn]);
		int failFlag = 0;
		for(i = 0; i < testGS.numPlayers; i++)
		{
		    if(testGS.whoseTurn == i)
		    {
			if(testGS.handCount[testGS.whoseTurn] != GS.handCount[GS.whoseTurn] + 3)
                	{
                            if(debug1)
                            {
                                strcat(failMsg, "Exactly four cards were not added to the current player's hand. ");
                                debug1 = 0;
                            }
                            failCount++;
		            failFlag = 1;
                	}
		    
		    	if(testGS.numBuys != GS.numBuys + 1)
                    	{
                            if(debug2)
                            {
                                strcat(failMsg, "Current player did not gain exactly one buy. ");
                                debug2 = 0;
                            }
			    if(!failFlag)
			    {
                                failCount++;
				failFlag = 1;
			    }
                    	}
		    }
		    else if(testGS.handCount[i] != GS.handCount[i] + 1)
		    {
		        if(debug3)
		        {
			    char msg[100];
			    snprintf(msg, 100, "Player %d did not draw exactly one card. ", i);
		            strcat(failMsg, msg);
			    debug3 = 0;
			}
			if(!failFlag)
			{
			    failCount++;
			    failFlag = 1;
			}
		    }
		    		    
		}
	}
	if(failCount == 0)
	    strcat(failMsg, "All tests passed. ");
	printf("%s failed %d of 10000 random tests.\nFailure messages include: %s\n", TESTCARD, failCount, failMsg);
	
	return 0;
}
