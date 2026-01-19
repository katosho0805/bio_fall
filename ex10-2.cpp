#include "image.hpp" 
#include <iostream>

typedef unsigned char uchar;
using namespace std;

int OtsuThreshold(const Image& gray){
    vector<int> hist(256, 0);
    
    for(int y = 0; y < gray.h; y++){
        for(int x = 0; x < gray.w; x++){
            uchar v = gray.GetPixel(y, x, 0); 
            hist[v]++;
        }
    }

    double m_t = 0.0;
    int n = gray.h * gray.w;
    
    for(int i = 0; i < hist.size(); i++){
        m_t += i * (double)hist[i];
    }
    m_t /= n;

    double max_sigma_b2 = -1.0;
    int best_t = 0;
    int w_b = 0;
    double sum_b = 0;

    for(int t = 0; t < 255; t++){ //t=0..254
        w_b += hist[t];
        int w_h = n - w_b;

        sum_b += t * (double)hist[t];

        double m_b = sum_b / w_b;               
        double m_h = (m_t * n - sum_b) / w_h;
	//w_bまたはw_hが0である時の対策が本当は必要だがそこまでは問わない

        double sigma_b2 = w_b*(m_b - m_t)*(m_b - m_t) + w_h*(m_h - m_t)*(m_h - m_t);

        if(sigma_b2 > max_sigma_b2){
            max_sigma_b2 = sigma_b2;
            best_t = t;
        }
    }
    
    return best_t;
}

int main(void){
    Image sample("grayscale.png");
    Image binary_image(sample.w, sample.h, 1); 

    int th = OtsuThreshold(sample);

    for (int y = 0; y < sample.h; y++){
        for (int x = 0; x < sample.w; x++){
            uchar v = sample.GetPixel(y, x, 0); 

            if(v >= th){
                binary_image.SetPixel(y, x, 0, 255);   
            }else{
                binary_image.SetPixel(y, x, 0, 0); 
            }
        }
    }
    
    binary_image.save("binary_otsu.png");

    return 0;
}
