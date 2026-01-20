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
    int len = seq.size() < 30 ? seq.size() : 30;
    for(int j = 0; j < len; j++){
      tmp.aa_prob[aa_to_index[seq[j]]] += 1.0/len;
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

  
  vector<int> k_array{1, 3, 5, 7};

  for(int l = 0; l < k_array.size(); l++){
    int k = k_array[l];
    int tp=0, fp=0, tn=0, fn=0;
    for(int i = 0; i < test_data.size(); i++){
      priority_queue<pair<double, int> > max_heap;
      //答えを出す分にはどちらでも良いが、折角なので今回はソートではなくヒープ(priority_queue)を活用して実装を行った。
      //ヒープはpop()とすることでデータに格納されている最大値が削除される。
      //よってこのプログラムではヒープに格納されているデータの数がk個より多くなると、
      //データの挿入→最大値の削除→データの挿入→最大値の削除...と繰り返すことで、最終的にはデータが小さい順にk個残る。

      //ソートにかかる計算量がO(NlogN)であるの対し、ヒープを使った手法だと計算量がO(NlogK)となり計算量が良い。
      //この辺の話は「アルゴリズムと情報処理」の講義で紹介した。

      //ソートで行う場合と、同一順位の取り扱い方が変わるので数値に微妙な違いが見られる可能性があることに注意。

      for(int j = 0; j < training_data.size(); j++){            
	double dist = CalcDist(test_data[i], training_data[j]);
	max_heap.push({dist, j});
	if ((int)max_heap.size() > k) {
	  max_heap.pop();
	}    
      }

      int loc_sum = 0;
      while (!max_heap.empty()) {
	loc_sum += training_data[max_heap.top().second].loc;
	max_heap.pop();
      }
      int pred = (loc_sum >= (k+1)/2) ? 1 : 0;

        
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

    cout << k <<" Balanced Accuracy: " << bal_acc << endl;
  }

  
}
