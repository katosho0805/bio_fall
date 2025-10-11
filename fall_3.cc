#include<iostream>
#include<cmath>
#include<iomanip>

int main (void){
    float a=1.0f;
    float b=10000.0f;
    float c=1.0f;

    float D=sqrt(b*b-4*a*c);
    float x1=(-b+D)/(2*a);
    float x2=(-b-D)/(2*a);//x1,x2は通常の誤差を気にしないときの解

    float good_answer1,good_answer2;

    if(b>=0){
      good_answer2=(-b-D)/(2*a);//b>0の時-b＋Dの時に桁落ちの可能性がある。
      good_answer1=c/(a*good_answer2);
     } else{
        good_answer1=(-b+D)/(2*a);
        good_answer2=c/(a*good_answer1);
       }

    std::cout << "--- 桁落ち配慮なし ---" << std::endl;
    std::cout << "x1 = " << x1 << std::endl;
    std::cout << "x2 = " << x2 << std::endl;
    std::cout << std::endl;
    
    std::cout << "--- 桁落ち配慮あり ---" << std::endl;
    std::cout << "x1 = " << good_answer1 << std::endl;
    std::cout << "x2 = " << good_answer2<< std::endl;

    return 0;
}
