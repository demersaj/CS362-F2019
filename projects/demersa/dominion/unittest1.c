/**************************************
 * Author: Andrew Demers
 * CS 362 - Assignment 3
 * File: unittest1.c
 * Description: Tests the baron card functions as it should. Looks specifically for my
 * 		bugs.
 **************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// custom defined assert function
#define STR(x) #x
#define _ASSERT(x) if (!(x)) { printf("Assertion failed: (%s), function %s, file %s, line %d.\n", STR(x), __PRETTY_FUNCTION__, __FILE__, __LINE__); } else { printf("Assertion passed: (%s)\n", STR(x)); };


int main (int argc, char** argv) {

	// set state of variables
	int handPos = 0, choice1 = 0, choice2 = 0, choice3 = 0, bonus = 0;
	struct gameState state;
	int numPlayers = 2;
	int player = 0;
	int k[10] = {baron, minion, ambassador, tribute, gardens, mine, remodel, smithy,
				 village, estate};

	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	printf("\n----------Begin Testing Baron Card----------\n");

	// check if a baron card is added to player's hand
	int handCountOld = state.handCount[player];

	baron_card(choice1, &state, handPos);

	if (handCountOld + 1 == state.handCount[player]) {
		printf("Passed test - Baron card was added to player's hand.\n");
	} else {
		printf("Failed test - Baron card was added to player's hand.\n");
	}

	// check if player played baron card
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int playedCardCountOld = state.playedCardCount;

	baron_card(choice1, &state, handPos);

	if (playedCardCountOld + 1 == state.playedCardCount) {
		printf("Passed test - Baron card was played.\n");
	} else {
		printf("Failed test - Baron card was played.\n");
	}

	// check if card was discarded
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int discardCountOld = state.discardCount[player];

	baron_card(choice1, &state, handPos);

	if (discardCountOld == state.discardCount[player] - 1)
		printf("Passed test - Baron card was discarded.\n");
	else
		printf("Failed test - Baron card was discarded.\n");

	// check deck count
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int deckCountOld = state.deckCount[player];

	baron_card(choice1, &state, handPos);

	if (deckCountOld == state.deckCount[player] - 1) {
		printf("Passed test - Baron card increased deck count.\n");
	} else {
		printf("Failed test - Baron card increased deck count.\n");
	};

	// check if player gets extra buy
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int numBuysOld = state.numBuys;

	baron_card(choice1, &state, handPos);

	if (numBuysOld + 1 == state.numBuys) {
		printf("Passed test - Baron card added one to the number of buys.\n");
	} else {
		printf("Failed test - Baron card added one to the number of buys.\n");
	}

	// check if player gains estate
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int numEstatesOld = 0, numEstates = 0, i = 0;
	for (i = 0; i < state.handCount[0]; i++) {
		if (state.hand[0][i] = estate);
			numEstatesOld++;
	}

	baron_card(choice1, &state, handPos);

	for (i = 0; i < state.handCount[0]; i++) {
		if (state.hand[0][i] = estate);
			numEstates++;
	}

	if (numEstatesOld < numEstates) {
		printf("Passed test - Estate card was added to player hand.\n");
	} else {
		printf("Failed test - Estate card was added to player hand.\n");
	}

	// check if player gains +4 coins
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	choice1 = 1;

	int numCoinsOld = state.coins;

	baron_card(choice1, &state, handPos);

	if (numCoinsOld < state.coins) {
		printf("Passed test - Player gained four extra coins.\n");
	} else {
		printf("Failed test - Player gained four extra coins.\n");
	}

	// check for isGameOver bug
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	state.supplyCount[estate] = 1;

	baron_card(choice1, &state, handPos);

	if (supplyCount(estate, &state) == 0) {
		printf("Passed test - Game is over.\n");
	} else {
		printf("Failed test - Game is over.\n");
	}

	printf("\n----------End Testing Baron Card----------\n");
	return 0;

}