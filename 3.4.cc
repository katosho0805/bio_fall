#include <iostream>
#include <cmath>
#include <functional>
#include <iomanip>

void method(const std::function<double(double)>& f, double x0, double x1, double tolerance) {
    int count = 0;
    double x_next;

    while(true){
        double fx0=f(x0);
        double fx1=f(x1);

        if(std::abs(fx1 - fx0) < 1e-15) {
            std::cout << "f(x1)とf(x0)の差が小さすぎるため計算を停止します。" << std::endl;
            return;
        }
        x_next = x1 - fx1 * (x1 - x0) / (fx1 - fx0);
        
        if (std::abs(x_next - x1) < tolerance) {
            x1 = x_next;
            break;
        }
        x0 = x1;
        x1 = x_next;
        count++;

        if (count > 100) {
            std::cout << "繰り返し回数が上限に達しました。" << std::endl;
            return;
        }
    }
    
    std::cout << "解: " << std::fixed << std::setprecision(12) << x1 << std::endl;
    std::cout << "繰り返し回数: " << count + 1 << " 回" << std::endl;
}
    double f1(double x) {
    return exp(x) + x - 5.0;
}

int main() {
    double tolerance = 1e-12;

    std::cout << "--- f(x) = e^x + x - 5 ---" << std::endl;
    method(f1, 0.0, 2.0, tolerance);

    return 0;
}