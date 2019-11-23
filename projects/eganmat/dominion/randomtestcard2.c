/***********************************
* Name: Andrew Demers
* Date: 11/17/19
* CS362 - 400
* Assignment 4 - randomtestcard2.c
* Description: This file contains a random tester for the minion card.
***********************************/

#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdbool.h>

int main() {
	int seed = 100;
	int numPlayers = 2;
	struct gameState G;
	int curPlayer = whoseTurn(&G);
	int deck[10] = {minion, baron, ambassador, tribute, gardens, mine, remodel, smithy,
					village, estate};

	int i, j, k;
	int deckSize, handSize, handPos = 0;
	int handCount, handCountOld;
	int coinCount, coinCountOld;
	int discardCount, discardCountOld;
	int choice1 = 0, choice2 = 0;

	int testPassed = 0;
	int drawTestFailed = 0;
	int discardTestFailed = 0;

	srand(time(NULL));    // seed random

	printf("\n----------Start testing minion card----------\n");

	// initialize game and randomize hand size 10,000 times
	for (i = 0; i < 10000; i++) {
		memset(&G, 23, sizeof(struct gameState));    // clear game state
		initializeGame(numPlayers, deck, seed, &G);

		// randomize hand size based on deck size
		deckSize = rand() % (MAX_DECK + 1);
		handSize = rand() % (deckSize + 1);

		// get old coin count
		coinCountOld = 0;
		for (j = 0; j < G.handCount[curPlayer]; j++) {
			if (G.hand[curPlayer][j] == copper || G.hand[curPlayer][j] == silver || G.hand[curPlayer][j] == gold) {
				coinCountOld++;
			}
		}

		// get old hand count
		handCountOld = G.handCount[curPlayer];

		// get old discard count
		discardCountOld = G.discardCount[curPlayer];

		// randomize choice 1 and 2
		choice1 = rand() % 2;
		choice2 = rand() % 2;

		minionCard(choice1, choice2, handPos, curPlayer, &G);


		// get current coin count
		coinCount = 0;
		for (j = 0; j < G.handCount[curPlayer]; j++) {
			if (G.hand[curPlayer][j] == copper || G.hand[curPlayer][j] == silver || G.hand[curPlayer][j] == gold) {
				coinCount++;
			}
		}

		// get current card and discount count
		handCount = G.handCount[curPlayer];
		discardCount = G.discardCount[curPlayer];

		// start of tests
		bool passed = true;

		// check if discarded works with minion
		if (discardCount == (discardCountOld) && choice1 != 1 && choice2 == 1) {
			printf("Test failed: Player's hand was not discarded.\n");
			discardTestFailed++;
			passed = false;
		}

		// check if hand count changed
		if (handCountOld == handCount && choice1 != 1 && choice2 == 1) {
			printf("Test failed: Player did not draw new cards.\n");
			drawTestFailed++;
			passed = false;
		}

		// check if coins were gained
		if (coinCount < coinCountOld + 2 && choice1 == 1) {
			printf("Test failed: Player did not gain coins.\n");
			drawTestFailed++;
			passed = false;
		}

		if (passed == true) {
			printf("All tests passed!\n");
			testPassed++;
		}
	}

	printf("\n\n# of Tests Passed: %d\n", testPassed);
	printf("# of Cards Drawn Failed: %d\n", drawTestFailed);
	printf("# of Cards Discarded Failed: %d\n", discardTestFailed);


	printf("\n----------End testing minion card----------\n");


}