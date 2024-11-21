#include <iostream>
#include <vector> 
using namespace std;

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
    for(int i = 0; i<n; i++){
        cout<<curr<<"->"<<requests[i]<<" "<<abs(requests[i]-curr)<<endl;
        dist+=abs(requests[i]-curr);
        curr = requests[i];
    }



    cout<<(float)dist/n<<endl;

    return 0;
}