#include <vector>
#include <iostream>
#include <unistd.h>

using namespace std;

void Init(int s, vector<vector<int>>& world){
    if(s==0){
        world[5][4]=1;
        world[5][5]=1;
        world[5][6]=1;
    }else{
        world[0][1]=1;
        world[1][2]=1;
        world[2][0]=1;
        world[2][1]=1;
        world[2][2]=1;
    }
}
void printWorld(vector<vector<int>>& world){
    system("clear");
    int w=world.size();
    int h=world[0].size();

    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            char c=world[i][j]==1?'M': '';
            cout<<c;
        }
        cout<<endl;
    }
    usleep(100000);
}

void Simulation(vector<vector<int>>&world){
    int w=world.size();
    int h=world[0].size();
    vector<vector<int>>new_world(w,vector<int>(h,0));
    for(int i=0;i<w;i++){
        for(int j=0;j<h;j++){
            int neighbor_state_sum=0;
            int current_state=world[i][j];
        
    for(int k=-1;k<=1;k++){
        for(int l=-1;l<=1;l++){
            if(k==0&&l==0){
                continue;
            }
            if(i+ k < 0 || j + l < 0 || i + k >= w || j + l >= h){
                        continue;
                    }else{
                       neighbor_state_sum+= world[i+k][j+l];
                    }
                }
            }
            if(current_state==0){
                if(neighbor_state_sum == 3){
                    new_world[i][j] = 1;
                }
            }else{
                if(neighbor_state_sum == 2 || neighbor_state_sum == 3){
                    new_world[i][j] = 1;
                }
            }
        }
    }
    for(int i = 0; i < w; i++){
        for(int j = 0; j < h; j++){
            if(new_world[i][j] == 1){
                world[i][j] = 1;
            }else{
                world[i][j] = 0;
            }
        }
    }
}
     

