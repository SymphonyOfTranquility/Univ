#include <iostream>

using namespace std;


const double inf = 1000000000;
const int nmax = 10000;

double not_rec_solve(int n)
{
    double f[nmax];
    f[1] = 1;
    for (int i = 2;i <= n; ++i)
    {
        double mini = inf;
        for (int j = 1;j <= i/2; ++j){
            mini = min(mini,f[j]+f[i-j]);
        }
        f[i] = mini/4.0;
    }
    return f[n];
}

double rec_mas[nmax];

double rec_solve(int n)
{
    if (n == 1)
    {
        rec_mas[1] = 1;
        return 1;
    }
    if (rec_mas[n] == 0)
    {
        double mini = inf;
        for (int i = 1;i < n; ++i)
            mini = min(mini,rec_solve(i)+rec_solve(n-i));
        rec_mas[n] = mini/4;
        return mini/4;
    }
    else return rec_mas[n];
}

int main()
{
    int n;
    cin >> n;
    cout << not_rec_solve(n) << '\n';
    cout << rec_solve(n) << '\n';
    return 0;
}
