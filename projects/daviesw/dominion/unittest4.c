#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int testUpdateCoins() {

    struct gameState *state = malloc(sizeof(struct gameState));
    int numPlayers = 2;
    int king[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int seed = 1000;
    int testPassed = 1;
    int i;
    int count;
    int expected = 0;
    
    initializeGame(numPlayers, king, seed, state);
    
    printf("TEST OF CARD COUNT OF CARD FOUNT IN HAND AND DECK ONLY\n");
    count = fullDeckCount(0, estate, state);
    for (i = 0; i < state->handCount[0]; i++) {
        if (state->hand[0][i] == estate) {
            expected++;
        }         
    }
    
    for (i = 0; i < state->deckCount[0]; i++) {
        if (state->deck[0][i] == estate) {
            expected++;
        }
    }

    state->hand[1][0] = duchy;
    state->hand[1][1] = duchy;
    state->hand[1][2] = duchy;
    state->handCount[1] += 3;

    state->discard[1][0] = estate;
    state->discard[1][1] = curse;
    state->discard[1][2] = curse;
    state->discardCount[1] += 3;

    state->deck[1][0] = sea_hag;
    state->deck[1][1] = sea_hag;
    state->deck[1][2] = sea_hag;

    if (expected == count) {
        printf("TEST OF CARD IN HAND AND DECK PASSED\n");
    }
    else {
        printf("TEST OF CARD IN HAND AND DECK FAILED\n");
        testPassed = 0;
    }

    printf("TEST FOR CARD FOUND ONLY IN DISCARD PILE\n");

    state->discard[0][0] = curse;
    state->discard[0][1] = curse;
    state->discard[0][2] = curse;
    state->discard[0][3] = curse;
    state->discard[0][4] = gardens;
    state->discard[0][5] = great_hall;
    state->discard[0][6] = estate;
    state->discard[0][7] = estate;
    state->discard[0][8] = estate;
    state->discard[0][9] = estate;
    state->discardCount[0] += 10;

    count = fullDeckCount(0, curse, state);
    expected = 4;

    if (expected == count) {
        printf("TEST OF CARD IN DISCARD PILE PASSED\n");
    }
    else {
        printf("TEST OF CARD IN DISCARD PILE FAILED\n");
        testPassed = 0;
    }

    printf("TEST FOR CARD FOUND ONLY IN DECK PILE\n");    

    state->deck[0][5] = duchy;
    state->deckCount[0] += 1;

    count = fullDeckCount(0, duchy, state);
    expected = 1;

    if (expected == count) {
        printf("TEST OF CARD IN DECK PASSED\n");
    }
    else {
        printf("TEST OF CARD IN DECK FAILED\n");
        testPassed = 0;
    }

    printf("TEST FOR CARD FOUND ONLY IN HAND\n");
    state->hand[0][5] = sea_hag;
    state->handCount[0]++;
    
    count = fullDeckCount(0, sea_hag, state);
    expected = 1;

    if (expected == count) {
        printf("TEST OF CARD IN HAND PASSED\n");
    }
    else {
        printf("TEST OF CARD IN HAND FAILED\n");
        testPassed = 0;
    }

    printf("TEST FOR CARD FOUND IN HAND AND DISCARD ONLY\n");

    state->discard[0][10] = sea_hag;
    state->discardCount[0] += 1;

    count = fullDeckCount(0, sea_hag, state);
    expected = 2;

    if (expected == count) {
        printf("TEST OF CARD IN HAND AND DISCARD PASSED\n");
    }
    else {
        printf("TEST OF CARD IN HAND AND DISCARD FAILED\n");
        testPassed = 0;
    }

    printf("TEST FOR CARD FOUND IN DECK AND DISCARD ONLY\n");

    state->discard[0][11] = duchy;
    state->discardCount[0]++;

    count = fullDeckCount(0, duchy, state);
    expected = 2;

    if (expected == count) {
        printf("TEST OF CARD IN DECK AND DISCARD PASSED\n");
    }
    else {
        printf("TEST OF CARD IN DECK AND DISCARD FAILED\n");
        testPassed = 0;
    }

    printf("TEST FOR CARD FOUND IN DECK, DISCARD, AND HAND\n");

    count = fullDeckCount(0, estate, state);
    expected = 7;

    if (expected == count) {
        printf("TEST OF CARD IN ALL POSSIBLE PLACES PASSED\n");
    }
    else {
        printf("TEST OF CARD IN ALL POSSIBLE PLACES FAILED\n");
        testPassed = 0;
    }

    printf("COMPARE TO RESULTS FOR ANOTHER PLAYER TO ENSURE FUNCTION WASN'T RETURNING CORRECT VALUES COINCIDENTALLY\n");

    if ((fullDeckCount(0, estate, state) == fullDeckCount(1, estate, state))) {
        printf("TEST FAILED\n");
        testPassed = 0;
    }
    else if ((fullDeckCount(0, estate, state) == fullDeckCount(1, estate, state))) {
        printf("TEST FAILED\n");
        testPassed = 0;
    }
    else if ((fullDeckCount(0, estate, state) == fullDeckCount(1, estate, state))) {
        printf("TEST FAILED\n");
        testPassed = 0;
    }
    else if ((fullDeckCount(0, estate, state) == fullDeckCount(1, estate, state))) {
        printf("TEST FAILED\n");
        testPassed = 0;
    }
    else {
        printf("TEST PASSED SUCCESSFULLY\n");
    }


    if (testPassed == 1) {
        printf("\n\nfullDeckCount() TESTS PASSED\n\n");
    }
    else {
        printf("\n\nfullDeckCOunt() TESTS FAILED\n\n");
    }
    free(state);
    return 0;
}

int main()
{
    testUpdateCoins();
    return 0;
}
