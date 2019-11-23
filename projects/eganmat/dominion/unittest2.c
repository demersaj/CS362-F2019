/**************************************
 * Author: Andrew Demers
 * CS 362 - Assignment 3
 * File: unittest2.c
 * Description: Tests the minion card functions as it should. Looks specifically for my
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
	int k[10] = {minion, baron, ambassador, tribute, gardens, mine, remodel, smithy,
				 village, estate};

	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	printf("\n----------Begin Testing Minion Card----------\n");

	// check if a minion card is added to player's hand
	int handCountOld = state.handCount[player];

	minionCard(choice1, choice2, handPos, player, &state);

	if (handCountOld + 1 == state.handCount[player]) {
		printf("Passed test - Minion card was added to player's hand.\n");
	} else {
		printf("Failed test - Minion card was added to player's hand.\n");
	}

	// check if player played minion card
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int playedCardCountOld = state.playedCardCount;

	minionCard(choice1, choice2, handPos, player, &state);

	if (playedCardCountOld + 1 == state.playedCardCount) {
		printf("Passed test - Minion card was played.\n");
	} else {
		printf("Failed test - Minion card was played.\n");
	}

	// check if card was discarded
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int discardCountOld = state.discardCount[player];

	minionCard(choice1, choice2, handPos, player, &state);

	if (discardCountOld == state.discardCount[player] - 1)
		printf("Passed test - Minion card was discarded.\n");
	else
		printf("Failed test - Minion card was discarded.\n");

	// check deck count
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int deckCountOld = state.deckCount[player];

	minionCard(choice1, choice2, handPos, player, &state);

	if (deckCountOld == state.deckCount[player] - 1) {
		printf("Passed test - Minion card increased deck count.\n");
	} else {
		printf("Failed test - Minion card increased deck count.\n");
	};

	// check if player gets +2 coins
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	choice1 = 1;

	int numCoinsOld = state.coins;

	minionCard(choice1, choice2, handPos, player, &state);

	if (numCoinsOld < state.coins) {
		printf("Passed test - Player gained two extra coins.\n");
	} else {
		printf("Failed test - Player gained two extra coins.\n");
	}

	// check if player discards cards and gains 4
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	choice1 = 0;
	choice2 = 1;

	discardCountOld = state.discardCount[player];
	handCountOld = state.handCount[player];

	minionCard(choice1, choice2, handPos, player, &state);

	if (discardCountOld < state.discardCount[player]) {
		printf("Passed test - Player discarded their cards.\n");
	} else {
		printf("Failed test - Player discarded their cards.\n");
	}

	if (handCountOld < state.handCount[player]) {
		printf("Passed test - Player drew four new cards.\n");
	} else {
		printf("Failed test - Player drew four new cards.\n");
	}

	// check if player gets an extra action
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int numActionsOld = state.numActions;

	minionCard(choice1, choice2, handPos, player, &state);

	if (numActionsOld < state.numActions) {
		printf("Passed test - Player gained an extra action.\n");
	} else {
		printf("Failed test - Player gained an extra action.\n");
	}

	// check if function returns -1 instead of 0
	int check = minionCard(choice1, choice2, handPos, player, &state);

	if (check == 0) {
		printf("Passed test - Function returns correctly.\n");
	} else {
		printf("Failed test - Function returns correctly.\n");
	}

	printf("\n----------End Testing Minion Card----------\n");

	return 0;
}