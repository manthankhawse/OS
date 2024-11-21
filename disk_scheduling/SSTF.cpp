#include <iostream>
#include <vector> 
#include <climits>
using namespace std;

int findClosest(vector<int>& r, vector<bool>& visited, int curr){
    int min_dist = INT_MAX;
    int idx = -1;
    for(int i = 0; i<r.size(); i++){
        if(!visited[i] && min_dist>abs(curr-r[i])){
            min_dist = abs(curr-r[i]);
            idx = i;
        }
    }

    return idx;
}

int main(){
    int n, st;
    cin>>n;
    vector<int> requests(n);
    for(int i = 0; i<n; i++){
        cin>>requests[i];
    }

    cin>>st;
    int curr = st;
    int dist = 0;
    vector<bool> visited(n, false);
    for(int i = 0; i<n; i++){
        int idx = findClosest(requests, visited, curr);
        cout<<curr<<"->"<<requests[idx]<<" "<<abs(requests[idx]-curr)<<endl;
        dist+=abs(requests[idx]-curr);
        curr = requests[idx];
        visited[idx] = true;
    }



    cout<<(float)dist/n<<endl;

    return 0;
}