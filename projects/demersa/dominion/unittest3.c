/**************************************
 * Author: Andrew Demers
 * CS 362 - Assignment 3
 * File: unittest2.c
 * Description: Tests the ambassador card functions as it should. Looks specifically for my
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
	int handPos = 0, choice1 = 1, choice2 = 1, choice3 = 0, bonus = 0;
	struct gameState state;
	int numPlayers = 2;
	int player = 0;
	int k[10] = {ambassador, baron, minion, tribute, gardens, mine, remodel, smithy,
				 village, estate};

	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	printf("\n----------Begin Testing Ambassador Card----------\n");

	// check if a ambassador card is added to player's hand
	int handCountOld = state.handCount[player];

	ambassador_card(choice1, choice2, &state, handPos);

	if (handCountOld + 1 == state.handCount[player]) {
		printf("Passed test - Ambassador card was added to player's hand.\n");
	} else {
		printf("Failed test - Ambassador card was added to player's hand.\n");
	}

	// check if player played ambassador card
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int playedCardCountOld = state.playedCardCount;

	ambassador_card(choice1, choice2, &state, handPos);

	if (playedCardCountOld + 1 == state.playedCardCount) {
		printf("Passed test - Ambassador card was played.\n");
	} else {
		printf("Failed test - Ambassador card was played.\n");
	}

	// check if card was discarded
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int discardCountOld = state.discardCount[player];

	ambassador_card(choice1, choice2, &state, handPos);

	if (discardCountOld == state.discardCount[player] - 1)
		printf("Passed test - Ambassador card was discarded.\n");
	else
		printf("Failed test - Ambassador card was discarded.\n");

	// check deck count
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int deckCountOld = state.deckCount[player];

	ambassador_card(choice1, choice2, &state, handPos);

	if (deckCountOld == state.deckCount[player] - 1) {
		printf("Passed test - Ambassador card increased deck count.\n");
	} else {
		printf("Failed test - Ambassador card increased deck count.\n");
	};

	// check if two copies of a card is returned to the player
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int oldHandCount = state.handCount[player];

	ambassador_card(choice1, choice2, &state, handPos);

	if (oldHandCount < state.handCount[player]) {
		printf("Passed test - Ambassador card increased player hand count.\n");
	} else {
		printf("Failed test - Ambassador card increased player hand count.\n");
	}

	// check if values for choice2 are valid
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	choice2 = 4;

	ambassador_card(choice1, choice2, &state, handPos);

	if (choice2 > 1) {
		printf("Failed test - Ambassador card's choice2 is invalid.\n");
	} else {
		printf("Passed test - Ambassador card's choice2 is valid.\n");
	}

}