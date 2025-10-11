#include<iostream>
#include<cmath>
#include<iomanip>
#include<functional>

void method(const std::function<double(double)>& f,double a, double b,int count){
    if(f(a)*f(b)>=0){
        std::cout<<"解は指定された区間[a,b]に存在しないか，複数存在する"<<std::endl;
        return;
    }

    count=0;
    double c;

    while((b-a)>=count){
        c=a+(b-a)/2.0;

        if(f(c)==0.0){
            break;
        }else if(f(a)*f(c)<0){
             b=c;
        }else{
            a=c;
        }
        count++;
    }
    
    std::cout << "解: " << std::fixed << std::setprecision(12) << a + (b - a) / 2.0 << std::endl;
    std::cout << "繰り返し回数: " << count << " 回" << std::endl;
}

double f1(double x){
    return exp(x)+x-5.0;
}
double f2 (double x){
    return cbrt(x);//xの３分の１乗
}
int main (){
   double count=1e-12;
   std::cout << "--- (1) f(x) = e^x + x - 5 ---" << std::endl;
    method(f1, 0.0, 2.0, count);
    
    std::cout << "\n--- (2) f(x) = x^(1/3) ---" << std::endl;
    method(f2, -0.1, 0.2, count);

    return 0;
}
