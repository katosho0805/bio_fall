#include <iostream>
#include "image.hpp"

using namespace std;

typedef unsigned char uchar;

int main(void) {
    Image sample("sample.jpg");
    
    Image gray_image(sample.w, sample.h, 3);

    for (int y = 0; y < sample.h; y++) {
        for (int x = 0; x < sample.w; x++) {
            int r = sample.GetPixel(y, x, 0);
            int g = sample.GetPixel(y, x, 1);
            int b = sample.GetPixel(y, x, 2);

            uchar avg = (uchar)((r + g + b) / 3);

            for(int c = 0; c < 3; c++) {
                gray_image.SetPixel(y, x, c, avg);//すべてのチャネルに同じ平均値をセットしてグレーにする
            }
        }
    }

    gray_image.save("grayscale.png");
    cout << "grayscale.png を保存しました。" << endl;

    return 0;
}