#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

void SetRuleNember(int& rule_number,vector<int>& rule_set){
    cout<<"Input rule_number:";
    cin >>rule_number;

    if(rule_number<0||rule_number>255){
        cout<<"The input number is inappropriate."<<endl;
        exit(1);
    }
    int x=rule_number;
    for(int i=0;i<8;i++){
        rule_set[7-i]=x%2;
        x/=2;
    }
}

void OutputState(ofstream& ost,const vector<int>&state){
    for(int i=0;i<state.size();i++){
        if(state[i]==1){
            ost<< "";
        }else{
            ost<<"";
        }
    }
    ost<<endl;
}

int GetNextState(const vector<int>& rule_set,int a,int b,int c){
    return (rule_set[7-(a*4+b*2+c*1)]);
}

void Simulation(ofstream& ost,vector<int>& state, const vector<int>& rule_set){
    int frame_size=state.size();
    vector<int> temp_state(frame_size,0);
    for(int i=0;i<frame_size;i++){
        int pre_i = i==0 ? frame_size-1 : i-1;
    int post_i = i==frame_size-1 ? 0 : i+1;
        
        temp_state[i]=GetNextState(rule_set,state[pre_i],state[i],state[post_i]);
    }

    copy(temp_state.begin(),temp_state.end(),state.begin());
    OutputState(ost,state);
}

int main(void){
    int step_size=200;
    int rule_number=0;
    vector<int> rule_set(8,0);
    vector<int> state(step_size*2+1,0);
    state[state.size()/2]=1;

    SetRuleNember(rule_number,rule_set);

     ofstream ost()
}
