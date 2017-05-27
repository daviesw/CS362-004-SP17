#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int testSmithy (int thisPlayer, struct gameState testState, int handPos) {

    //printf("In function\n");
    int i, j, k;
    int drawn = 3;
    int discarded = 1;
    //int seed = 1000;
    int numPlayers = testState.numPlayers;
    //printf("Past accessing\n");
    //int thisPlayer = 0;
    //int bonus = 0;
    int changeTestPass = 1;
    struct gameState state;
    //int king[10] = {smithy, tribute, sea_hag, cutpurse, mine, minion, village, embargo, gardens, adventurer};
    //int handPos = 0;
    //int curCount = testState.handCount[thisPlayer];
    //int curCard;    
    
    int testPassed = 1;
    //initializeGame(numPlayers, king, seed, &state);
    
    int deckCounter = testState.deckCount[thisPlayer];
    //printf("Before expected cards\n");
    int expectedCards[3] = {testState.deck[thisPlayer][(deckCounter - 1)], testState.deck[thisPlayer][(deckCounter - 2)], testState.deck[thisPlayer][(deckCounter - 3)]};
    //printf("About to memcpy\n"); 
    memcpy(&state, &testState, sizeof(struct gameState));
    
    printf("\n\nTESTING SMITHY\n\n");
    
    //smithyPlayed(&testState, thisPlayer, handPos);
    //cardEffect(smithy, 0, 0, 0, &testState, handPos, &bonus);
    smithy_fct(thisPlayer, &testState, handPos);

    //printf("Made it here\n");
    if (testState.handCount[thisPlayer] == (state.handCount[thisPlayer] + drawn - discarded)) {
        //printf("HANDCOUNT INCREASE TEST: PASSED\n");
    }
    else {
        printf("HANDCOUNT INCREASE TEST: FAILED\n");
        printf("EXPECTED: %d Actual: %d\n", (state.handCount[thisPlayer] + drawn - discarded), (testState.handCount[thisPlayer]));
        testPassed = 0;
    }

    if (testState.deckCount[thisPlayer] == (state.deckCount[thisPlayer] - drawn)) {
       // printf("DECKCOUNT DECREASE TEST: PASSED\n");
    }
    else {
        printf("DECKCOUNT DECREASE TEST: FAILED\n");
        printf("EXPECTED: %d Actual: %d\n", (state.deckCount[thisPlayer] - drawn), (testState.deckCount[thisPlayer]));
	testPassed = 0;
    }

    if ((testState.playedCards[(testState.playedCardCount - 1)] == state.hand[thisPlayer][handPos])
    && (testState.playedCardCount == state.playedCardCount + 1)) {
       // printf("PLAYEDCARD HAS PLAYED CARD TEST: PASSED\n");
       // printf("PLAYEDCARDCOUNT INCREASE TEST: PASSED\n");
    }
    else {
        printf("PLAYEDCARD HAS PLAYED CARD TEST: FAILED\n");
        printf("PLAYEDCARDCOUNT INCREASE TEST: FAILED\n");
        printf("EXPECTED COUNT: %d Actual: %d\n", (state.playedCardCount + 1), (testState.playedCardCount));
        printf("EXPECTED CARD IN PLAYEDCARD: %d Actual: %d\n", state.hand[thisPlayer][handPos], testState.playedCards[(testState.playedCardCount - 1)]);
	testPassed = 0;
    }

    if ((testState.hand[thisPlayer][handPos] == expectedCards[2])) {

        //printf("PLAYED CARD'S POSITION OCCUPIED BY NEW CARD TEST: PASSED\n");
    }    
    else {
        printf("PLAYED CARD'S POSITION OCCUPIED BY NEW CARD TEST: FAILED\n");
        printf("EXPECTED CARD: %d ACTUAL CARD: %d\n", expectedCards[2], testState.hand[thisPlayer][handPos]);
	testPassed = 0;
    }

    if (testState.hand[thisPlayer][(testState.handCount[thisPlayer])] == -1) {
        //printf("POSITION FORMERLY OCCUPIED NOW VALUED AT -1 TEST: PASSED\n");
    }
    else {
        printf("POSITION FORMERLY OCCUPIED NOW VALUED AT -1 TEST: FAILED\n");
        printf("ACTUAL CARD PRESENT: %d\n", testState.hand[thisPlayer][(testState.handCount[thisPlayer])]);
	testPassed = 0;
    }

    if ((testState.hand[thisPlayer][ (testState.handCount[thisPlayer] - 2)] == expectedCards[0])
    && (testState.hand[thisPlayer][ (testState.handCount[thisPlayer] - 1)] == expectedCards[1])
    && (testState.hand[thisPlayer][handPos] == expectedCards[2])) {
        //printf("CARDS WERE DRAWN FROM TOP OF PLAYER'S DECK TEST: PASSED\n");

    }
    else {
        printf("CARDS WERE DRAWN FROM TOP OF PLAYER'S DECK TEST: FAILED\n");
        printf("ACTUAL CARDS IN THOSE POSITIONS: %d, %d, and %d\n", testState.hand[thisPlayer][ (testState.handCount[thisPlayer] - 2)], testState.hand[thisPlayer][ (testState.handCount[thisPlayer] - 1)], testState.hand[thisPlayer][handPos]);
	printf("EXPECTED CARDS IN THOSE POSITIONS: %d, %d, and %d\n", expectedCards[0], expectedCards[1], expectedCards[2]);
	testPassed = 0;
    }
    if (testPassed == 1) {
        printf("TESTS OF CARDS EFECT ON THE PLAYER USING IT: PASSED\n");
    }
    printf("\n---------TEST TO ENSURE OTHER PLAYERS NOT AFFECTED------\n");

    for (j = 0; j < numPlayers; j++) {
    	if (j != thisPlayer) {
	    printf("\nPlayer %d\n", (j+1));
            if (testState.handCount[j] == state.handCount[j]) {
    	        //printf("HANDCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: PASSED\n");
    	    }
    	    else {
    	        printf("HANDCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: FAILED\n");
    	        printf("EXPECTED: %d ACTUAL: %d\n", state.handCount[j], testState.handCount[j]);
		printf("ENDING TEST TO AVOID CRASH\n");
    	        return 0;
    	    }

    	    if (testState.deckCount[j] == state.deckCount[j]) {
    	        //printf("DECKCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: PASSED\n");
    	    }
    	    else {
    	        printf("DECKCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: FAILED\n");
		printf("EXPECTED: %d ACTUAL: %d\n", state.deckCount[j], testState.deckCount[j]);
    	        printf("ENDING TEST TO AVOID CRASH\n");
    	        return 0;
    	    }

    	    if (testState.discardCount[j] == state.discardCount[j]) {
    	        //printf("DISCARDCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: PASSED\n");
    	    }
    	    else {
    	        printf("DISCARDCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: FAILED\n");
		printf("EXPECTED: %d ACTUAL: %d\n", state.discardCount[j], testState.discardCount[j]);
    	        printf("ENDING TEST TO AVOID CRASH\n");
    	        return 0;
    	    }
    
    	    changeTestPass = 1;

    	    for (i = 0; i < testState.handCount[1]; i++) {
    	        if (testState.hand[j][i] != state.hand[j][i]) {
    	            //printf("OTHER PLAYER'S HAND NOT AFFECTED TEST: FAILED\n");
    	            testPassed = 0;
    	            changeTestPass = 0;
    	        }
    	    }

    	    if (changeTestPass == 1) {
    	        //printf("OTHER PLAYER'S HAND NOT AFFECTED TEST: PASSED\n");
    	    }
	    else {
                printf("OTHER PLAYER'S HAND NOT AFFECTED TEST: FAILED\n");
                printf("EXPECTED HAND\n");
                for (k = 0; k < state.handCount[j]; k++) {
                    printf("%d\n", state.hand[j][k]);
                }
                printf("ACTUAL HAND\n");
                for (k = 0; k < testState.handCount[j]; k++) {
                    printf("%d\n", testState.hand[j][k]);
                }
            }

    	    changeTestPass = 1;

    	    for (i = 0; i < testState.deckCount[j]; i++) {
    	        if (testState.deck[j][i] != state.deck[j][i]) {
    	            //printf("OTHER PLAYER'S DECK NOT AFFECTED TEST: FAILED\n");
    	            testPassed = 0;
    	            changeTestPass = 0;
    	        }
    	    }

    	    if (changeTestPass == 1) {
    	        //printf("OTHER PLAYER'S DECK NOT AFFECTED TEST: PASSED\n");
    	    }
            else {
                printf("OTHER PLAYER'S DECK NOT AFFECTED TEST: FAILED\n");
                printf("EXPECTED DECK\n");
                for (k = 0; k < state.deckCount[j]; k++) {
                    printf("%d\n", state.deck[j][k]);
                }
                printf("ACTUAL DECK\n");
                for (k = 0; k < testState.deckCount[j]; k++) {
                    printf("%d\n", testState.deck[j][k]);
                }
            }

    	    changeTestPass = 1;
	    //printf("Before the count\n");
	    //printf("Hand Count: %d Deck Count: %d Discard Count: %d", testState.handCount[j], testState.deckCount[j], testState.discardCount[j]);
	    //printf("After the count\n");
    	    for (i = 0; i < testState.discardCount[j]; i++) {
    	        if (testState.discard[j][i] != state.discard[j][i]) {
    	            //printf("OTHER PLAYER'S DISCARD PILE NOT AFFECTED TEST: FAILED\n");
    	            testPassed = 0;
    	            changeTestPass = 0;
    	        }
    	    }
	    
    	    if (changeTestPass == 1) {
    	        //printf("OTHER PLAYER'S DISCARD PILE NOT AFFECTED TEST: PASSED\n");
    	    }
            else {
                printf("OTHER PLAYER'S DISCARD PILE NOT AFFECTED TEST: FAILED\n");
                printf("EXPECTED DISCARD PILE\n");
                for (k = 0; k < state.discardCount[j]; k++) {
                    printf("%d\n", state.discard[j][k]);
                }
                printf("ACTUAL DISCARD PILE\n");
                for (k = 0; k < testState.discardCount[j]; k++) {
                    printf("%d\n", testState.discard[j][k]);
                }
            }

    	    changeTestPass = 1;
        }
    }
    if (changeTestPass == 1) {
        printf("TESTS OF OTHER PLAYERS' HANDS DECKS AND DISCARD PILES: PASSED\n");
    }
    printf("\n------------------TEST TO ENSURE SUPPLY IS UNCHANGED-------\n");
    
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
    else {
        printf("VICTORY AND KINGDOM CARDS NOT AFFECTED TEST: FAILED\n");
        printf("EXPECTED CONTENTS\n");
        for (k = 0; k <= treasure_map; k++) {
            printf("CARD %d: %d\n", k, state.supplyCount[k]);
        }
        printf("ACTUAL CONTENTS\n");
        for (k = 0; k <= treasure_map; k++) {
            printf("CARD %d: %d\n", k, testState.hand[j][k]);
        }
    }

    return testPassed;
}



