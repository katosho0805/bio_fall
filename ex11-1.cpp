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

void PrintTopGenes(vector<double>& score, vector<string>& gene_name){
  
  vector<double> sorted_score = score;
  sort(sorted_score.begin(), sorted_score.end());

  double th = sorted_score[sorted_score.size() - NUM_TOP];
  
  //scoreとgene_nameを構造体にしてからソートをすれば以降のfor文の処理は不要になるが、
  //簡単のため今回はこちらを実装
  
  for(int i = 0; i < NUM_GENES; i++){
    if(score[i] >= th){
      cout << gene_name[i] << " " << score[i] << endl;
    }
  }
}

int main(void){
  vector<string> tissue_name(NUM_TISSUES, "");
  vector<string> gene_name(NUM_GENES, "");
  vector<vector<double> > expression_matrix(NUM_GENES, vector<double>(NUM_TISSUES, 0.0));
  LoadExpressionFile("gene_expression.txt",tissue_name, gene_name, expression_matrix);

  vector<double> tpm_mean(NUM_GENES, 0.0);
  for(int i = 0; i < NUM_GENES; i++){
    double sum = 0.0;
    for(int j = 0; j < NUM_TISSUES; j++){
      sum += expression_matrix[i][j];
    }
    sum /= NUM_TISSUES;
    tpm_mean[i] = sum;
  }
  cout << "High average scores" << endl;
  PrintTopGenes(tpm_mean, gene_name);
  cout << endl;


  vector<double> normalized_score(NUM_GENES, 0.0);
  for(int i = 0; i < NUM_GENES; i++){
    double mu = tpm_mean[i];
    double var = 0.0;
    for(int j = 0; j < NUM_TISSUES; j++){
      var += pow(expression_matrix[i][j] - mu, 2);
    }
    var /= NUM_TISSUES;
    normalized_score[i] = mu /(sqrt(var)+EPS);
  }
  cout << "High normalized scores" << endl;
  PrintTopGenes(normalized_score, gene_name);
  cout << endl;

  return 0;
}
