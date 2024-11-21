#include <iostream>
#include <vector> 
using namespace std;

bool allFinished(vector<bool>& finished){
    for(int i = 0; i<finished.size(); i++){
        if(!finished[i]){
            return false;
        }
    }

    return true;
}

bool check(vector<int>& request, vector<int>& avl){
    for(int i = 0; i<request.size(); i++){
        if(request[i]>avl[i]){
            return false;
        }
    }

    return true;
}

int main(){
    int n, m;
    cout<<"enter the number of processes: ";
    cin>>n;
    cout<<"enter the types of resoures: ";
    cin>>m;
    vector<int> work(m, 0);
    cout<<"Enter the number of work resources of each type:\n";
    for(int i = 0; i<m; i++){
        cin>>work[i];
    }

    vector<vector<int>> allocation;
    vector<vector<int>> request;
    for(int i = 0; i<n; i++){
        cout<<"Enter allocation of the process"<< i+1<<endl;
        vector<int> curr(m, 0);
        for(int j = 0; j<m; j++){
            cin>>curr[j];
        }

        allocation.push_back(curr);
    }

    for(int i = 0; i<n; i++){
        cout<<"Enter request of the process"<< i+1<<endl;
        vector<int> c1urr(m, 0);
        for(int j = 0; j<m; j++){
            cin>>curr[j];
        }

        request.push_back(curr);
    }

    vector<bool> finished(n, false);

    vector<int> seq;

    while(true){

        bool found = false;

        for(int j = 0; j<n; j++){
            if(!finished[j] && check(request[j], work)){
                found = true;
                for(int k = 0; k<m; k++){
                    work[k] += allocation[j][k];
                }
                finished[j] = true;
                seq.push_back(j);
            }
        }

        if(!found){
            cout<<"Deadlock detected"<<endl;
            exit(0);
        }

        if(allFinished(finished)){
            break;
        }
    }

    cout<<"Deadlock is not present"<<endl;

    for(int i = 0; i<seq.size(); i++){
        cout<<seq[i]+1<<"->";
    }

    return 0;

    
}