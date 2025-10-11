#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>

void newton (const std::function<double(double)>& f,const  std::function<double(double)>& df,
               double x0,double tolerance){
    int count=0;
    double x=x0;

    while(true){
        double fx=f(x);
        double dfx=df(x);
         if (std::abs(dfx) < 1e-15) { // 導関数が0に近すぎる場合
            std::cout << "導関数が0に近づいたため、計算を停止します。発散の可能性があります。" << std::endl;
            return;
        }
    double x_next=x-fx/dfx;
    
    if (std::abs(x_next - x) < tolerance) {
            x = x_next;
            break;
    }

     x=x_next;
     count++;

     if(count>100){
        std::cout << "繰り返し回数が上限に達しました。収束しませんでした。" << std::endl;
             return;
     }
    }

     std::cout << "解: " << std::fixed << std::setprecision(12) << x << std::endl;
    std::cout << "繰り返し回数: " << count + 1 << " 回" << std::endl; // 初回を含む
}

// --- 関数 (1) ---
double f1(double x) { return exp(x) + x - 5.0; }
double df1(double x) { return exp(x) + 1.0; }

// --- 関数 (2) ---
double f2(double x) { return cbrt(x); }
double df2(double x) { return 1.0 / (3.0 * cbrt(x*x)); } // f'(x) = (1/3)x^(-2/3)

int main() {
    double tolerance = 1e-12;

    std::cout << "--- (1) f(x) = e^x + x - 5 ---" << std::endl;
    newton(f1, df1, 0.0, tolerance);
    
    std::cout << "\n--- (2) f(x) = x^(1/3) ---" << std::endl;
    newton(f2, df2, -0.1, tolerance);

    return 0;
}


