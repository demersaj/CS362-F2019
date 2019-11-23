/**************************************
 * Author: Andrew Demers
 * CS 362 - Assignment 3
 * File: unittest2.c
 * Description: Tests the mine card functions as it should. Looks specifically for my
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
	int handPos = 0, choice1 = 3, choice2 = -1, choice3 = 0, bonus = 0;
	struct gameState state;
	int numPlayers = 2;
	int player = 0;
	int k[10] = {mine, baron, minion, ambassador, gardens, copper, remodel, smithy,
				 village, estate};

	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	printf("\n----------Begin Testing Mine Card----------\n");
	// check if a mine card is added to player's hand
	int handCountOld = state.handCount[player];

	playCard(handPos, choice1, choice2, choice3, &state);

	mineCard(choice1, choice2, handPos, player, &state);

	if (handCountOld + 1 == state.handCount[player]) {
		printf("Passed test - Mine card was added to player's hand.\n");
	} else {
		printf("Failed test - Mine card was added to player's hand.\n");
	}

	// check if player played mine card
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int playedCardCountOld = state.playedCardCount;

	mineCard(choice1, choice2, handPos, player, &state);

	if (playedCardCountOld + 1 == state.playedCardCount) {
		printf("Passed test - Mine card was played.\n");
	} else {
		printf("Failed test - Mine card was played.\n");
	}

	// check if card was discarded
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int discardCountOld = state.discardCount[player];

	mineCard(choice1, choice2, handPos, player, &state);

	if (discardCountOld == state.discardCount[player] - 1)
		printf("Passed test - Mine card was discarded.\n");
	else
		printf("Failed test - Mine card was discarded.\n");

	// check deck count
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int deckCountOld = state.deckCount[player];

	mineCard(choice1, choice2, handPos, player, &state);

	if (deckCountOld == state.deckCount[player] - 1) {
		printf("Passed test - Mine card increased deck count.\n");
	} else {
		printf("Failed test - Mine card increased deck count.\n");
	};

	// check if player gains a treasure card
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int numCoinsOld = state.coins;

	mineCard(choice1, choice2, handPos, player, &state);

	if (numCoinsOld <= state.coins) {
		printf("Passed test - Player gained a treasure card./n");
	} else {
		printf("Failed test - Player gained a treasure card./n");
	}

	// check if choice2 is passed in. If it is not, the player's card count will remain the same
	// need to call the cardEffect function since the mineCard choice1, choice2, handPos, player, &stateiables
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int numCardsOld = state.handCount[player];

	cardEffect(mine, choice1, choice2, choice3, &state, handPos, &bonus);

	if (numCardsOld < state.handCount[player]) {
		printf("Passed test - Player gained a card.\n");
	} else {
		printf("Failed test - Player gained a card.\n");
	}

	printf("\n----------End Testing Mine Card----------\n");

}