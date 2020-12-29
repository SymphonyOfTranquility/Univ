#include <iostream>
#include <cmath>

using namespace std;

long double find_ans(long double e)
{
    long double sum = 0, k = 1, znak = -1, fact = 1, x;
    bool flag = true;
    while (flag)
    {
        fact /= k;
        x = k*k*(znak)*fact;
        cout << x << '\n';
        if (abs(x) < e)
            flag = false;
        else{
            sum += x;
            ++k;
            znak *= -1;
        }
    }
    return sum;
}

int main()
{
    long double e;
    cin >> e;
    cout << find_ans(e);
    return 0;
}
