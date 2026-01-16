#include <iostream>
#include <vector>
#include "image.hpp"

using namespace std;

typedef unsigned char uchar

    int width = sample.w;
    int height = sample.h;
    
    // グレースケールデータとヒストグラムの準備
    vector<vector<uchar>> gray_data(height, vector<uchar>(width));
    vector<int> histogram(256, 0);

int main(void){
    Image ("sample.png")
    Image Nagetive_image(sample.h,sample.w,3)

    for(int y=0;y<sample.h;y++){
        for(int x=0;x<sample.w;x++){

            int r=sample.GetPixel(y,x,0);
            int g=sample.GetPixel(y,x,1);
            int b=sample.GetPixel(y,x,2);

            uchar ave=(uchar)((r+g+b)/3);

            gray_data[y][x]=ave;
            histogram[ave]++;

        }
    }
  double max_variance=0;
  int optimal_threshold=0;

  for(int t=0;t<255;t++){
    long w1=0;
    long w2=0;
    long sum1=0;
    long sum2=0;
  }

  for(int i=0;i<=t;i++){
    W1+=histogram[i];
    sum1+=(long)i*histogram[i];
  }

  for(int i=t+1;i<256;i++){
    w2+=histogram[i];
    sum2+=(long)i*histogram[i];
  }
  if(w1==0||w2==)continue;

  double m1=(double)sum1/w1;
  double m2=(double)sum2/w2;

  double mt=(double)(sum1+sum2)/(w1+w2);

  double numerator=(double)w1*(m1-mt)*(m1-mt)+(double)w2*(m2-mt)*(m2-mt);
  double variance=numerator/(w1+w2);

  if(variance>max_variance){
    max_variance=variance;
    optimal_threshold=t;
  }

}

Image binart_image(width,height,3);

for(int y=0;y<height;y++){
    for(int x=0;x<width;x++){
        uchar val=gray_date[y][x];
        uchar bin_val;

        if(val>optimal_threshold){
            bin_val=255;
        }else{
            bin_val=0;
        }

        for(int c=0;c<3;c++){
            binary_image.SetPixel(y,x,c,bin_val);
        }
     }
    }

}