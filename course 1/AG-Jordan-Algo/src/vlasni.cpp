#include "vlasni.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

vlasni::vlasni()
{
    n = 0;
    eigenvalues.clear();
    eigenvectors.clear();
    for (int i = 0; i < nmax; ++i)
    {
        for (int j = 0; j < nmax; ++j)
            mat[i][j] = 0;
    }
    //ctor
}

bool ok(vector<int> a)
{
    for (int i = 0; i < a.size(); ++i)
        if (a[i] != a.size()-i-1)
            return false;
    return true;
}

void vlasni::dob_pol_num(vector<int> &a,int x)
{
    for (int j = 0; j < a.size(); ++j)
        a[j] *= x;
}

int vlasni::invertion(const vector<int> &a)
{
    int counter = 0;
    for (int i = 0; i < a.size(); ++i)
    {
        for (int j = i + 1; j < a.size(); ++j)
            if (a[i] > a[j])
                ++counter;
    }
    return counter;
}

void vlasni::sum_pol(vector<int> &a,const vector<int> &b,const vector<int> &permut)
{
    int counter = invertion(permut);
    if (counter%2 == 0)
    {
        for (int i = 0; i < b.size(); ++i)
            a[i] += b[i];
    }
    else
    {
        for (int i = 0; i < b.size(); ++i)
            a[i] -= b[i];
    }

}

vector<int> vlasni::polinom_deter()
{
    vector<int> permut,pol;
    pol.resize(n+1);
    for (int i = 0; i < n; ++i)
        permut.push_back(i);
    bool flag = false;
    do
    {
        if (flag)
            next_permutation(permut.begin(),permut.end());
        else
            flag = true;
        vector<int> temp_pol;
        temp_pol.push_back(1);
        for (int i = 0; i < n; ++i)
        {
            if (i != permut[i])
                dob_pol_num(temp_pol,mat[i][permut[i]]);
            else
            {
                vector<int> tmp = temp_pol;
                dob_pol_num(temp_pol,mat[i][permut[i]]);
                temp_pol.push_back(-tmp[tmp.size()-1]);
                for (int i = 1; i < tmp.size(); ++i)
                    temp_pol[i] -= tmp[i-1];
            }
        }
        sum_pol(pol,temp_pol,permut);
    }
    while (!ok(permut));
    cout << "Polynomial for determinant: ";
    for (int i = 0;i < pol.size(); ++i)
        cout << pol[i] << ' ';
    cout << '\n';
    return pol;
}

vector<int> vlasni::divisors(int num)
{
    num = abs(num);
    vector<int> ans;
    ans.clear();
    for (int i = 1; i*i <= num; ++i)
    {
        if (num%i == 0)
        {
            ans.push_back(i);
            if (i*i != num)
                ans.push_back(num/i);
        }
    }
    return ans;
}

int vlasni::substit(vector<int> a,int step)
{
    int ans = 0,x = 1;
    for (int i = 0; i < a.size(); ++i)
    {
        ans += a[i]*x;
        x *= step;
    }
    return ans;
}

void vlasni::devide(vector<int> &a,int x)
{
    x = -x;
    vector<int> res,help;
    res.resize(a.size()-1,0);
    for (int i = a.size()-1; i > 0; --i)
    {
        res[i-1] = a[i];
        a[i-1] -= x*a[i];
    }
    a = res;
}

void vlasni::if_devide(vector<int> &pol,vector<int> &ans,int x)
{
    while (substit(pol,x) == 0 && ans.size() != n)
    {
        devide(pol,x);
        ans.push_back(x);
    }
}

vector<int> vlasni::polinomial_roots(vector<int> pol)
{
    vector<int> ans;
    ans.clear();
    if_devide(pol,ans,0);
    vector<int> int_roots = divisors(pol[0]);

    for (int i = 0; i < int_roots.size() && ans.size() != n; ++i)
    {
        if_devide(pol,ans,int_roots[i]);
        if_devide(pol,ans,-int_roots[i]);
    }
    return ans;
}

void vlasni::vlasni_num()
{
    vector<int> polin;
    polin = polinom_deter();
    eigenvalues = polinomial_roots(polin);
}

void vlasni::input()
{
    cout << "Enter the size of square matrix: ";
    cin >> n;
    cout << "Enter matrix size of: " << n << "x" << n << "\n";
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            cin >> mat[i][j];
}

int vlasni::gcd(int a,int b)
{
    a = abs(a);
    b = abs(b);
    while (a > 0 && b > 0)
    {
        if (a > b)
            a %= b;
        else
            b %= a;
    }
    return a+b;
}