//note, basic structure adapted from lecture slides
int main() 
{
    //SelectStream(2);
    //PutSeed(3);
    srand(time(0));

    int n, i, p, j, handPos;
    int  result = 0;
    int testsFailed = 0;
    struct gameState G;
    int numTests = 200;

    for (n = 0; n < numTests; n++) {
        for (i = 0; i < sizeof(struct gameState); i++) {
            ((char*)&G)[i] = rand() % 256;
	}
        G.numPlayers = rand() % MAX_PLAYERS+1;
	for (p = 0; p < G.numPlayers; p++) {
            G.deckCount[p] = rand() % MAX_DECK+1;
            G.discardCount[p] = rand() % MAX_DECK+1;
            G.handCount[p] = rand() % MAX_HAND+1;
	    G.playedCardCount = rand() % MAX_DECK+1;
	    for (j = 0; j < G.handCount[p]; j++) {
	        G.hand[p][j] = (rand() % treasure_map+1);
	    }
	    for (j = 0; j < G.deckCount[p]; j++) {
                G.deck[p][j] = (rand() % treasure_map+1);
            }
	    for (j = 0; j < G.playedCardCount; j++) {
                G.playedCards[j] = (rand() % treasure_map+1);
            }
        }
	p = rand() % G.numPlayers;
        handPos = rand() % G.handCount[p];
	G.hand[p][handPos] = smithy;
	G.whoseTurn = p;
	//printf("numPlayers: %d player: %d\n\n", G.numPlayers, p);
        result = testSmithy(p, G, handPos);
        
	if (result == 0) {
	    testsFailed++;
	}
    }

    printf("Failed %d tests\n", testsFailed);
/*
    //int result = testSmithy();
    if (result == 1) {
        printf("\nSMITHY TESTS PASSED\n\n");
    }
    else {
        printf("\nSMITHY TEST(S) FAILED\n\n");
    }
*/
    return 0;
}
