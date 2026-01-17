#include<iostream>
#include<fstream>
#include<vector>
#include<string>

#define NUM_TISSUES 68
#define NUM_GENES 19594

using namespace std;

void LoadExpressinFile(string file_name,vector<string >& tissue_name,vector<string>& gane_name,){

    ifstream ifs(file_name);
    if(!ifs){
        cerr<<"Cannot open ewpression file:"<<file_name<<endl;
        exit(1);
  }
string tmp;
ifs>>tmp;

for(int i=0;i<NUM_TISSUES;i++){
    ifs>>tissue_name[i];
}

for(int i=0;i<NUM_GENES;i++){
  ifs>>gene_name[i];
  for(int j=0;j<NUM_TISSUES;j++){
    ifs>>expression_matrix[i][j];
  }
}
ifs.close()
}

int main(void){
    vector<string> tissue_name(NUM_TISSUES,"");
    vector<string> gene_name(NUM_GENES,"");
    vector<vector<double>>expression_matrix(NUM_GENES,vector<double>(NUM_TISSUES,0.0));
    LoadExpressionFile("gene_expression.txt",tissue_name,gene_name,expression_mmatrix);
}
