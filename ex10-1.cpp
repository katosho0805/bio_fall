#include "image.hpp" 

typedef unsigned char uchar;

int main(void){
    Image sample("sample.png");
    Image grayscale_image(sample.w, sample.h, 1); //グレイスケール画像の場合はチャネル数を1とする。
  
    for (int y = 0; y < sample.h; y++){
        for (int x = 0; x < sample.w; x++){
            uchar r = sample.GetPixel(y, x, 0); 
            uchar g = sample.GetPixel(y, x, 1); 
            uchar b = sample.GetPixel(y, x, 2); 
            uchar v = (r + g + b)/3;
            grayscale_image.SetPixel(y, x, 0, v);   
        }
    }
    
    grayscale_image.save("grayscale.png");

    return 0;
}
