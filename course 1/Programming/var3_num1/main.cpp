#include <iostream>

using namespace std;

long perev(long n, long p)
{
    long ans = 0, pw = 1;
    while (n > 0)
    {
        ans += n%10*pw;
        n /= 10;
        pw *= p;
    }
    return ans;
}

int main()
{
    long long x, A, B, p, n;
    cin >> p >> n;
    long long n10 = perev(n,p);
    for (long long i = 0;i <= n10; ++i)
    {
        x = i;
        for (long long j = 0; j < x; ++j)
        {
            A = j;
            B = x-j;
            if (A == 0)
            {
                if (x == 1)
                    cout << x << ' ';
            }
            else if (A != 0 && (x*x-B)%A == 0)
            {
                long long pow_p = (x*x-B)/A, pow_p1 = pow_p;
                while (pow_p%p == 0 && pow_p > 0)
                    pow_p /= p;
                if (pow_p == 1 && pow_p1 > B)
                    cout << x << ' ';
            }
        }
    }
    return 0;
}
