#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int testGreatHall() {

    int i;
    int drawn = 1;
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
    int expectedCards[1] = {state.deck[thisPlayer][(deckCounter - 1)]};
    
    memcpy(&testState, &state, sizeof(struct gameState));
    
    printf("\n\nTESTING GREAT_HALL\n\n");
    cardEffect(great_hall, 0, 0, 0, &testState, handPos, &bonus);

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

    if ((testState.hand[thisPlayer][handPos] == expectedCards[0])) {

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

    if ((testState.hand[thisPlayer][handPos] == expectedCards[0])) {
        printf("CARD DRAWN IS FORMER TOP FROM PLAYERS DECK AND IN CORRECT POSITION TEST: PASSED\n");

    }
    else {
        printf("CARD DRAWN IS FORMER TOP FROM PLAYERS DECK AND IN CORRECT POSITION TEST: FAILED\n");
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

    if(testState.numActions == (state.numActions + 1)) {
        printf("NUMBER OF ACTIONS INCREASED BY ONE TEST: PASSED\n");
    }
    else {
        printf("NUMBER OF ACTIONS INCREASED BY ONE TEST: FAILED\n");
        testPassed = 0;
    }

    return testPassed;
}




int main() 
{
    int result = testGreatHall();
    if (result == 1) {
        printf("\nGREAT_HALL TESTS PASSED\n\n");
    }
    else {
        printf("\nGREAT_HALL TEST(S) FAILED\n\n");
    }

    return 0;
}
