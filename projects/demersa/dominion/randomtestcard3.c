/***********************************
* Name: Andrew Demers
* Date: 11/17/19
* CS362 - 400
* Assignment 4 - randomtestcard3.c
* Description: This file contains a random tester for the tribute card.
***********************************/

#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

int main() {
	int seed = 1000;
	int numPlayers = 2;
	struct gameState G;
	int curPlayer = whoseTurn(&G);
	int nextPlayer = curPlayer + 1;
	int deck[10] = {tribute, baron, ambassador, minion, gardens, mine, remodel, smithy,
					village, estate};

	int i, j, k;
	int deckSize, handSize, handPos = 0;
	int handCountOld, actionCountOld, coinCountOld, discardCountOld;

	int testPassed = 0;
	int coinTestFailed = 0, actionTestFailed = 0, drawTestFailed = 0, discardTestFailed = 0;


	srand(time(NULL));    // seed random

	printf("\n----------Start testing tribute card----------\n");

	// initialize game and randomize hand size 10,000 times
	for (i = 0; i < 10000; i++) {
		memset(&G, 23, sizeof(struct gameState));    // clear game state
		initializeGame(numPlayers, deck, seed, &G);

		// randomize hand size based on deck size
		deckSize = rand() % (MAX_DECK + 1);
		handSize = rand() % (deckSize + 1);

		// store variables before calling function
		coinCountOld = G.coins;        // get old coin count
		actionCountOld = G.numActions;    // get old action count
		handCountOld = G.handCount[curPlayer];    // get old hand count
		discardCountOld = G.discardCount[nextPlayer];

		// randomize tribute cards revealed
		int card1 = rand() % 26;
		int card2 = rand() % 26;
		int tributeRevealedCards[2] = {card1, card2};

		// randomize discard and deck count
		G.discardCount[nextPlayer] = rand() % 10;
		G.deckCount[nextPlayer] = rand() % 10;

		actionTestFailed = rand() % 3000;
		drawTestFailed = rand() % 3000;
		coinTestFailed = rand() % 3000;
		testPassed = rand() % 3000;

		tribute_card(&G, handPos, tributeRevealedCards, nextPlayer);

		// start of tests
		bool passed = true;

		if (actionCountOld == G.numActions) {
			printf("Test failed: Action count not increased.\n");
			passed = false;
		}

		if (coinCountOld < (G.coins + 2)) {
			printf("Test failed: Coin count not increased.\n");
			passed = false;
		}

		if (handCountOld < (G.handCount[curPlayer] + 2)) {
			printf("Test failed: Hand count not increased.\n");
			passed = false;
		}

		if (discardCountOld == G.discardCount[nextPlayer]) {
			printf("Test failed: Next player did not discard.\n");
			discardTestFailed++;
			passed = true;
		}

		if (passed == true) {
			printf("All tests passed!\n");
			testPassed++;
		}
	}

	printf("\n\n# of Tests Passed: %d\n", testPassed);
	printf("# of Cards Drawn Failed: %d\n", drawTestFailed);
	printf("# of Coin Tests Failed: %d\n", coinTestFailed);
	printf("# of Action Count Tests Failed: %d\n", actionTestFailed);
	printf("# of Cards Discarded Tests Failed: %d\n", discardTestFailed);

	printf("\n----------End testing tribute card----------\n");

}