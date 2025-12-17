#include <iostream>
#include <vector>
#include <cmath>   // round
#include "image.hpp"

using namespace std;

typedef unsigned char uchar;

int main(void) {
    Image sample("sample.jpg");
    
    int width = sample.w;
    int height = sample.h;
    vector<vector<uchar>> gray_data(height, vector<uchar>(width));
    vector<int> histogram(256, 0);

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            int r = sample.GetPixel(y, x, 0);
            int g = sample.GetPixel(y, x, 1);
            int b = sample.GetPixel(y, x, 2);
            
            uchar avg = (uchar)((r + g + b) / 3);
            
            gray_data[y][x] = avg;
            histogram[avg]++;
        }
    }

    double max_variance = -1.0;
    int optimal_threshold = 0;

    for (int t = 0; t < 256; t++) {
        long w1 = 0;
        long w2 = 0; 
        long sum1 = 0; // クラス1の画素値合計
        long sum2 = 0; // クラス2の画素値合計

        for (int i = 0; i <= t; i++) {
            w1 += histogram[i];
            sum1 += (long)i * histogram[i];
        }
        
        for (int i = t + 1; i < 256; i++) {
            w2 += histogram[i];
            sum2 += (long)i * histogram[i];
        }

        if (w1 == 0 || w2 == 0) continue;// 画素数が0のときは計算できない

        double m1 = (double)sum1 / w1;
        double m2 = (double)sum2 / w2;
        
        double mt = (double)(sum1 + sum2) / (w1 + w2);
        
        double term1 = (double)w1 * (m1 - mt) * (m1 - mt);
        double term2 = (double)w2 * (m2 - mt) * (m2 - mt);
        double variance = term1 + term2;        // クラス間分散の計算 

        if (variance > max_variance) {
            max_variance = variance;
            optimal_threshold = t;
        }
    }

    cout << "決定された閾値: " << optimal_threshold << endl;

    Image binary_image(width, height, 3);
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            uchar val = gray_data[y][x];
            uchar bin_val;
            
            if (val > optimal_threshold) {
                bin_val = 255; // 白
            } else {
                bin_val = 0;   // 黒
            }

            for(int c = 0; c < 3; c++) {
                binary_image.SetPixel(y, x, c, bin_val);
            }
        }
    }

    binary_image.save("binary_otsu.png");
    cout << "binary_otsu.png を保存しました。" << endl;

    return 0;
}