#include <iostream>
#include <fstream>
#include <math.h>


bool is_left(double x, double y, double A) {
    return isnan(A) ? x < 0 : A * x - y < 0;
}

double distance(double x, double y, double A, double a) {

    return isnan(A) ? abs(x) : abs(A * x - y) / a;
}


int main() {
    std::ifstream file("in.txt");
    double x0, y0, x_l, y_l, x_r, y_r, A, a, d_l = 0, d_r = 0;
    x_l = x_r = y_l = y_r = NAN;
    file >> x0 >> y0;

    A = x0 == 0 ? NAN : y0 / x0;
    a = sqrt(pow(A, 2) + 1);

    double x, y, d;
    while (file >> x >> y) {
        d = distance(x, y, A, a);

        if (is_left(x, y, A)) {
            if (d > d_l) {
                d_l = d;
                x_l = x;
                y_l = y;
            }
        } else {
            if (d > d_r) {
                d_r = d;
                x_r = x;
                y_r = y;
            }
        };

    }


    std::cout << "Leftmost: " << x_l << " " << y_l << '\n';
    std::cout << "Rightmost: " << x_r << " " << y_r << '\n';


}
