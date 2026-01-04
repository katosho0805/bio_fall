#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

// ファイル読み込み
string LoadGenome(string filename) {
    ifstream ifs(filename);
    if (!ifs) {
        cerr << "Error: Cannot open " << filename << endl;
        exit(1);
    }
    string seq, line;

    while (getline(ifs, line)) {
        // ヘッダ行（>で始まる）は無視する場合
        if (line.empty() || line[0] == '>') continue;
        seq += line;
    }
    return seq;
}

bool IsMatch(const string& T, const string& S, int start_index) {
    int n = T.size();
    int m = S.size();

    // 残りの長さが足りない場合
    if (start_index + m > n) return false;

    for (int i = 0; i < m; ++i) {
        if (T[start_index + i] != S[i]) {
            return false; // 不一致が見つかった時点で終了
        }
    }
    return true; // 最後まで一致
}

int main() {
    string filename = "genome.txt";
    cout << "Loading " << filename << "..." << endl;
    string T = LoadGenome(filename);
    cout << "Text length: " << T.size() << endl;

    string S;
    cout << "Input pattern S: ";
    cin >> S;

    cout << "Searching..." << endl;
    vector<int> positions;

    for (int i = 0; i < T.size(); ++i) {
        if (IsMatch(T, S, i)) {
            positions.push_back(i);
        }
    }

    if (positions.empty()) {
        cout << "Pattern not found." << endl;
    } else {
        cout << "Found at: ";
        for (int pos : positions) {
            cout << pos << " ";
        }
        cout << endl;
        cout << "Total count: " << positions.size() << endl;
    }

    return 0;
}