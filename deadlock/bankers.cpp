#include <bits/stdc++.h>
using namespace std;  

bool isSafe(vector<vector<int>>& max, vector<vector<int>>& alloc, vector<int>& avail, int process, int numResources) {  
    vector<int> need(numResources);  
    for (int i = 0; i < numResources; i++) {  
        need[i] = max[process][i] - alloc[process][i];  
    }  
    for (int i = 0; i < numResources; i++) {  
        if (need[i] > avail[i]) {  
            return false;  
        }  
    }  
    return true;  
}  

bool bankersAlgorithm(vector<vector<int>>& max, vector<vector<int>>& alloc, vector<int>& avail, int numProcesses, int numResources) {  
    vector<bool> finish(numProcesses, false);  
    vector<int> safeSequence;  
    int numFinished = 0;  
    while (numFinished < numProcesses) {  
        bool found = false;  
        for (int i = 0; i < numProcesses; i++) {  
            if (!finish[i] && isSafe(max, alloc, avail, i, numResources)) {  
                for (int j = 0; j < numResources; j++) {  
                    avail[j] += alloc[i][j];  
                }  
                safeSequence.push_back(i);  
                finish[i] = true;  
                numFinished++;  
                found = true;  
            }  
        }  
        if (!found) {  
            return false;  
        }  
    } 
    cout << "Safe sequence: ";  
    for (int i = 0; i < safeSequence.size(); i++) {  
        cout << "P" << safeSequence[i];  
        if (i < safeSequence.size() - 1) {  
            cout << " -> ";  
        }  
    }  
    cout << endl;  
    return true;  
}  

int main() {  
    int numProcesses, numResources;  
    cout << "number of processes: ";  
    cin >> numProcesses;  
    cout << "number of resources: ";  
    cin >> numResources;  
    vector<vector<int>> max(numProcesses, vector<int>(numResources));  
    vector<vector<int>> alloc(numProcesses, vector<int>(numResources));  
    vector<int> avail(numResources);  
    cout << "Enter the maximum resource matrix:" << endl;  
    for (int i = 0; i < numProcesses; i++) {  
        for (int j = 0; j < numResources; j++) {  
            cin >> max[i][j];  
        }  
    }  
    cout << "allocation matrix: " << endl;  
    for (int i = 0; i < numProcesses; i++) {  
        for (int j = 0; j < numResources; j++) {  
            cin >> alloc[i][j];  
        }  
    }  
    cout << "available resource vector: " << endl;  
    for (int j = 0; j < numResources; j++) {  
        cin >> avail[j];  
    }  
    if (bankersAlgorithm(max, alloc, avail, numProcesses, numResources)) {  
        cout << "System is in a safe state." << endl;  
    } else {  
        cout << "System is in an unsafe state." << endl;  
    }  
    return 0;  
}  