/***********************************
* Name: Andrew Demers
* Date: 11/17/19
* CS362 - 400
* Assignment 4 - randomtestcard1.c
* Description: This file contains a random tester for the baron card.
***********************************/

#include "dominion.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include <string.h>

int main() {
	int seed = 1000;
	int numPlayers = 2;
	int curPlayer = 0;
	struct gameState G;
	int deck[10] = {baron, minion, ambassador, tribute, gardens, mine, remodel, smithy,
				 village, estate};

	int i, j , k;
	int deckSize, handSize, handPos = 0;
	int randomCard = 0, random = 0;
	int estateCount, estateCountOld;
	int coinCount, coinCountOld;
	int discardEstate = 0;
	int choice1 = 0;

	int testPassed = 0;
	int drawTestFailed = 0;
	int discardTestFailed = 0;

	srand(time(NULL));	// seed random

	printf("\n----------Start testing baron card----------\n");

	// initialize game and randomize hand size 10,000 times
	for (i = 0; i < 10000; i++) {
		memset(&G, 23, sizeof(struct gameState));    // clear game state
		initializeGame(numPlayers, deck, seed, &G);

		// randomize hand size based on deck size
		deckSize = rand() % (MAX_DECK + 1);
		handSize = rand() % (deckSize + 1);

		G.deckCount[0] = deckSize - handSize;
		G.handCount[0] = handSize;

		// randomize number of coin cards each player has
		for (j = 0; j < numPlayers; j++) {
			for (k = 0; k < G.deckCount[j]; k++) {
				randomCard = rand() % (50 + 1);
				random = rand() % 10;

				switch (randomCard) {
					case 1:
						G.deck[j][k] = copper;
					case 2:
						G.deck[j][k] = silver;
					case 3:
						G.deck[j][k] = gold;
					default:
						G.deck[j][k] = deck[random];
				}
			}
		}

		// randomize choice 1 to either 0 or 1
		choice1 = rand() % 2;

		// get old estate count
		for (j = 0; j < G.handCount[curPlayer]; j++) {
			if (G.hand[curPlayer][j] == estate) {
				estateCountOld = 0;
			}
		}


		// get old coin count
		coinCountOld = 0;
		for (j = 0; j < G.handCount[curPlayer]; j++) {
			if (G.hand[curPlayer][j] == copper || G.hand[curPlayer][j] == silver || G.hand[curPlayer][j] == gold) {
				coinCountOld++;
			}
		}

		baronCard(choice1, curPlayer, &G);	// call baron card's effect
		//cardEffect(baron, choice1, 0, 0, &G, handPos, 0);

		// get current estate count
		estateCount = 0;
		for (j = 0; j < G.handCount[curPlayer]; j++) {
			if (G.hand[curPlayer][j] == estate) {
				estateCount++;
			}
		}

		// get count of discarded estates
		discardEstate = 0;
		for (j = 0; j < G.discardCount[curPlayer]; j++) {
			if (G.discard[curPlayer][j] == estate) {
				discardEstate++;
			}
		}

		// get current coin count
		coinCount = 0;
		for (j = 0; j < G.handCount[curPlayer]; j++) {
			if (G.hand[curPlayer][j] == copper || G.hand[curPlayer][j] == silver || G.hand[curPlayer][j] == gold) {
				coinCount++;
			}
		}

		// start of tests
		bool passed = true;

		// check if discarding an estate works correctly
		if (estateCount > (estateCountOld - 1) && choice1 == 1) {
			printf("Failed test: Estate card was not discarded.\n");
			discardTestFailed++;
			passed = false;
		}

		// check if drawing an estate works correctly
		if (estateCount != (estateCountOld + 1) && choice1 == 0) {
			printf("Failed test: Estate card was not drawn.\n");
			drawTestFailed++;
			passed = false;
		}


		if (coinCount != (coinCountOld + 4) && choice1 == 1) {
			printf("Failed test: Player did not gain coins.\n");
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


	printf("\n----------End testing baron card----------\n");

	return 0;
}