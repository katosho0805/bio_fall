#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>

#define NUM_TISSUES 68
#define NUM_GENES 19594
#define NUM_TOP 5
#define EPS 0.01

using namespace std;

void LoadExpressionFile(string file_name, vector<string>& tissue_name, 
			vector<string>& gene_name,  vector<vector<double> >& expression_matrix){
        
  ifstream ifs(file_name);
  if(!ifs){
    cerr << "Cannot open expression file:" << file_name << endl;
    exit(1);
  }
  string tmp;
  ifs >> tmp;

  for(int i = 0; i < NUM_TISSUES; i++){
    ifs >> tissue_name[i];
  }
    
  for(int i = 0; i < NUM_GENES; i++){
    ifs >> gene_name[i];
    for(int j = 0; j < NUM_TISSUES; j++){
      ifs >> expression_matrix[i][j];
    }
  }
  ifs.close();
}

int main(void){
  vector<string> tissue_name(NUM_TISSUES, "");
  vector<string> gene_name(NUM_GENES, "");
  vector<vector<double> > expression_matrix(NUM_GENES, vector<double>(NUM_TISSUES, 0.0));
  LoadExpressionFile("gene_expression.txt",tissue_name, gene_name, expression_matrix);

  vector<int> num_tissue_specific_genes(NUM_TISSUES, 0);
  vector<vector<string> > tissue_specific_genes(NUM_TISSUES);

  for(int i = 0; i < NUM_GENES; i++){
    double max_val = 0.0;
    double mean = 0.0;
    int max_index = -1;

    for(int j = 0; j < NUM_TISSUES; j++){
      double val = expression_matrix[i][j];
      mean += val;
      if(max_val < val){
	max_val = val;
	max_index = j;
      }
    }
    mean /= NUM_TISSUES;
    if(max_index == -1){continue;}

    double sum = 0.0;
    for(int j = 0; j < NUM_TISSUES; j++){
      double val = expression_matrix[i][j];
      sum += 1 - val/max_val;
    }
    double tau = sum / (NUM_TISSUES-1);
    if(tau > 0.85){
      num_tissue_specific_genes[max_index]++;
    }
    if(tau > 0.95 && mean >= 30){
      tissue_specific_genes[max_index].push_back(gene_name[i]);
    }
  }

  int max_val = 0;
  int max_index = -1;
  for(int i = 0; i < NUM_TISSUES; i++){
    int val = num_tissue_specific_genes[i];
    cout << tissue_name[i] << ":" << val << endl;
    
    if(max_val < val){
      max_val = val;
      max_index = i;
    }
  }
  cout << endl;

  cout << "The tissue with the highest number of tissue-specific genes: " << tissue_name[max_index] << endl;
  cout << "example:" << endl;
  for(int i = 0; i < tissue_specific_genes[max_index].size(); i++){
    cout << tissue_specific_genes[max_index][i] << endl;
  }
  return 0;
}
