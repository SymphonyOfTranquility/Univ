#include <bits/stdc++.h>

using namespace std;

long z_function(string s,long t)
{
    long *z = new long[s.size()];
    for (long i = 0;i < s.length(); ++i)
        z[i] = 0;
    for (long i = t, l = 0, r = 0;i < s.length(); ++i)
    {
        if (i <= r)
            z[i]= min (r-i+1, z[i-l]);
        while (i+z[i] < s.length() && z[i] < t && s[z[i]]== s[i+z[i]])
            ++z[i];
        if (i+z[i]-1 > r)
            l = i, r = i+z[i]-1;
    }
    long  maxs = 0;
    for (long i = t;i < s.length(); ++i)
        maxs = max(maxs,z[i]);
    return maxs;
}

int main()
{
    string s1, s2, t,ans;
    long maxi = 0;
    getline(cin, s1);
    getline(cin, s2);
    for (long i = 0;i < s1.length()-1; ++i)
    {
        t = s1 + s2;
        t.erase(0, i);
        long x = z_function(t,s1.length()-i);
        if (x > maxi)
        {
            ans = t.substr(0,(int)x);
            maxi = x;
        }
    }
    cout << maxi << '\n' << ans;
    return 0;
}
