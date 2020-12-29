#include <iostream>
#include <cmath>

using namespace std;

const long nmax = 40;

void build_arr(long n, long mas[nmax][nmax], long &dlina)
{
    long x,y,step_x = 0,step_y,max_x = n,max_y = n,min_x = 1,min_y = 0;
    if (n%2 == 0)
    {
        x = 1, y = 1, step_y = 1;
    }
    else
    {
        x = n, y = n, ++min_y, ++max_y,step_y = -1;
    }
    for (long i = n*n; i > 0; --i)
    {
        mas[x][y] = i;
        if (x == max_x)
        {
            if (y == max_y)
            {
                step_x = 0;
                step_y = -1;
                ++min_x;
                ++min_y;
            }
            else if (y == min_y)
            {
                step_x = -1;
                step_y = 0;
            }
        }
        else if (x == min_x)
        {
            if (y == min_y)
            {
                step_x = 0;
                step_y = 1;
                --max_x;
                --max_y;
            }
            else if (y == max_y)
            {
                step_x = 1;
                step_y = 0;
            }
        }
        x += step_x;
        y += step_y;
    }
    long step = 1, num = 10;
    while (n*n >= num)
    {
        ++step;
        num *= 10;
    }
    dlina = step;
}

void vivid(long a,long len)
{
    long step = 1, num = 10;
    while (a >= num)
    {
        ++step;
        num *= 10;
    }
    for (long i = 1;i <= len - step; ++i)
        cout << ' ';
    cout << a << ' ';
}

int main()
{
    long n,len;
    long mas[nmax][nmax];
    cin >> n;
    build_arr(n,mas,len);
    for (long i = 1; i <= n; ++i)
    {
        for (long j = 1; j <= n; ++j)
            vivid(mas[i][j],len);
        cout << '\n';
    }
    return 0;
}
