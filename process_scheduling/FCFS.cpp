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

    for(int i = 0; i<n; i++){
        cout<<currentTime<<"|";
        if(currentTime<p[i].at || currentTime == 0){
            if(currentTime<p[i].at){
                cout<<currentTime<<"|";
            }
            currentTime = p[i].ct = p[i].at + p[i].bt;
            p[i].tat = p[i].ct - p[i].at;
            p[i].wt = 0;

            
        }else{
            p[i].wt = currentTime - p[i].at;
            currentTime = p[i].ct = currentTime + p[i].bt;
            p[i].tat = p[i].ct - p[i].at;  
        }

        cout<<"P"<<i+1;

        cout<<currentTime<<"|";
    }

    return 0;
}