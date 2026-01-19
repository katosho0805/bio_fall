#include<image.hpp>

typedef  unsigned char uchar;
using namespace std;

int decide_num (const image&gray){
     vector<int> hist(256, 0);//ヒストグラム

     for(int y=0;y<gray.h;y++){
        for(int x=0;x<gray.w;x++){
            uchar v= gray.getPixel(y,x,0);
            hist++;
        }
     }

     double m_t=0.0;//全体の平均
     int n=gray.w*gray.h;//全画素数

     for(int i=0;i<n;i++){
        m_t=i*(double)hist[i]; //(画素の明るさ)*(その明るさを持つ個数)
     }
     m_t/=n;

     double max_sigma_b2=-1.0;//最大分散
     int best_t=0;//ベスト閾値
     int w_b=0;//黒クラスの画素数
     double sum_b=0;//黒クラスに含まれる画素の 画素値（明るさ）の合計

     for(int t=0;t<255;t++){
        w_b+=hist[t];//hist[t]は明るさがtである画素数
        int w_h=n-w_b;//w_hは全画素数から黒を引いたもの

        sum_b+=t*(double)hist[t];//黒の(画素の明るさ)*(その明るさを持つ個数)

        double m_b=sum_b/w_b;//黒クラスの平均画素値
        double m_h=(m_t*n-sum_b)/w_h;//白クラスの平均画素数

        double sigma_b2=w_b*(m_b-m_t)*(m_b-m_t)+w_h*(m_h-m_t)*(m_h-m_t);//クラス間分散

        if(sigma_b2>max_sigma_b2){
            max_sigma_b2=sigma_b2;
            best_t=t;
        }
     }
  return best_t;
}

int main(void){
    Image sample.("grayscale.png");
    Image binary_image(sample.w, sample.h, 1); 

    int th= int decide_num(sample);

    for(int y=0;y<sample.h;y++){
        for(int x=0;x<sample.w;x++){
            uchar v=sample.getPixel(y,x,0);

            if(v>=th){
                binary_image.SetPixel(y, x, 0, 255);   
            }else{
                binary_image.SetPixel(y, x, 0, 0); 
            }
          }
        }

         binary_image.save("binary_otsu.png");

    return 0;
    }

