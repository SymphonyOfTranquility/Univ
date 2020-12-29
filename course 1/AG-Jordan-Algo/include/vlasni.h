
#include <vector>

#ifndef VLASNI_H
#define VLASNI_H
using namespace std;
const int nmax = 10;

class vlasni
{
private:
    int mat[nmax][nmax];                            //дана матриц€
    int n;                                          //розм≥р матриц≥
    vector<vector<double> > eigenvectors;           //власн≥ вектори
    vector<int> eigenvalues;
    vector<int> polinom_deter();
    void dob_pol_num(vector<int> &a,int x);
    int invertion(const vector<int> &a);
    void sum_pol(vector<int> &a,const vector<int> &b,const vector<int> &permut);
    vector<int> polinomial_roots(vector<int> pol);
    vector<int> divisors(int num);
    void if_devide(vector<int> &pol,vector<int> &ans,int x);
    int substit(vector<int> a,int step);
    void devide(vector<int> &a,int x);
    void sub_cur_row(int matrix[nmax][nmax],bool used[nmax],int row,int col);
    int gcd(int a,int b);
    void res_matrix(int matrix[nmax][nmax]);
    void FSR(int matrix[nmax][nmax],int eigen);
public:
    vlasni();
    void input();
    void vlasni_num();
    void find_eigenvec();
    void output_all();
    virtual ~vlasni();

};

#endif // VLASNI_H
