#ifndef bus_schedule_h
#define bus_schedule_h

typedef struct BusSchedule {
    int* buses;
    int index;
} BusSchedule;

typedef struct Solution {
    int busID;
    int waitTime;
} Solution;

BusSchedule* newBusSchedule(char* input);
Solution soonestBus(BusSchedule* schedule, int currentTime);
void freeBus(BusSchedule* schedule);
void printBusSchedule(BusSchedule* schedule);

#endif