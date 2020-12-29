#include <iostream>

using namespace std;

string mreverse(string a)
{
    string s = "";
    for (long i = a.length()-1;i >= 0; --i)
        s += a[i];
    return s;
}

string transl(long long a,long long b)
{
    string res = "";
    while (a > 0)
    {
        res += a%b + '0';
        a /= b;
    }
    res = mreverse(res);
    return res;
}

int main()
{
    long long num, basis;
    string ans;
    cin >> num >> basis;
    ans = transl(num,basis);
    cout << ans;
    return 0;
}
