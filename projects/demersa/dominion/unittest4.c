/**************************************
 * Author: Andrew Demers
 * CS 362 - Assignment 3
 * File: unittest2.c
 * Description: Tests the tribute card functions as it should. Looks specifically for my
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
	int k[10] = {tribute, baron, minion, ambassador, gardens, mine, remodel, smithy,
				 village, estate};
	int currentPlayer = whoseTurn(&state);
	int nextPlayer = currentPlayer + 1;
	int tributeRevealedCards[2] = {-1, -1};

	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	printf("\n----------Begin Testing Tribute Card----------\n");

	// check if a tribute card is added to player's hand

	int handCountOld = state.handCount[player];

	tribute_card(&state, handPos, tributeRevealedCards, nextPlayer);

	if (handCountOld + 1 == state.handCount[player]) {
		printf("Passed test - Tribute card was added to player's hand.\n");
	} else {
		printf("Failed test - Tribute card was added to player's hand.\n");
	}

	// check if player played tribute card
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	currentPlayer = whoseTurn(&state);
	nextPlayer = currentPlayer + 1;

	int playedCardCountOld = state.playedCardCount;

	tribute_card(&state, handPos, tributeRevealedCards, nextPlayer);

	if (playedCardCountOld + 1 == state.playedCardCount) {
		printf("Passed test - Tribute card was played.\n");
	} else {
		printf("Failed test - Tribute card was played.\n");
	}

	// check if card was discarded
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	currentPlayer = whoseTurn(&state);
	nextPlayer = currentPlayer + 1;

	int discardCountOld = state.discardCount[player];

	tribute_card(&state, handPos, tributeRevealedCards, nextPlayer);

	if (discardCountOld == state.discardCount[player] - 1)
		printf("Passed test - Tribute card was discarded.\n");
	else
		printf("Failed test - Tribute card was discarded.\n");

	// check deck count
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	currentPlayer = whoseTurn(&state);
	nextPlayer = currentPlayer + 1;

	int deckCountOld = state.deckCount[player];

	tribute_card(&state, handPos, tributeRevealedCards, nextPlayer);

	if (deckCountOld == state.deckCount[player] - 1) {
		printf("Passed test - Tribute card increased deck count.\n");
	} else {
		printf("Failed test - Tribute card increased deck count.\n");
	};

	// check if player gains card based on what the player to the left discards
	// player should gain either +2 actions, +2 coins, or +2 cards
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	currentPlayer = whoseTurn(&state);
	nextPlayer = currentPlayer + 1;
	state.discardCount[nextPlayer] = 5;

	int numActionsOld = state.numActions;
	int numCoinsOld = state.coins;
	int numCardsOld = state.handCount[player];

	tribute_card(&state, handPos, tributeRevealedCards, nextPlayer);

	if (numActionsOld != state.numActions + 2 || numCoinsOld != state.coins + 2 || numCardsOld != state.handCount[player]) {
		printf("Failed test - Tribute card increased action, coin, card count.\n");
	} else {
		printf("Passed test - Tribute card increased action, coin, card count.\n");
	}

	// check if player gains cards when they reveal a copper
	memset(&state, 23, sizeof(struct gameState));    // clear game state
	initializeGame(numPlayers, k, time(0), &state);        // initialize game state

	int tributeRevealedCardsNew[2] = {copper, 0};
	currentPlayer = whoseTurn(&state);
	nextPlayer = currentPlayer + 1;

	numCoinsOld = state.coins;

	tribute_card(&state, handPos, tributeRevealedCardsNew, nextPlayer);

	if (numCoinsOld != state.coins) {
		printf("Passed test - Tribute card increased player coins.\n");
	} else {
		printf("Failed test - Tribute card increased player coins.\n");
	}


	printf("\n----------End Testing Tribute Card----------\n");

}