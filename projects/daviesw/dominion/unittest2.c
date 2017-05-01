#include "dominion.h"
#include "dominion_helpers.h"
#include "rngs.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int testGetCost() {

    printf("\nTEST getCost()\n");
    int testPassed = 1;
    if (getCost(curse) == 0) {
        printf("CURSE TEST PASSED\n");
    }
    else {
        printf("CURSE TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(estate) == 2) {
        printf("ESTATE TEST PASSED\n");
    }
    else {
        printf("ESTATE TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(duchy) == 5) {
        printf("DUCHY TEST PASSED\n");
    }
    else {
        printf("DUCHY TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(province) == 8) {
        printf("PROVINCE TEST PASSED\n");
    }
    else {
        printf("PROVINCE TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(copper) == 0) {
        printf("COPPER TEST PASSED\n");
    }
    else {
        printf("COPPER TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(silver) == 3) {
        printf("SILVER TEST PASSED\n");
    }
    else {
        printf("SILVER TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(gold) == 6) {
        printf("GOLD TEST PASSED\n");
    }
    else {
        printf("GOLD TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(adventurer) == 6) {
        printf("ADVENTURER TEST PASSED\n");
    }
    else {
        printf("ADVENTURER TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(council_room) == 5) {
        printf("COUNCIL_ROOM TEST PASSED\n");
    }
    else {
        printf("COUNCIL_ROOM FAILED\n");
        testPassed = 0;
    }

    if (getCost(feast) == 4) {
        printf("FEAST TEST PASSED\n");
    }
    else {
        printf("FEAST TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(gardens) == 4) {
        printf("GARDENS TEST PASSED\n");
    }
    else {
        printf("GARDENS TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(mine) == 5) {
        printf("MINE TEST PASSED\n");
    }
    else {
        printf("MINE TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(remodel) == 4) {
        printf("REMODEL TEST PASSED\n");
    }
    else {
        printf("REMODEL TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(smithy) == 4) {
        printf("SMITHY TEST PASSED\n");
    }
    else {
        printf("SMITHY TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(village) == 3) {
        printf("VILLAGE TEST PASSED\n");
    }
    else {
        printf("VILLAGE TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(baron) == 4) {
        printf("BARON TEST PASSED\n");
    }
    else {
        printf("BARON TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(great_hall) == 3) {
        printf("GREAT_HALL TEST PASSED\n");
    }
    else {
        printf("GREAT_HALL TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(minion) == 5) {
        printf("MINION TEST PASSED\n");
    }
    else {
        printf("MINION TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(steward) == 3) {
        printf("STEWARD TEST PASSED\n");
    }
    else {
        printf("STEWARD TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(tribute) == 5) {
        printf("TRIBUTE TEST PASSED\n");
    }
    else {
        printf("TRIBUTE TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(ambassador) == 3) {
        printf("AMBASSADOR TEST PASSED\n");
    }
    else {
        printf("AMBASSADOR TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(cutpurse) == 4) {
        printf("CUTPURSE TEST PASSED\n");
    }
    else {
        printf("CUTPURSE TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(embargo) == 2) {
        printf("EMBARGO TEST PASSED\n");
    }
    else {
        printf("EMBARGO TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(outpost) == 5) {
        printf("OUTPOST TEST PASSED\n");
    }
    else {
        printf("OUTPOST TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(salvager) == 4) {
        printf("SALVAGER TEST PASSED\n");
    }
    else {
        printf("SALVAGER TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(sea_hag) == 4) {
        printf("SEA_HAG TEST PASSED\n");
    }
    else {
        printf("SEA_HAG TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(treasure_map) == 4) {
        printf("TREASURE_MAP TEST PASSED\n");
    }
    else {
        printf("TREASURE_MAP TEST FAILED\n");
        testPassed = 0;
    }

    if (getCost(9999) == -1) {
        printf("INVALID CARD NUMBER TEST: PASSED\n");
    }
    else {
        printf("INVALID CARD NUMBER TEST: FAILED\n");
        testPassed = 0;
    }


    if (testPassed == 1) {
        printf("\n\ngetCost() TEST PASSED\n\n");
    }
    else {
        printf("\n\ngetCost() TEST FAILED\n\n");
    }

    return 0;
}

int main() {
    testGetCost();

    return 0;
}
