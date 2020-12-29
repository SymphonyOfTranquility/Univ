#include <iostream>
#include <cmath>

using namespace std;

const double eps = 0.000001;

double f(double x)
{
    return x;
}

double pohidna(double x)
{
    bool flag = true;
    double znach, dx = 1, znach1 = (f(x+dx)-f(x))/dx, step = 0.1;
    while (flag)
    {
        if (step + step/10.0 >= dx)
            step /= 10.0;
        dx -= step;
        znach = (f(x+dx)-f(x))/dx;
        if (abs(znach-znach1) < eps)
            return znach;
        znach1 = znach;
    }
}

double len(double x)
{
    double a = pohidna(x);
    double b = f(x);
    return sqrt(a*a+b*b);
}

double trapecii(double left_gr, double right_gr, int n){
    double alpha = 0.0, delta_x = 0.0;

    double trapecii_integ = (len(left_gr) + len(right_gr)) / 2.0;
    alpha = left_gr;
    delta_x = (right_gr - left_gr) / n;
    for (int k = 1; k < n; ++k){
        alpha += delta_x;
        trapecii_integ += len(alpha);
    }
    return trapecii_integ * delta_x;
}

int main()
{
    double a,b;
    cin >> a >> b;
    cout << trapecii(a, b, 1000);
}
