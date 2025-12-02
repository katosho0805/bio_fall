#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool HasCDS (string DNA){
    size_t start_pos=DNA.find("ATG");
    if(start_pos==string::npos){
        return false;
    }
    for(size_t i=start_pos+3;i+2<DNA.size();i+=3){
        if(DNA.substr(i,3)=="TGA"){
            size_t end_pos=i+2;
            size_t length=(i+3)-start_pos;
        }
    }
    if(DNA.size()>=300){
        return true;
    }else{
     return false;
    }
}

int main(void){
ifstream ifs("sequences.txt");
if(!ifs){
cout << "ファイルを開けませんでした。" << endl;
return 1;

string line;
vector<string> seq_with_cds;
while(getline(ifs, line) ){
if(HasCDS(line)){
seq_with_cds.push_back(line);

}
ifs.close();

cout << "CDSを含む配列:" << endl;
for(int i = 0; i < seq_with_cds.size(); i++){
cout << seq_with_cds[i] << endl;

return 0;