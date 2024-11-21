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
    int n, tq;
    cout << "Enter the number of processes: ";
    cin >> n;

    cout<<"Enter time quanta: ";
    cin>>tq;

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
        bool flag = false;
        for (int i = 0; i < n; i++) {
            if(!finished[i] && p[i].at <=currentTime){
                flag = true;
                int t = min(p[i].bt, tq);
                p[i].bt-=t;
                currentTime+=t;
                if (p[i].bt == 0) {
                    finished[i] = true;
                    completed++;
                    p[i].ct = currentTime;                   
                    p[i].tat = p[i].ct - p[i].at;            
                    p[i].wt = p[i].tat - p[i].original_bt;  
                }
            }
        }
        if(!flag)
            currentTime++;
    }

    cout << "\nProcess\tAT\tBT\tCT\tTAT\tWT\n";
    for (int i = 0; i < n; i++) {
        cout << "P" << i + 1 << "\t" << p[i].at << "\t" << p[i].original_bt << "\t"
             << p[i].ct << "\t" << p[i].tat << "\t" << p[i].wt << endl;
    }

    return 0;
}
