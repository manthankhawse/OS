#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_REQUESTS 10
#define DISK_SIZE 200

// Comparator function for qsort
int compareTracks(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// SCAN disk scheduling function
void SCAN(int requests[], int headPosition, char *direction) {
    int totalSeekDistance = 0;
    int seekDifference, currentTrack;
    int leftRequests[NUM_REQUESTS], rightRequests[NUM_REQUESTS];
    int seekSequence[NUM_REQUESTS + 2]; // Accommodates requests + disk boundaries
    int leftCount = 0, rightCount = 0;

    // Add disk boundaries based on the initial direction
    if (strcmp(direction, "left") == 0) {
        leftRequests[leftCount++] = 0; // Add track 0 for left direction
    } else if (strcmp(direction, "right") == 0) {
        rightRequests[rightCount++] = DISK_SIZE - 1; // Add last track for right direction
    }

    // Divide requests into left and right of the head position
    for (int i = 0; i < NUM_REQUESTS; i++) {
        if (requests[i] < headPosition) {
            leftRequests[leftCount++] = requests[i];
        } else if (requests[i] > headPosition) {
            rightRequests[rightCount++] = requests[i];
        }
    }

    // Sort left and right requests
    qsort(leftRequests, leftCount, sizeof(int), compareTracks);
    qsort(rightRequests, rightCount, sizeof(int), compareTracks);

    int remainingPasses = 2; // Two passes: one for each direction
    int sequenceIndex = 0;

    // Service requests in both directions
    while (remainingPasses--) {
        if (strcmp(direction, "left") == 0) {
            // Process left-side requests in reverse order
            for (int i = leftCount - 1; i >= 0; i--) {
                currentTrack = leftRequests[i];
                seekSequence[sequenceIndex++] = currentTrack;
                seekDifference = abs(currentTrack - headPosition);
                totalSeekDistance += seekDifference;
                headPosition = currentTrack;
            }
            direction = "right"; // Switch direction
        } else if (strcmp(direction, "right") == 0) {
            // Process right-side requests in ascending order
            for (int i = 0; i < rightCount; i++) {
                currentTrack = rightRequests[i];
                seekSequence[sequenceIndex++] = currentTrack;
                seekDifference = abs(currentTrack - headPosition);
                totalSeekDistance += seekDifference;
                headPosition = currentTrack;
            }
            direction = "left"; // Switch direction
        }
    }

    // Print results
    printf("Total seek distance: %d\n", totalSeekDistance);
    printf("Seek sequence: ");
    for (int i = 0; i < sequenceIndex; i++) {
        printf("%d ", seekSequence[i]);
    }
    printf("\n");
}

int main() {
    int requests[NUM_REQUESTS] = {126, 90, 14, 50, 25, 42, 51, 78, 102, 100};
    int headPosition = 42;
    char direction[] = "left";

    SCAN(requests, headPosition, direction);
    return 0;
}
