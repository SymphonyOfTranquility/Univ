#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct pt{
     double x,y;
};

double formula(pt a, pt b, pt p)
{
    return (p.x - a.x)*(b.y - a.y) - (p.y - a.y)*(b.x - a.x);
}

bool proverka(vector<pt> m, long i, long n)
{
     double a = formula(m[i], m[(i-2+n)%n], m[(i-1+n)%n]);
     double b = formula(m[i], m[(i-2+n)%n], m[(i-3+n)%n]);
     if (a == 0 || b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
        return false;
     return true;
}

bool global_prov(vector<pt> m, long i, long n)
{
    if (i == n-1){
        if (m[0].x == m[n-1].x && m[0].y == m[n-1].y)
            return false;
        if (i > 2 && (!proverka(m,i,n) || !proverka(m,0,n) || !proverka(m,1,n)))
            return false;
    }
    if (i > 0 && m[i].x == m[i-1].x && m[i].y == m[i-1].y)
        return false;
    if (i == 2 && formula(m[2], m[0], m[1]) == 0)
        return false;
    if (i >= 3 && !proverka(m,i,n))
        return false;
    return true;
}

long double sum_next(pt a, pt b){
    return ((a.x + b.x)*(a.y - b.y)/2.0);
}

long double plosh(vector<pt> a)
{
    long n = a.size();
    long double s = 0;
    for (long i = 0;i < n; ++i)
        s += sum_next(a[(i+1)%n],a[i]);
    return abs(s);
}

long double len(pt a, pt b){
    return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
}

long double perimetr(vector<pt> a)
{
    long double p = 0;
    long n = a.size();
    for (long i = 0; i < n; ++i)
        p += len(a[i],a[(i+1)%n]);
    return p;
}

int main()
{
    // принято что многоугольник выпуклый
    long n;
    bool err = false;
    vector<pt> mas;
    do{
        if (err)
            cout << "n less than 3\n";
        err = true;
        cin >> n;
    }
    while (n <= 2);
    mas.resize(n);
    for (long i = 0;i < mas.size(); ++i){
        cin >> mas[i].x >> mas[i].y;
        if (!global_prov(mas,i,n)){
            --i;
            cout << "mistake\nanother point, please:\n";
        }
    }
    bool flag = true;
    long double s = plosh(mas);
    long double p = perimetr(mas);
    cout << s << ' ' << p;
    return 0;
}
