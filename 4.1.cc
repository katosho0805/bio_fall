#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using namespace std;

const int cell_num = 401;
const int time_step = 200;

vector<int> getRuleSet(int ruleNumber) {
    // 8個の要素を持つvectorを、すべて0で初期化
    vector<int> rules(8, 0);
    int tempNum = ruleNumber;

    // 8回（8ビット分）繰り返す
    for (int i = 0; i < 8; ++i) {
        rules[i] = tempNum % 2;
        tempNum = tempNum / 2;
    }
    return rules;
}

// 現在のセルの状態をファイルに出力する
void printStateToFile(const vector<int>& cells, ofstream& outfile) {
    for (int cell_state : cells) {
        if (cell_state == 1) {
            outfile << "*";
        }
        else {
            outfile << " ";
        }
    }
    outfile << endl;
}

int main() {

    int ruleNumber;
    cout << "演習課題1: 1次元セル・オートマトン" << endl;
    cout << "ルール番号 (0-255) を入力してください: ";
    cin >> ruleNumber;

    if (ruleNumber < 0 || ruleNumber > 255) {
        cerr << "エラー: ルール番号は0から255の間で入力してください。" << endl;
        return 1; // エラー終了
    }

    // ルール配列を取得
    vector<int> ruleSet = getRuleSet(ruleNumber);

    // ----- 初期状態の設定 -----
    vector<int> currentState(cell_num, 0);
    vector<int> nextState(cell_num, 0);
    
    currentState[cell_num / 2] = 1; // 中央を1に

    // ----- ファイル出力の準備 -----
    string filename = "rule" + to_string(ruleNumber) + ".txt";
    ofstream outfile(filename);

    if (!outfile) {
        cerr << "エラー: ファイル " << filename << " を開けません。" << endl;
        return 1; // エラー終了
    }
    cout << filename << " に結果を出力します..." << endl;

    for (int t = 0; t <= time_step; ++t) {
        // 1. 現在の状態を出力
        printStateToFile(currentState, outfile);

        // 2. 次の状態を計算
        for (int i = 0; i < cell_num; ++i) {
            int left;
            if (i == 0) {
                left = 0;
            }
            else {
                left = currentState[i - 1];
            }
            int middle = currentState[i];
            int right;
            
            if (i == cell_num - 1) {
                right = 0; // 最後のセルの右隣は 0 とする
            }
            else {
                right = currentState[i + 1];
            }

            int patternIndex = (left << 2) | (middle << 1) | right;

            nextState[i] = ruleSet[patternIndex];
        }

        // 3. 状態を更新
        currentState = nextState;
    }

    outfile.close();
    cout << "演習1のシミュレーションが完了しました。" << endl;
    
    return 0; 
}