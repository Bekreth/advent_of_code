#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <limits.h>

#include "busSchedule.h"

bool validTime(BusSchedule* schedule, int time) {
    int busID = 0;
    int modValue = 0;
    for (int j = 0; j < schedule->index; j++) {
        busID = schedule->buses[j];
        if (busID == 0) continue;
        modValue = (time % busID);
        if (modValue == 0) modValue = busID;
        if (busID - modValue != j) return false;
    }
    return true;
}

void solveGold(BusSchedule* schedule) {
    printf("solving gold\n");
    //int countBy = 0;
    //for (int i = 0; i < schedule->index; i++) {
    //    if (schedule->buses[i] > countBy) countBy = schedule->buses[i] - i;
    //}
    //printf("counting by %d\n", countBy);
    bool matches = false;
    unsigned long time = 1;
    while (!validTime(schedule, time)) {
        if (time % 100000000 == 0) printf("%ld\n", time);
        time++;
    }
    printf(" - %ld -\n", time);
}

void solveSilver(BusSchedule* schedule, int startingTime) {
    printf("solving silver \n");
    Solution solution = soonestBus(schedule, startingTime);
    int output = solution.busID * solution.waitTime;
    printf(" - %d - \n", output);
}

typedef struct Integer {
    unsigned long x[4];
} Integer;

unsigned long* binAddition(unsigned long* a, unsigned long* b) {
    unsigned long* ref = calloc(2 * sizeof(unsigned long), 1);
    unsigned long* c = calloc(2 * sizeof(unsigned long), 1);
    while (*b != *ref) {
            //find carry and shift it left
            *c = (*a & *b) << 1;
            //find the sum
            *a=*a^*b;
            *b=*c;
    }
    return a;
}


int main() {
    int i = 10;
    int j = 100;
    int k = 1000;
    unsigned long* A = calloc(2 * sizeof(unsigned long), 1);
    A[0] = 18446744073709551615;
    *A = *A << 1;
    unsigned long* B = calloc(2 * sizeof(unsigned long), 1);
    B[1] = 5;
    *B = *B << 1;
    printf("%d\n", *binAddition(A, B));
}

int pig(int argc, char** argv) {
    printf("starting\n");
    int startingTime = atoi(argv[1]);
    BusSchedule* schedule = newBusSchedule(argv[2]);
    solveSilver(schedule, startingTime);
    solveGold(schedule);

    freeBus(schedule);
}
