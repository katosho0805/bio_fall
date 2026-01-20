#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

bool equals_seq(const string &t, int pos, string& s){
    for(int i = 0; i < s.size(); i++){
        if(t[pos + i] != s[i]){
            return false;
        }
    }
    return true;
}

vector<int> naive_search(string &genome, string &pattern){
    vector<int> hit;
    
    for (int i = 0; i <= genome.size() - pattern.size(); i++) {
        if(equals_seq(genome, i, pattern)){
            hit.push_back(i);
        }
    }
    return hit;
}

int main(void){
    string genome = "";
    ifstream ifs("genome.txt");
    
    if (!ifs) {
        cout << "genome.txt を開けませんでした" << endl;
        return 1;
    }
    ifs >> genome;

    string pattern;
    cout << "検索パターンを入力してください: ";
    cin >> pattern;

    vector<int> positions = naive_search(genome, pattern);
	
    for(int i = 0; i < positions.size(); i++){
        cout << positions[i] << " ";
    }
    cout << endl;

    return 0;
}
