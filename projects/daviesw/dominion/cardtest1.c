#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int testSmithy () {

    int i;
    int drawn = 3;
    int discarded = 1;
    int seed = 1000;
    int numPlayers = 2;
    int thisPlayer = 0;
    int bonus = 0;
    struct gameState state, testState;
    int king[10] = {smithy, tribute, sea_hag, cutpurse, mine, minion, village, embargo, gardens, adventurer};
    int handPos = 0;
    //int curCount = testState.handCount[thisPlayer];
    //int curCard;    
    
    int testPassed = 1;
    initializeGame(numPlayers, king, seed, &state);
    
    int deckCounter = state.deckCount[thisPlayer];
    int expectedCards[3] = {state.deck[thisPlayer][(deckCounter - 1)], state.deck[thisPlayer][(deckCounter - 2)], state.deck[thisPlayer][(deckCounter - 3)]};
    
    memcpy(&testState, &state, sizeof(struct gameState));
    
    printf("\n\nTESTING SMITHY\n\n");
    cardEffect(smithy, 0, 0, 0, &testState, handPos, &bonus);

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

    if ((testState.hand[thisPlayer][handPos] == expectedCards[2])) {

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

    if ((testState.hand[thisPlayer][ (testState.handCount[thisPlayer] - 2)] == expectedCards[0])
    && (testState.hand[thisPlayer][ (testState.handCount[thisPlayer] - 1)] == expectedCards[1])
    && (testState.hand[thisPlayer][handPos] == expectedCards[2])) {
        printf("CARDS WERE DRAWN FROM TOP OF PLAYER'S DECK TEST: PASSED\n");

    }
    else {
        printf("CARDS WERE DRAWN FROM TOP OF PLAYER'S DECK TEST: FAILED\n");
        testPassed = 1;
    }

    if (testState.handCount[1] == state.handCount[1]) {
        printf("HANDCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: PASSED\n");
    }
    else {
        printf("HANDCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: FAILED\n");
        printf("ENDING TEST TO AVOID CRASH\n");
        return 0;
    }

    if (testState.deckCount[1] == state.deckCount[1]) {
        printf("DECKCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: PASSED\n");
    }
    else {
        printf("DECKCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: FAILED\n");
        printf("ENDING TEST TO AVOID CRASH\n");
        return 0;
    }

    if (testState.discardCount[1] == state.discardCount[1]) {
        printf("DISCARDCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: PASSED\n");
    }
    else {
        printf("DISCARDCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: FAILED\n");
        printf("ENDING TEST TO AVOID CRASH\n");
        return 0;
    }
    
    int changeTestPass = 1;

    for (i = 0; i < testState.handCount[1]; i++) {
        if (testState.hand[1][i] != state.hand[1][i]) {
            printf("OTHER PLAYER'S HAND NOT AFFECTED TEST: FAILED\n");
            testPassed = 0;
            changeTestPass = 0;
        }
    }

    if (changeTestPass == 1) {
        printf("OTHER PLAYER'S HAND NOT AFFECTED TEST: PASSED\n");
    }
    changeTestPass = 1;

    for (i = 0; i < testState.deckCount[1]; i++) {
        if (testState.deck[1][i] != state.deck[1][i]) {
            printf("OTHER PLAYER'S DECK NOT AFFECTED TEST: FAILED\n");
            testPassed = 0;
            changeTestPass = 0;
        }
    }

    if (changeTestPass == 1) {
        printf("OTHER PLAYER'S DECK NOT AFFECTED TEST: PASSED\n");
    }
    changeTestPass = 1;


    for (i = 0; i < testState.discardCount[1]; i++) {
        if (testState.discard[1][i] != state.discard[1][i]) {
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
    int result = testSmithy();
    if (result == 1) {
        printf("\nSMITHY TESTS PASSED\n\n");
    }
    else {
        printf("\nSMITHY TEST(S) FAILED\n\n");
    }

    return 0;
}
