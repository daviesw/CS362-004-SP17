#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int testKingdom() {

    int i;
    int firstPassed = 1;
    int secondPassed = 1;
    int thirdPassed = 1;
    int king[10] = {smithy, tribute, sea_hag, cutpurse, mine, minion, village, embargo, gardens, adventurer};
    int *testArray = kingdomCards(king[0], king[1], king[2], king[3], king[4], king[5], king[6], king[7], king[8], king[9]);

    int *testTwo = kingdomCards(king[9], king[8], king[7], king[6], king[5], king[4], king[3], king[2], king[1], king[0]);

    printf("TESTING FIRST USE OF testKingdom()\n");
    for (i = 0; i < 10; i++) {
        if (king[i] == testArray[i]) {
            printf("KINGDOM CARD %d PASS\n", (i + 1));
        }
        else {
            printf("KINGDOM CARD %d FAILED\n", (i + 1));
            firstPassed = 0;
        }
    }
    printf("SECOND TEST OF testKingdom() WITH ALTERNATE VALUES\n");
    for (i = 0; i < 10; i++) {
        if (king[(9 - i)] == testTwo[i]) {
            printf("KINGDOM CARD %d PASS\n", (i + 1));
        }
        else {
            printf("KINGDOM CARD %d FAILED\n", (i + 1));
            secondPassed = 0;
        }
    }

    printf("COMPARE THE TWO ARRAYS OF KINGDOM CARDS--SHOULD NOT BE THE SAME\n");
    for (i = 0; i < 10; i++) {
        if (testTwo[i] != testArray[i]) {
            printf("KINGDOM CARD %d PASS\n", (i + 1));
        }
        else {
            printf("KINGDOM CARD %d FAILED\n", (i + 1));
            thirdPassed = 0;
        }
    }

    if (firstPassed == 1) {
        printf("FIRST TEST SUCCESSFUL\n");
    }
    else {
        printf("FIRST TEST FAILED\n");
    }

    if (secondPassed == 1) {
        printf("SECOND TEST SUCCESSFUL\n");
    }
    else {
        printf("SECOND TEST FAILED\n");
    }

    if (thirdPassed == 1) {
        printf("THIRD TEST SUCCESSFUL\n");
    }
    else {
        printf("THIRD TEST FAILED\n");
    }

    free(testArray);
    free(testTwo);

    return 0;
}

int main() {

    testKingdom();

    return 0;

}
