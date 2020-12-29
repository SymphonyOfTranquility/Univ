#include <bits/stdc++.h>

using namespace std;

const int nmax = 100;

void build(int mas[nmax],int d[nmax], int p[nmax], int ans[nmax], int &m, int k)
{
    int endon = 1, max_i = 1;
    d[0] = 1;
    for (int i = 1;i <= 99; ++i)
        for (int j = i-1;j >= 0; --j)
            if (abs(mas[i]-mas[j]) <= k){
                if (d[j]+1 > d[i]){
                    d[i] = d[j]+1;
                    p[i] = j;
                    if (d[i] > max_i){
                        endon = i;
                        max_i = d[i];
                    }
                }
        }
    m = 0;
    while (endon != -1)
    {
        ans[m] = mas[endon];
        ++m;
        endon = p[endon];
    }

}

int main()
{
    int mas[nmax],d[nmax], p[nmax], ans[nmax];
    for (int i = 0;i < nmax; ++i){
        mas[i] = rand()%100;
        p[i] = -1;
        d[i] = ans[i] = 0;
        cout << mas[i] << ' ';
    }
    cout << '\n';
    int k,m;
    cin >> k;
    build(mas,d,p,ans,m,k);
    cout << m << '\n';
    for (int i = m-1;i >= 0; --i)
        cout << ans[i] << ' ';
    return 0;
}
