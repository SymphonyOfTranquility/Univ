#include <iostream>
#include <cmath>

using namespace std;

long num;

long my_pow(long a,long n)
{
    if (n == 0)
        return 1;
    if (n%2 == 1)
        return (my_pow(a,n-1)*a)%num;
    else
    {
        long b = my_pow(a,n/2);
        return (b*b)%num;
    }
}


long gcd(long a,long b)
{
    while (a > 0 && b > 0)
    {
        if (a > b)
            a %= b;
        else
            b %= a;
    }
    return a+b;
}

bool prost(long n)
{
    if (n == 1)
        return false;
    for (long i = 2;i <= sqrt(n); ++i)
        if (n%i == 0)
            return false;
    return true;
}

bool karmaikl(long n)
{
    if (prost(n))
        return false;
    for (long i = 2;i < n; ++i){
        if (gcd(i,n) == 1){
            if (my_pow(i,n-1) != 1)
                return false;
        }
    }
    return true;
}

int main()
{
    cin >> num;
    if (karmaikl(num))
        cout << "YES";
    else
        cout << "NO";
    return 0;
}
