#include <iostream>
#include <cmath>

using namespace std;

const double e = 2.718281828459;

double f(double x)
{
    return cos(5*x)+cos(7*x);
}

bool perevirka(double mas[])
{
    double eps = 0.0002;
    double step = 0.0001;
    for (int i = 0;i < 100;++i)
        mas[i] += step;
    for (int i = 0;i < 100;++i)
    {
        if (abs(f(mas[i])-f(i*(i+e)) > eps))
            return false;
    }
    return true;
}

bool find_period(double &ans)
{
    double mas_tochok[100];
    for (int i = 0;i < 100; ++i)
        mas_tochok[i] = i*(i+e);
    bool flag = false;
    int counter = 0;
    while(!flag)
    {
        if (perevirka(mas_tochok))
        {
            ans = mas_tochok[0];
            return true;
        }

        if (counter > 1000000)
            break;
        ++counter;
    }
    return false;
}


int main()
{
    double ans = -1;
    if (find_period(ans))
        cout << "Yes " << ans;
    else
        cout << "No";

    return 0;
}
