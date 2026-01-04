#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cmath>
#include <map>
#include <algorithm>
#include <iomanip>

using namespace std;

const string AA_ORDER = "ACDEFGHIKLMNPQRSTVWY";

struct Protein {
    string seq;
    int label; 
    vector<double> features; 
};


vector<Protein> LoadDataset(string filename) {
    vector<Protein> data;
    ifstream ifs(filename);
    if (!ifs) {
        cerr << "Error: Cannot open " << filename << endl;
        exit(1);
    }

    int num_data;
    ifs >> num_data; 
    data.resize(num_data);

    for (int i = 0; i < num_data; ++i) {
        ifs >> data[i].seq >> data[i].label;
    }
    return data;
}

void ExtractAAC(vector<Protein>& data, bool use_n_term) {
    map<char, int> aa_to_index;
    for (int i = 0; i < 20; ++i) aa_to_index[AA_ORDER[i]] = i;

    for (auto& p : data) {
        p.features.assign(20, 0.0);
        string target_seq = p.seq;
        
        if (use_n_term && target_seq.size() > 30) {
            target_seq = target_seq.substr(0, 30);
        }

        double len = (double)target_seq.size();
        if (len == 0) continue;

        for (char aa : target_seq) {
            if (aa_to_index.count(aa)) {
                p.features[aa_to_index[aa]] += 1.0;
            }
        }
        for (double& v : p.features) v /= len;//確率に変換する
    }
}

// 発展課題3用
void ExtractDPC(vector<Protein>& data, bool use_n_term) {
    map<char, int> aa_to_index;
    for (int i = 0; i < 20; ++i) aa_to_index[AA_ORDER[i]] = i;

    for (auto& p : data) {
        p.features.assign(400, 0.0); 
        string target_seq = p.seq;

        if (use_n_term && target_seq.size() > 30) {
            target_seq = target_seq.substr(0, 30);
        }

        double len = (double)target_seq.size();
        if (len < 2) continue; 

        for (size_t i = 0; i < target_seq.size() - 1; ++i) {
            char aa1 = target_seq[i];
            char aa2 = target_seq[i+1];
            if (aa_to_index.count(aa1) && aa_to_index.count(aa2)) {
                int idx1 = aa_to_index[aa1];
                int idx2 = aa_to_index[aa2];
                p.features[idx1 * 20 + idx2] += 1.0;
            }
        }
        for (double& v : p.features) v /= (len - 1.0);//確率に変換する
    }
}

double EuclideanDistance(const vector<double>& v1, const vector<double>& v2) {
    double sum = 0.0;
    for (size_t i = 0; i < v1.size(); ++i) {
        double d = v1[i] - v2[i];
        sum += d * d;
    }
    return sqrt(sum);
}// ユークリッド距離の計算

int PredictKNN(const vector<Protein>& train_data, const Protein& test_sample, int k) {
    vector<pair<double, int>> distances;
    distances.reserve(train_data.size());

    for (const auto& train_sample : train_data) {
        double dist = EuclideanDistance(test_sample.features, train_sample.features);
        distances.push_back({dist, train_sample.label});
    }

    // 距離が小さい順にソート 
    sort(distances.begin(), distances.end());

    int vote_mito = 0; 
    int vote_cyto = 0; 

    for (int i = 0; i < k; ++i) {
        if (distances[i].second == 1) vote_mito++;
        else vote_cyto++;
    }

    if (vote_mito > vote_cyto) return 1;
    else return 0;
}

void Evaluate(const vector<int>& predictions, const vector<int>& ground_truths, string title) {
    int TP = 0, FN = 0, TN = 0, FP = 0;

    for (size_t i = 0; i < predictions.size(); ++i) {
        int pred = predictions[i];
        int true_label = ground_truths[i];

        if (true_label == 1) { 
            if (pred == 1) TP++;
            else FN++;
        } else { 
            if (pred == 0) TN++;
            else FP++;
        }
    }

    double sensitivity = (TP + FN == 0) ? 0.0 : (double)TP / (TP + FN);
    double specificity = (TN + FP == 0) ? 0.0 : (double)TN / (TN + FP);
    double balanced_acc = (sensitivity + specificity) / 2.0;

    cout << "[" << title << "]" << endl;
    cout << "  TP: " << TP << ", FN: " << FN << endl;
    cout << "  FP: " << FP << ", TN: " << TN << endl;
    cout << "  Sensitivity: " << fixed << setprecision(4) << sensitivity << endl;
    cout << "  Specificity: " << fixed << setprecision(4) << specificity << endl;
    cout << "  Balanced Accuracy: " << fixed << setprecision(4) << balanced_acc << endl;
    cout << "----------------------------------------" << endl;
}

void RunExperiment(vector<Protein>& train_data, vector<Protein>& test_data, 
                   string feature_type, bool use_n_term, vector<int> k_list) {
    
    if (feature_type == "AAC") {
        ExtractAAC(train_data, use_n_term);
        ExtractAAC(test_data, use_n_term);
    } else if (feature_type == "DPC") {
        ExtractDPC(train_data, use_n_term);
        ExtractDPC(test_data, use_n_term);
    }

    vector<int> ground_truths;
    for(const auto& p : test_data) ground_truths.push_back(p.label);

    for (int k : k_list) {
        vector<int> predictions;
        predictions.reserve(test_data.size());

        for (const auto& test_sample : test_data) {
            int pred = PredictKNN(train_data, test_sample, k);
            predictions.push_back(pred);
        }

        string condition = feature_type + (use_n_term ? " (N-term 30)" : " (Full)");
        string title = "k=" + to_string(k) + ", " + condition;
        Evaluate(predictions, ground_truths, title);
    }
}

int main() {
    cout << "Loading datasets..." << endl;
    vector<Protein> train_data = LoadDataset("train_mitochondrion_cytoplasm_dataset.txt");
    vector<Protein> test_data = LoadDataset("test_mitochondrion_cytoplasm_dataset.txt");
    cout << "Train size: " << train_data.size() << ", Test size: " << test_data.size() << endl;
    cout << "----------------------------------------" << endl;

    cout << "=== Exercise 1: Nearest Neighbor (k=1) ===" << endl;
    RunExperiment(train_data, test_data, "AAC", false, {1});//演習問題1

    cout << "\n=== Exercise 2: k-NN (Full vs N-term 30) ===" << endl;
    vector<int> k_list = {1, 3, 5, 7};//演習問題2
    
    RunExperiment(train_data, test_data, "AAC", false, k_list);
    
    cout << "\n--- N-terminal 30 residues ---" << endl;
    RunExperiment(train_data, test_data, "AAC", true, k_list);

    cout << "\n=== Advanced Exercise 3: Dipeptide Composition (N-term 30) ===" << endl;
    RunExperiment(train_data, test_data, "DPC", true, k_list);//演習問題3

    return 0;
}