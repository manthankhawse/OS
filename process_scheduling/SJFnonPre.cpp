#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

typedef struct process{
    int at;
    int bt;
    int pt;
    int tat;
    int ct;
    int wt;
}process;

bool cmp(process p1, process p2){
    return p1.at<p2.at;
}

int main(){
    int n;
    cout<<"Enter the number of processes\n";
    cin>>n;
    vector<process> p; 
    for(int i = 0; i<n; i++){
        process x;
        cin>>x.at;
        cin>>x.bt;
        cin>>x.pt;

        p.push_back(x);
    }

    sort(p.begin(), p.end(), cmp);

    int currentTime = 0;
    vector<bool> finished(n, false);
    for(int i = 0; i<n; i++){
        cout<<currentTime<<"|";
        if(currentTime<p[i].at){
            currentTime+=p[i].at;
            cout<<currentTime<<"|";
        }
        int min_idx = -1;
        for(int j = 0; j<n; j++){
            if((min_idx==-1 || (currentTime >= p[j].at && p[j].bt < p[min_idx].bt)) && !finished[j]){
                min_idx = j;
            }
        }

        cout<<"P"<<min_idx+1;

        currentTime += p[min_idx].bt;
        p[min_idx].ct = currentTime;
        p[min_idx].tat = p[min_idx].ct - p[min_idx].at;
        p[min_idx].wt = p[min_idx].tat - p[min_idx].bt;
        finished[min_idx] = true;

        cout<<currentTime<<"|"; 
    }

    return 0;
}