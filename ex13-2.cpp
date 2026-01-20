#include <iostream>
#include <fstream>
#include <string>
#include <vector>

const int BASE = 257;
const int MOD =  1000003;

using namespace std;

bool equals_seq(const string &t, int pos, const string& s){
    for(int i = 0; i < s.size(); i++){
        if(t[pos + i] != s[i]){
            return false;
        }
    }
    return true;
}

vector<int> rabin_karp(const string& genome, const string& pattern){
    vector<int> hit;
    int m = pattern.size();
    int n = genome.size();

    vector<int> pow_base(m, 1);
    for(int k = 1; k < m; k++){
        pow_base[k] = ((long)pow_base[k-1] * BASE) % MOD;
    }
    
    int hash_p = 0;
    for(int i = 0; i < m; i++){
        int term = ((long)pattern[i] * pow_base[m-1-i]) % MOD;
        hash_p = (hash_p + term) % MOD;
    }

    int hash_t = 0;
    for(int i = 0; i < m; i++){
        int term = ((long)genome[i] * pow_base[m-1-i]) % MOD;
        hash_t = (hash_t + term) % MOD;
    }

    int pos = 0;
    while(true){
        if(hash_t == hash_p && equals_seq(genome, pos, pattern)){
            hit.push_back(pos);
        }

        if (pos + m == n) break;

        int left = ((long)genome[pos] * pow_base[m-1]) % MOD;
        hash_t = (hash_t + MOD - left) % MOD;
        hash_t = ((long)hash_t * BASE + genome[pos+m]) % MOD;
        pos++;
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

    vector<int> positions = rabin_karp(genome, pattern);

    for(int i = 0; i < positions.size(); i++){
        cout << positions[i] << " ";
    }
    cout << endl;

    return 0;
}
