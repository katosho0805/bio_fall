#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <map>
#include <cfloat>
#include <cmath>
#include <queue>

using namespace std;

struct protein{
  vector<double> aa_prob;
  int loc;    
};

void LoadData(vector<protein>& data, string file_name){
  ifstream ifs(file_name);
  if(!ifs){
    cerr << "Cannot open file:" << file_name << endl;
    exit(1);
  }
  int num_seq; 
  ifs >> num_seq;

  string aa_order = "ACDEFGHIKLMNPQRSTVWY";
  map<char, int> aa_to_index;
  for(int i = 0; i < 20; i++){
    aa_to_index[aa_order[i]] = i;
  }

  for(int i = 0; i < num_seq; i++){
    protein tmp;
    tmp.aa_prob.resize(20, 0.0);

    string seq; 
    ifs >> seq;
    for(int j = 0; j < seq.size(); j++){
      tmp.aa_prob[aa_to_index[seq[j]]] += 1.0/seq.size();
    }        
    ifs >> tmp.loc;

    data.push_back(tmp);
  }
}

double CalcDist(protein a, protein b){
  double sum = 0.0;
  for(int i = 0; i < 20; i++){
    sum += pow(a.aa_prob[i] - b.aa_prob[i] , 2.0);
  }
  return sqrt(sum);
}

int main(void){
  vector<protein> training_data;
  LoadData(training_data, "train_mitochondrion_cytoplasm_dataset.txt");
  vector<protein> test_data;
  LoadData(test_data, "test_mitochondrion_cytoplasm_dataset.txt");

  int tp=0, fp=0, tn=0, fn=0;

  for(int i = 0; i < test_data.size(); i++){
    double min_dist = DBL_MAX;
    int min_index = -1;
    for(int j = 0; j < training_data.size(); j++){            
      double dist = CalcDist(test_data[i], training_data[j]);
      if(dist < min_dist){
	min_dist = dist;
	min_index = j;
      }      
    }

    int pred = training_data[min_index].loc;
    int actual = test_data[i].loc;
        
    if(pred == 1 && actual == 1){
      tp++;
    }else if(pred == 1 && actual == 0){
      fp++;
    }else if(pred == 0 && actual == 0){
      tn++;
    }else if (pred == 0 && actual == 1){
      fn++;
    }
  }

  double bal_acc   = ((tp/(double)(tp+fn)) + (tn/(double)(tn+fp))) / 2.0;

  cout << "Balanced Accuracy: " << bal_acc << endl;
}
