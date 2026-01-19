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

struct Correlation{
  double corr;
  int i;
  int j;
};

bool CmpCorr(const Correlation& a, const Correlation& b) {
  return a.corr > b.corr;   // true ならaをbより前に置く(降順にする、昇順にしたい場合は<を使う)
}

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

  vector<string> filtered_gene_name;
  vector<vector<double> > filtered_expression_matrix;
  vector<double> mean_tpm;
  vector<double> var_tpm;
  
  for(int i = 0; i < NUM_GENES; i++){
    int low_expr_count = 0;
    double sum = 0.0;
    double squared_sum = 0.0;

    for(int j = 0; j < NUM_TISSUES; j++){
      if(expression_matrix[i][j] > 100.0){
	expression_matrix[i][j] = 100;
      }
      double val = expression_matrix[i][j];
      if(val < 1.0){
	low_expr_count++;
      }
      sum += val;
      squared_sum += val * val;
    }
    double mean = sum / NUM_TISSUES;        
    double var = squared_sum / NUM_TISSUES - mean * mean;
        
    double low_expr_ratio = (double)(low_expr_count) / NUM_TISSUES;
    if (low_expr_ratio <= 0.8 && var >= 100.0){
      filtered_gene_name.push_back(gene_name[i]);
      filtered_expression_matrix.push_back(expression_matrix[i]);
      mean_tpm.push_back(mean);
      var_tpm.push_back(var);
    }
  }
  int filtered_gene_size = filtered_gene_name.size();

  vector<Correlation> all_pairs;
  all_pairs.reserve(filtered_gene_size * (filtered_gene_size - 1) / 2);

  for(int i = 0; i < filtered_gene_size; i++){
    for(int j = i+1; j < filtered_gene_size; j++){
      double cov_ij = 0.0;

      for(int k = 0; k < NUM_TISSUES; k++){
	cov_ij += (filtered_expression_matrix[i][k] - mean_tpm[i]) * (filtered_expression_matrix[j][k] - mean_tpm[j]);
      }
      cov_ij /= NUM_TISSUES;

      double corr = cov_ij / sqrt(var_tpm[i] * var_tpm[j]);
      all_pairs.push_back({corr, i, j});
    }
  }

  sort(all_pairs.begin(), all_pairs.end(), CmpCorr);

  for(int i = 0; i < NUM_TOP; i++){
    Correlation p = all_pairs[i];
    cout << p.corr << " " << filtered_gene_name[p.i] << " " << filtered_gene_name[p.j] << "\n";
  }
}
