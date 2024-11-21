#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_REQUESTS 10
#define DISK_SIZE 200

// Comparator function for qsort
int compareTracks(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

// C-SCAN disk scheduling function
void CSCAN(int requests[], int headPosition, char *direction) {
    int totalSeekDistance = 0;
    int seekDifference, currentTrack;
    int leftRequests[NUM_REQUESTS], rightRequests[NUM_REQUESTS];
    int seekSequence[NUM_REQUESTS + 3]; // Accommodates requests + disk boundaries
    int leftCount = 0, rightCount = 0;

    // Add disk boundaries
    leftRequests[leftCount++] = 0;             // Add the first track
    rightRequests[rightCount++] = DISK_SIZE - 1; // Add the last track

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

    int sequenceIndex = 0;

    if (strcmp(direction, "right") == 0) {
        // Process requests on the right of the head
        for (int i = 0; i < rightCount; i++) {
            currentTrack = rightRequests[i];
            seekSequence[sequenceIndex++] = currentTrack;
            seekDifference = abs(currentTrack - headPosition);
            totalSeekDistance += seekDifference;
            headPosition = currentTrack;
        }

        // Jump to the first track and continue processing left requests
        headPosition = 0;
        totalSeekDistance += (DISK_SIZE - 1); // Jump distance
        for (int i = 0; i < leftCount; i++) {
            currentTrack = leftRequests[i];
            seekSequence[sequenceIndex++] = currentTrack;
            seekDifference = abs(currentTrack - headPosition);
            totalSeekDistance += seekDifference;
            headPosition = currentTrack;
        }
    } else if (strcmp(direction, "left") == 0) {
        // Process requests on the left of the head
        for (int i = leftCount - 1; i >= 0; i--) {
            currentTrack = leftRequests[i];
            seekSequence[sequenceIndex++] = currentTrack;
            seekDifference = abs(currentTrack - headPosition);
            totalSeekDistance += seekDifference;
            headPosition = currentTrack;
        }

        // Jump to the last track and continue processing right requests
        headPosition = DISK_SIZE - 1;
        totalSeekDistance += (DISK_SIZE - 1); // Jump distance
        for (int i = rightCount - 1; i >= 0; i--) {
            currentTrack = rightRequests[i];
            seekSequence[sequenceIndex++] = currentTrack;
            seekDifference = abs(currentTrack - headPosition);
            totalSeekDistance += seekDifference;
            headPosition = currentTrack;
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
    char direction[] = "right";

    CSCAN(requests, headPosition, direction);
    return 0;
}
