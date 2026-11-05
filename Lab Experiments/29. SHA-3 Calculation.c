#include <stdio.h>
int main() {
    int state = 1600;
    int block = 1024;
    int lane = 64;
    int rate = block;
    int capacity = state - rate;
    int rateLanes = rate / lane;
    int capacityLanes = capacity / lane;
    printf("SHA-3 State Size: %d bits\n", state);
    printf("Block Size: %d bits\n", block);
    printf("Rate: %d bits\n", rate);
    printf("Capacity: %d bits\n", capacity);
    printf("\nRate Lanes: %d\n", rateLanes);
    printf("Capacity Lanes: %d\n", capacityLanes);
    printf("\nInitially:\n");
    printf("Rate lanes: Nonzero\n");
    printf("Capacity lanes: Zero\n");
    printf("\nPermutation is ignored.\n");
    printf("Capacity lanes remain zero.\n");
    printf("Time required: Never (Infinite).\n");
    return 0;
}
