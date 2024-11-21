#include <iostream>
#include <vector> 
using namespace std;

int main(){
    int n, m;
    cout<<"Enter the number of processes: ";
    cin>>n;
    cout<<"Enter the number of block: ";
    cin>>m;
    vector<int> processes(n, 0);
    for(int i = 0; i<n; i++){
        cin>>processes[i];
    }

    vector<int> block(m, 0);
    for(int i = 0; i<m; i++){
        cin>>block[i];
    }

    vector<pair<int, int>> memory[m];

    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            if(block[j]>=processes[i]){
                memory[j].push_back({i, processes[i]});
                block[j]-=processes[i];
                break;
            }
        }   
    }

    for(int i = 0; i<m; i++){
        if(block[i]!=0){
            memory[i].push_back({-1, block[i]});
        }
    }


    cout<<"Memory State after First fit"<<endl;

    for(int i = 0; i<m; i++){
        cout<<"|";
        for(int j = 0; j<memory[i].size(); j++){
            if(memory[i][j].first==-1){
                cout<<"_ ("<<memory[i][j].second<<") ";
            }else{
                cout<<"P"<<memory[i][j].first<<" ("<<memory[i][j].second<<") ";
            }
        }
        cout<<"|";
    }

    return 0;

}