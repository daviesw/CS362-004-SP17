#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int testAdventurer() {

    int i;
    int drawn = 4;
    int discarded = 3;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 1;
    int otherPlayer = 0;
    int bonus = 0;
    int drawntreasure = 0;
    int temphand[MAX_HAND];
    int z = 0;
    struct gameState state, testState;
    int king[10] = {smithy, tribute, sea_hag, cutpurse, mine, minion, village, embargo, gardens, adventurer};
    int handPos = 0;
    int testPassed = 1;
    initializeGame(numPlayers, king, seed, &state);

    int deckCounter = state.deckCount[thisPlayer];
    state.deck[thisPlayer][(deckCounter - 1)] = sea_hag;
    state.deck[thisPlayer][(deckCounter - 2)] = copper;
    state.deck[thisPlayer][(deckCounter - 3)] = cutpurse;
    state.deck[thisPlayer][(deckCounter - 4)] = silver;
    state.hand[thisPlayer][handPos] = adventurer;
    state.hand[thisPlayer][handPos + 1] = curse;
    state.hand[thisPlayer][handPos + 2] = curse;
    state.hand[thisPlayer][handPos+3] = curse;
    state.handCount[thisPlayer] = 4;
    state.whoseTurn = thisPlayer;

    memcpy(&testState, &state, sizeof(struct gameState));

    printf("\n\nTESTING ADVENTURER\n\n");
    //cardEffect(adventurer, 0, 0, 0, &testState, handPos, &bonus);
    adventurer_fct(drawntreasure, thisPlayer, temphand, z, &testState, handPos, &bonus);

    if (testState.handCount[thisPlayer] == (state.handCount[thisPlayer] + drawn - discarded)) {
        printf("HANDCOUNT INCREASE TEST: PASSED\n");
    }
    else {
        printf("HANDCOUNT INCREASE TEST: FAILED\n");
        testPassed = 0;
    }

    if (testState.deckCount[thisPlayer] == (state.deckCount[thisPlayer] - drawn)) {
        printf("DECKCOUNT DECREASE TEST: PASSED\n");
    }
    else {
        printf("DECKCOUNT DECREASE TEST: FAILED\n");
        testPassed = 0;
    }

    if ((testState.playedCards[(testState.playedCardCount - 1)] == state.hand[thisPlayer][handPos])
    && (testState.playedCardCount == state.playedCardCount + 1)) {
        printf("PLAYEDCARD HAS PLAYED CARD TEST: PASSED\n");
        printf("PLAYEDCARDCOUNT INCREASE TEST: PASSED\n");
    }
    else {
        printf("PLAYEDCARD HAS PLAYED CARD TEST: FAILED\n");
        printf("PLAYEDCARDCOUNT INCREASE TEST: FAILED\n");
        testPassed = 0;
    }

    if ((testState.hand[thisPlayer][handPos] == silver)) {

        printf("PLAYED CARD'S POSITION OCCUPIED BY NEW CARD TEST: PASSED\n");
    }
    else {
        printf("PLAYED CARD'S POSITION OCCUPIED BY NEW CARD TEST: FAILED\n");
        testPassed = 0;
    }

    if (testState.hand[thisPlayer][(testState.handCount[thisPlayer])] == -1) {
        printf("POSITION FORMERLY OCCUPIED NOW VALUED AT -1 TEST: PASSED\n");
    }
    else {
        printf("POSITION FORMERLY OCCUPIED NOW VALUED AT -1 TEST: FAILED\n");
        testPassed = 0;
    }

    if ((testState.hand[thisPlayer][handPos] == silver)
    && (testState.hand[thisPlayer][ (testState.handCount[thisPlayer] - 1)] == copper)) {
        printf("CARDS DRAWN ARE THE CORRECT CARDS AND IN CORRECT HAND POSITION TEST: PASSED\n");

    }
    else {
        printf("CARDS DRAWN ARE THE CORRECT CARDS AND IN THE CORRECT HAND POSITION TEST: FAILED\n");
        testPassed = 0;
    }

    if (testState.handCount[otherPlayer] == state.handCount[otherPlayer]) {
        printf("HANDCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: PASSED\n");
    }
    else {
        printf("HANDCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: FAILED\n");
        printf("ENDING TEST TO AVOID CRASH\n");
        return 0;
    }

    if (testState.deckCount[otherPlayer] == state.deckCount[otherPlayer]) {
        printf("DECKCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: PASSED\n");
    }
    else {
        printf("DECKCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: FAILED\n");
        printf("ENDING TEST TO AVOID CRASH\n");
        return 0;
    }

    if (testState.discardCount[otherPlayer] == state.discardCount[otherPlayer]) {
        printf("DISCARDCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: PASSED\n");
    }
    else {
        printf("DISCARDCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: FAILED\n");
        printf("ENDING TEST TO AVOID CRASH\n");
        return 0;
    }

    int changeTestPass = 1;

    for (i = 0; i < testState.handCount[otherPlayer]; i++) {
        if (testState.hand[otherPlayer][i] != state.hand[otherPlayer][i]) {
            printf("OTHER PLAYER'S HAND NOT AFFECTED TEST: FAILED\n");
            testPassed = 0;
            changeTestPass = 0;
        }
    }

    if (changeTestPass == 1) {
        printf("OTHER PLAYER'S HAND NOT AFFECTED TEST: PASSED\n");
    }
    changeTestPass = 1;

    for (i = 0; i < testState.deckCount[otherPlayer]; i++) {
        if (testState.deck[otherPlayer][i] != state.deck[otherPlayer][i]) {
            printf("OTHER PLAYER'S DECK NOT AFFECTED TEST: FAILED\n");
            testPassed = 0;
            changeTestPass = 0;
        }
    }

    if (changeTestPass == 1) {
        printf("OTHER PLAYER'S DECK NOT AFFECTED TEST: PASSED\n");
    }
    changeTestPass = 1;


    for (i = 0; i < testState.discardCount[otherPlayer]; i++) {
        if (testState.discard[otherPlayer][i] != state.discard[otherPlayer][i]) {
            printf("OTHER PLAYER'S DISCARD PILE NOT AFFECTED TEST: FAILED\n");
            testPassed = 0;
            changeTestPass = 0;
        }
    }

    if (changeTestPass == 1) {
        printf("OTHER PLAYER'S DISCARD PILE NOT AFFECTED TEST: PASSED\n");
    }
    changeTestPass = 1;

    for (i = adventurer; i <= treasure_map; i++) {
        if (testState.supplyCount[i] != state.supplyCount[i]) {
            printf("VICTORY AND KINGDOM CARDS NOT AFFECTED TEST: FAILED\n");
            changeTestPass = 0;
            testPassed = 0;
        }
    }

    if (changeTestPass == 1) {
        printf("VICTORY AND KINGDOM CARDS NOT AFFECTED TEST: PASSED\n");
    }

    return testPassed;
}




int main()
{
    int result = testAdventurer();
    if (result == 1) {
        printf("\nADVENTURER TESTS PASSED\n\n");
    }
    else {
        printf("\nADVENTURER TEST(S) FAILED\n\n");
    }

    return 0;
}

