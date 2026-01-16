#include <iostream>
#include<vector>
#include"image.hpp"

using namespace std;

typedef unsigned char uchar;

int main(void){

    Image sample("stap.jpg");
    Image eq_image(sample.w,sample.h,3);

    int N=sample.w*sample.h;

    vector<vector<uchar>>gray_data(sample.h,vector<uchar>(sample.w));
    vactor<int> histogram(256,0);

    for(int y=0;y<sample.h;y++){
        for(int x=0;x<sample.w;x++){
            int r=sample.GetPixel(y,x,0);
            int g=sample.GetPixel(y,x,1);
            int b=sample.GetPixel(y,x,2);
            uchar ave=(uchar)((r+g+b)/3);

            gray_data[y][x];
            histogram[ave]++;
        }
    }

    vector<dounle> cdf(256,0,0);
    long current_sum=0;

    for(int i=0;i<256;i++){
        current_sum+=histogram[i];

        cdf[i]=(double)current_sum/N;
    }

    vector<uchar> map_table(256);
    for(int i=0;i<256;i++){
        map_table[i]=(uchar)(cdf[i]*255.0);
    }

    for(int y=0;y<sample.h;y++){
        for(int x=0;x<sample.w;x++){
            uchar original=gray_data[y][x];
            uchar new_val=map_table[original];

            for(int c=0;c<3;c++){
                eq_image.Setpixel(y,x,c,new_val);
            }
        }
    }
     eq_image.save("equalized_stap.png");
    cout << "equalized_stap.png を保存しました。" << endl;

    return 0;


}

