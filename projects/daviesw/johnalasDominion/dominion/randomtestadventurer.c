#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int testAdventurer (int thisPlayer, struct gameState testState, int handPos) {

    int i, j, k;
    int drawn = 0;//TODO: Determine this!
    int discarded = 0;//TODO: Determine this!
    int drawnTreasure = 0;
    int numPlayers = testState.numPlayers;
    int bonus = 0;
    int changeTestPass = 1;
    struct gameState state;
    int testPassed = 1;
    //int deckCounter = testState.deckCount[thisPlayer];
    int *otherCards = 0;
    int otherCardCount = 0;
    //int expectedOne, expectedTwo;
    int newTreasures = 0;
    int additions[2] = {-1, -1};
    int nonTreasures = 0;
    int lastDrawnIndex = 0;
    int lastTreasureFound = 0;
    int temphand[MAX_HAND];
    int z = 0;
    int inDeck = 0;
    memcpy(&state, &testState, sizeof(struct gameState));
     
    for (i = testState.deckCount[thisPlayer]-1; i >= 0; i--) {
        if (testState.deck[thisPlayer][i] == copper || testState.deck[thisPlayer][i] == silver || testState.deck[thisPlayer][i] == gold) {
            if (drawnTreasure < 2) {
	        drawnTreasure++;
	    }
	    
	    //printf("drawnTreasure increased to %d\n", drawnTreasure);
            if (drawnTreasure == 2 && lastTreasureFound == 0) {
                lastDrawnIndex = i;
		lastTreasureFound = 1;
            }
        }
        else {
            if (lastTreasureFound == 0) {
		nonTreasures++;
	    }
        }
    }

    if (drawnTreasure  == 2) {
        otherCards = malloc(nonTreasures * sizeof(int));
        
        for (i = testState.deckCount[thisPlayer]-1; i >= lastDrawnIndex; i--) {
            if (testState.deck[thisPlayer][i] == copper || testState.deck[thisPlayer][i] == silver || testState.deck[thisPlayer][i] == gold) {
                newTreasures++;
                
                if (newTreasures != 2) {
                    additions[0] = testState.deck[thisPlayer][i];
                }
		else {
		    additions[1] = testState.deck[thisPlayer][i];
		}
            }
            else {
                otherCards[otherCardCount] = testState.deck[thisPlayer][i];
		otherCardCount++;
            }
        }
        inDeck = 1;
    }
    else {
        for (i = testState.discardCount[thisPlayer]-1; i >= 0; i--) {
            if (testState.discard[thisPlayer][i] == copper || testState.discard[thisPlayer][i] == silver || testState.discard[thisPlayer][i] == gold) {
            drawnTreasure++;
                if (drawnTreasure == 2 && lastTreasureFound == 0) {
                    lastDrawnIndex = i;
                    lastTreasureFound = 1;
                }
            }
            else {
                if (lastTreasureFound == 0) {
                    nonTreasures++;
                }
            }
        }
    }

    drawn = nonTreasures + drawnTreasure;
    discarded = nonTreasures + 1;//TODO: Take these into account!
    printf("\n\nTESTING ADVENTURER\n\n");
    
    //cardEffect(adventurer, 0, 0, 0, &testState, handPos, &bonus);
    //adventurerPlayed(&testState, handPos, thisPlayer, 0);
    adventurer_fct(0, thisPlayer, temphand, z, &testState, handPos, &bonus);

    if (testState.handCount[thisPlayer] == (state.handCount[thisPlayer] + drawn - discarded)) {
        //printf("HANDCOUNT INCREASE TEST: PASSED\n");
    }
    else {
        printf("HANDCOUNT INCREASE TEST: FAILED\n");
        printf("EXPECTED: %d Actual: %d\n", (state.handCount[thisPlayer] + drawn - discarded), (testState.handCount[thisPlayer]));
	testPassed = 0;
    }

    if (testState.deckCount[thisPlayer] == (state.deckCount[thisPlayer] - drawn)) {
        //printf("DECKCOUNT DECREASE TEST: PASSED\n");
    }
    else {
        printf("DECKCOUNT DECREASE TEST: FAILED\n");
        printf("EXPECTED: %d Actual: %d\n", (state.deckCount[thisPlayer] - drawn), (testState.deckCount[thisPlayer]));
	testPassed = 0;
    }

    if ((testState.playedCards[(testState.playedCardCount - 1)] == state.hand[thisPlayer][handPos])
    && (testState.playedCardCount == state.playedCardCount + 1)) {
        //printf("PLAYEDCARD HAS PLAYED CARD TEST: PASSED\n");
        //printf("PLAYEDCARDCOUNT INCREASE TEST: PASSED\n");
    }
    else {
        printf("PLAYEDCARD HAS PLAYED CARD TEST: FAILED\n");
        printf("PLAYEDCARDCOUNT INCREASE TEST: FAILED\n");
        printf("EXPECTED COUNT: %d Actual: %d\n", (state.playedCardCount + 1), (testState.playedCardCount));
	printf("EXPECTED CARD IN PLAYEDCARD: %d Actual: %d\n", state.hand[thisPlayer][handPos], testState.playedCards[(testState.playedCardCount - 1)]);
        testPassed = 0;
    }