void vlasni::sub_cur_row(int matrix[nmax][nmax],bool used[nmax],int row,int col)
{
    for (int i = 0; i < n; ++i)
    {
        if (i != row)
        {
            if (matrix[i][col] != 0)
            {
                int a = matrix[i][col], b = matrix[row][col],gcd_el = gcd(a,b);
                int nsk = a/gcd_el*b;
                a = nsk/a;
                b = nsk/b;
                for (int j = 0; j < n; ++j)
                    matrix[i][j] = matrix[i][j]*a-matrix[row][j]*b;
            }
        }
    }
    if (col != row)
    {
        for (int j = 0; j < n; ++j)
            swap(matrix[col][j],matrix[row][j]);
    }
    used[col] = true;
}


void vlasni::res_matrix(int matrix[nmax][nmax])
{
    bool used[nmax];
    for (int i = 0;i < nmax; ++i)
        used[nmax] = false;
    for (int j = 0; j < n; ++j)
    {
        for (int i = 0; i < n; ++i)
            if (!used[i] && matrix[i][j] != 0){
                sub_cur_row(matrix,used,i,j);
            }
    }
    for (int i = 0; i < n; ++i)
    {
        bool flag = false;
        int del = 1,gcd_el;
        for (int j = 0; j < n; ++j)
            if (matrix[i][j] != 0)
            {
                if (!flag)
                {
                    if (matrix[i][j] < 0)
                        del *= -1;
                    gcd_el = abs(matrix[i][j]);
                    flag = true;
                }
                else
                {
                    gcd_el = gcd(gcd_el,matrix[i][j]);
                }
            }
        del *= gcd_el;
        for (int j = 0; j < n; ++j)
            matrix[i][j] /= del;
    }
}

void vlasni::FSR(int matrix[nmax][nmax],int eigen)
{
                    cout << eigen << '\n';
                    cout << "Before :\n";
                    for (int j = 0;j < n; ++j)
                    {
                        for (int i = 0;i < n; ++i)
                            cout << matrix[j][i] << ' ';
                        cout << '\n';
                    }
                    cout << '\n';

    res_matrix(matrix);

                    cout << "After :\n";
                    for (int j = 0;j < n; ++j)
                    {
                        for (int i = 0;i < n; ++i)
                            cout << matrix[j][i] << ' ';
                        cout << '\n';
                    }
                    cout << '\n';
    vector<int> temp_x;
    for (int j = 0;j < n; ++j)
    {
        bool flag = false;
        for (int i = 0;i < n; ++i)
            if (matrix[i][j] != 0)
            {
                flag = true;
                break;
            }
        if (!flag)
            temp_x.push_back(j);
    }
    for (int i = 0;i < n; ++i)
    {
        for (int j = i+1;j < n; ++j)
        {
            if (matrix[i][j] != 0)
            {
                bool flag = false;
                for (int k = 0;k < temp_x.size(); ++k)
                    if (temp_x[k] == j)
                    {
                        flag = true;
                        break;
                    }
                if (!flag)
                    temp_x.push_back(j);
            }
        }
    }
    vector<double> ans;
    for (int k = 0;k < temp_x.size(); ++k)
    {
        ans.clear();
        ans.resize(n);
        for (int i = 0;i < temp_x.size(); ++i)
            ans[temp_x[i]] = 0;
        ans[temp_x[k]] = 1;
        for (int i = 0;i < temp_x[k]; ++i)
        {
            if (matrix[i][temp_x[k]] != 0 && matrix[i][i] != 0)
            {
                ans[i] = -(double)matrix[i][temp_x[k]]/(double)matrix[i][i];
            }
            else ans[i] = 0;
        }
        ans.push_back(eigen);
        eigenvectors.push_back(ans);
    }
}

void vlasni::find_eigenvec()
{
    int new_mat[nmax][nmax];
    for (int eig = 0; eig < eigenvalues.size(); ++eig)
    {
        if (eig+1 < eigenvalues.size() && eigenvalues[eig] == eigenvalues[eig+1])
            continue;
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
                new_mat[i][j] = mat[i][j];
            new_mat[i][i] -= eigenvalues[eig];
        }

        FSR(new_mat,eigenvalues[eig]);
    }
}



void vlasni::output_all()
{
    cout << "Eigenvalues of matrix: ";
    for (int i = 0; i < eigenvalues.size(); ++i)
        cout << eigenvalues[i] << ' ';
    cout << ";\n";

    cout << "All eigenvectors: \n";
    for (int i = 0;i < eigenvectors.size(); ++i)
    {
        cout << i+1  << ": ";
        for (int j = 0;j < eigenvectors[i].size()-1; ++j)
            cout << eigenvectors[i][j] << ' ';
        cout << "    is for eigenvalue " << eigenvectors[i][eigenvectors[i].size()-1];
        cout << '\n';
    }
}





vlasni::~vlasni()
{
    //dtor
}

