#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct process {
    int at;  // Arrival Time
    int bt;  // Burst Time
    int original_bt; // Original Burst Time
    int ct;  // Completion Time
    int tat; // Turnaround Time
    int wt;  // Waiting Time
} process;

// Comparator to sort processes by arrival time
bool cmp(process p1, process p2) {
    return p1.at < p2.at;
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<process> p(n);
    cout << "Enter Arrival Time and Burst Time for each process:\n";
    for (int i = 0; i < n; i++) {
        cin >> p[i].at >> p[i].bt;
        p[i].original_bt = p[i].bt; // Store the original burst time
    }

    sort(p.begin(), p.end(), cmp); // Sort processes by arrival time

    int currentTime = 0;
    vector<bool> finished(n, false);
    int completed = 0;

    while (completed < n) {
        int idx = -1;

        // Find the process with the shortest remaining time
        for (int i = 0; i < n; i++) {
            if (!finished[i] && p[i].at <= currentTime) {
                if (idx == -1 || p[i].bt < p[idx].bt) {
                    idx = i;
                }
            }
        }

        if (idx != -1) {
            // Execute the process for 1 unit of time
            p[idx].bt -= 1;

            if (p[idx].bt == 0) {
                finished[idx] = true;
                completed++;
                p[idx].ct = currentTime + 1;                    // Completion Time
                p[idx].tat = p[idx].ct - p[idx].at;            // Turnaround Time
                p[idx].wt = p[idx].tat - p[idx].original_bt;   // Waiting Time
            }
        }

        currentTime++; // Increment time
    }

    // Print results
    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t" << p[i].at << "\t" << p[i].original_bt << "\t"
             << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << endl;
    }

    return 0;
}