/*
    if ((testState.hand[thisPlayer][handPos] == additions[0]) || (testState.hand[thisPlayer][handPos] == additions[1])) {

        printf("PLAYED CARD'S POSITION OCCUPIED BY NEW CARD TEST: PASSED\n");
    }    
    else {
        printf("PLAYED CARD'S POSITION OCCUPIED BY NEW CARD TEST: FAILED\n");
        printf("CARDS THAT COULD BE IN POSITION: %d or %d  ACTUAL CARD: %d\n", additions[0], additions[1], testState.hand[thisPlayer][handPos]);
	testPassed = 0;
    }
*/
    if (testState.hand[thisPlayer][(testState.handCount[thisPlayer])] == -1) {
        //printf("POSITION FORMERLY OCCUPIED NOW VALUED AT -1 TEST: PASSED\n");
    }
    else {
        printf("POSITION FORMERLY OCCUPIED NOW VALUED AT -1 TEST: FAILED\n");
        printf("ACTUAL CARD PRESENT: %d\n", testState.hand[thisPlayer][(testState.handCount[thisPlayer])]);
	testPassed = 0;
    }
//TODO: Alternate options for not enough treasures in deck
    if (lastTreasureFound == 1 && inDeck == 1) {
        if ((testState.hand[thisPlayer][ (testState.handCount[thisPlayer] - 1)] == additions[0] || testState.hand[thisPlayer][ (testState.handCount[thisPlayer] - 1)] == additions[1])
        && (testState.hand[thisPlayer][handPos] == additions[0] || testState.hand[thisPlayer][handPos] == additions[1])) {
            //printf("CARDS WERE DRAWN FROM TOP OF PLAYER'S DECK TEST: PASSED\n");

        }
        else {
            printf("CARDS WERE DRAWN FROM TOP OF PLAYER'S DECK TEST: FAILED\n");
            printf("CARDS IN THOSE POSITIONS: %d and %d\n", testState.hand[thisPlayer][ (testState.handCount[thisPlayer] - 1)], testState.hand[thisPlayer][handPos]);
	    testPassed = 0;
        }
    }
    else if (lastTreasureFound == 1 && inDeck == 0) {
       if ((testState.hand[thisPlayer][ (testState.handCount[thisPlayer] - 1)] == copper || testState.hand[thisPlayer][ (testState.handCount[thisPlayer] - 1)] == silver || testState.hand[thisPlayer][ (testState.handCount[thisPlayer] - 1)] == gold)
        && (testState.hand[thisPlayer][handPos] == copper || testState.hand[thisPlayer][handPos] == silver || testState.hand[thisPlayer][handPos] == gold)) {
            //printf("CARDS WERE DRAWN FROM PLAYER'S DECK TEST: PASSED\n");

        }
        else {
            printf("CARDS WERE DRAWN FROM PLAYER'S DECK TEST: FAILED\n");
	    printf("CARDS IN THOSE POSITIONS: %d and %d\n", testState.hand[thisPlayer][ (testState.handCount[thisPlayer] - 1)], testState.hand[thisPlayer][handPos]);
            testPassed = 0;
        }
 
    }
    else if (drawnTreasure == 1) {
        if (testState.hand[thisPlayer][handPos] == copper || testState.hand[thisPlayer][handPos] == silver || testState.hand[thisPlayer][handPos] == gold) {
            //printf("CARDS WERE DRAWN FROM PLAYER'S DECK TEST: PASSED\n");
        }
        else {
            printf("CARDS WERE DRAWN FROM PLAYER'S DECK TEST: FAILED\n");
	    printf("CARD IN THAT POSITION: %d\n", testState.hand[thisPlayer][handPos]);
            testPassed = 0;
        }    
    }
    if (testPassed == 1) {
        printf("TESTS OF CARDS EFECT ON THE PLAYER USING IT: PASSED\n");
    }
    printf("\n---------TEST TO ENSURE OTHER PLAYERS NOT AFFECTED------\n");

    for (j = 0; j < numPlayers; j++) {
    	if (j != thisPlayer) {
	    printf("\nPlayer %d\n", (j+1));
            if (testState.handCount[j] == state.handCount[j]) {
    	       // printf("HANDCOUNT OF OTHER PLAYER DIDN'T CHANGE TEST: PASSED\n");
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

    	    for (i = 0; i < testState.handCount[j]; i++) {
    	        if (testState.hand[j][i] != state.hand[j][i]) {
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
    	    //printf("VICTORY AND KINGDOM CARDS NOT AFFECTED TEST: FAILED\n");
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
	    for (j = 0; j < G.discardCount[p]; j++) {
                G.discard[p][j] = (rand() % treasure_map+1);
            }
	    for (j = 0; j < G.playedCardCount; j++) {
                G.playedCards[j] = (rand() % treasure_map+1);
            }
        }
	p = rand() % G.numPlayers;
        handPos = rand() % G.handCount[p];
	G.hand[p][handPos] = adventurer;
	G.whoseTurn = p;
	//printf("numPlayers: %d player: %d\n\n", G.numPlayers, p);
        result = testAdventurer(p, G, handPos);
        
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
