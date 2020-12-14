#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <limits.h>

#include "busSchedule.h"

BusSchedule* newBusSchedule(char* input) {
    BusSchedule* output = malloc(sizeof(BusSchedule));
    output->buses = malloc(0);
    output->index = 0;
    int index = 0;
    int bufferIndex = 0;
    char intBuffer[3] = "";
    bool running = true;
    while(running) {
        switch (input[index]) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            intBuffer[bufferIndex] = input[index];
            bufferIndex++;
            break;

        case '\0':
            running = false;
        case ',':
            output->buses = realloc(output->buses, (output->index + 1) * sizeof(int));
            output->buses[output->index] = atoi(intBuffer);
            output->index++;
            memset(intBuffer, 0, 3);
            bufferIndex = 0;
            break;

        default:
            break;
        }
        index++;
    }
    return output;
}

Solution soonestBus(BusSchedule* schedule, int currentTime) {
    Solution output;
    int soonest = INT_MAX;
    int nextArrival = 0;
    int busID = 1;
    for (int i = 0; i < schedule->index; i++) {
        busID = schedule->buses[i];
        if (busID == 0) continue;
        nextArrival = busID - (currentTime % busID) + currentTime;
        if (nextArrival < soonest) {
            soonest = nextArrival;
            output.busID = busID;
            output.waitTime = nextArrival - currentTime;
        }
    }
    return output;
}

void freeBus(BusSchedule* schedule) {
    free(schedule->buses);
    free(schedule);
}

void printBusSchedule(BusSchedule* schedule) {
    printf("== Schedule ==\n");
    for (int i = 0; i < schedule->index; i++) {
        printf(" - %d\n", schedule->buses[i]);
    }
}