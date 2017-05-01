#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int testIsGameOver() {

    int i, j, k;
    struct gameState *testOne = malloc(sizeof(struct gameState));
    int numPlayers = 2;
    int king[10] = {adventurer, embargo, village, minion, mine, cutpurse, sea_hag, tribute, smithy, council_room};
    int seed = 1000;
    int oldProvince;
    int oldOne, oldTwo, oldThree;
    int testPassed = 1;
    int passCount = 0;
    printf("\n\nTESTS FOR isGameOver() FUNCTION BEGIN HERE\n\n");

    initializeGame(numPlayers, king, seed, testOne);

    int result = isGameOver(testOne);

    printf("TEST THAT FUNCTION CORRECTLY RETURNS 0 FOR A GAME IN-PROGRESS\n");
    if (result == 0) {
        printf("TEST OF IN-PROGRESS GAME PASSED\n");
    }
    else {
        printf("TEST OF IN-PROGRESS GAME FAILED\n");
        testPassed = 0;
    }

    printf("TEST THAT FUNCTION CORRECTLY RETURNS 1 WHEN PROVINCE PILE EMPTY\n");

    oldProvince = testOne->supplyCount[province];
    testOne->supplyCount[province] = 0;
    result = isGameOver(testOne);

    if (result == 1) {
        printf("TEST OF GAME OVER DUE TO EMPTY PROVINCE PILE PASSED\n");
    }
    else {
        printf("TEST OF GAME OVER DUE TO EMPTY PROVINCE PILE FAILED\n");
        testPassed = 0;
    }
    
    testOne->supplyCount[province] = oldProvince;
    printf("TEST THAT GAME ENDS WHEN ANY THREE OF SUPPLY PILE ARE EMPTY\n");
    
    for(i = 0; i < 25; i++) {
        oldOne = testOne->supplyCount[i];

        for(j = (i + 1); j < 25; j++) {
            oldTwo = testOne->supplyCount[j];
            for (k = (j + 1); k < 25; k++) {
                oldThree = testOne->supplyCount[k];

                testOne->supplyCount[i] = 0;
                testOne->supplyCount[j] = 0;
                testOne->supplyCount[k] = 0;

                result = isGameOver(testOne);

                if (result == 1) {
                    passCount++;
                }
                else {
                    printf("TEST OF GAME OVER DUE TO THREE EMPTY SUPPLY PILES FAILED FOR COMBINATION %d %d %d\n", i, j, k);
                    testPassed = 0;
                }
                testOne->supplyCount[k] = oldThree;
            }
            testOne->supplyCount[j] = oldTwo;
        }
        testOne->supplyCount[i] = oldOne;
    }

    printf("TEST OF GAME OVER DUE TO THREE EMPTY SUPPLY PILES PASSED FOR %d combination(s) out of 2300 possible\n", passCount);

    printf("\n\nFINAL RESULT FOR TEST OF isGameOver()\n\n");

    if (testPassed == 1) {
        printf("isGameOver() TESTS PASSED\n\n");
    }
    else {
        printf("isGameOver() TESTS FAILED\n\n");
    }

    free(testOne);

    return 0;
}


int main() {
    testIsGameOver();

    return 0;
}
