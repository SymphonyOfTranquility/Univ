#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

const int my_lovely_len = 80;

void my_read(vector<string> &s, vector<int> &m, int &n)
{
    string a;
    while (getline(cin,a))
    {
        s.push_back(a);
        m.push_back(0);
        for (int i = 0;i < s[n].length(); ++i)
            if (s[n][i] == ' ')
            {
                ++m[n];
                int j = i+1;
                while (s[n][j] == ' ')
                    s[n].erase(j,1);
            }
        ++n;
    }
}

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    setlocale(LC_ALL,"Russian");
    vector<string> s;
    vector<int> prob;
    int n = 0;
    my_read(s,prob,n);
    for (int i = 0;i < my_lovely_len; ++i)
        cout << 0;
    cout << '\n';
    for (int i = 0;i < n; ++i)
    {
        if (s[i].length() == my_lovely_len || s[i].length() == 0 || prob[i] == 0)
            continue;
        bool flag = false;
        int counter = 0;
        while (!flag){
            cout << s[i] << '\n';
            if (s[i].length() > my_lovely_len)
            {
                while (s[i].length() > my_lovely_len)
                {
                    int j = s[i].length()-1;
                    while (s[i][j] != ' ' && j >= 0)
                        --j;
                    if(j < 0){
                        flag = true;
                        break;
                    }
                    string temp_s = s[i].substr(j+1);
                    --prob[i];
                    while (s[i][j] == ' ' && j >= 0)
                        --j;
                    s[i].erase(j+1);
                    if (i+1 == n)
                    {
                        s.push_back(temp_s);
                        prob.push_back(0);
                        ++n;
                    }
                    else if (s[i+1].length() == 0)
                        s[i+1] = temp_s;
                    else {
                        s[i+1] = temp_s + ' ' + s[i+1];
                        ++prob[i+1];
                    }
                }
            }
            else if (s[i].length() < my_lovely_len)
            {
                if (counter >= 3 && my_lovely_len - s[i].length() < prob[i])
                {
                    int prob_count = my_lovely_len - s[i].length();
                    for (int j = 0;j < s[i].length() && prob_count > 0; ++j)
                        if (s[i][j] == ' ')
                        {
                            --prob_count;
                            while (s[i][j] == ' ')
                                ++j;
                            s[i].insert(j-1," ");
                        }
                    flag = true;
                    continue;
                }
                ++counter;
                for (int j = 0; j < s[i].length(); ++j)
                    if (s[i][j] == ' ')
                    {
                        while (s[i][j] == ' ')
                            ++j;
                        s[i].insert(j-1," ");
                    }
            }
            else flag = true;
        }
    }
    for (int i = 0;i < n; ++i)
        cout << s[i] << "        " << prob[i] << '\n';
    cout << (char) 'å';
}





























































/*#include <iostream>
#include <cstdio>

using namespace std;

const long nmax = 10000, my_lovely_length = 150;

int main()
{
    freopen("input.txt","r",stdin);
    freopen("output.txt","w",stdout);
    vector<string> s;
    vector<long> mas;
    string a;
    long n = 0;
    while (getline(cin,a))
    {
        cout << a.length() << '\n';
        s.push_back(0);
        mas.push_back(0);
        for (long i = 0;i < s[n].length(); ++i)
            if (s[n][i] == ' ')
            {
                mas[n]++;
                long j = i+1;
                while (s[n][j] == ' ' && j < s[n].length()) ++j;
                if (j-i > 1 || j == s[n].length())
                {
                    if (j == s[n].length())
                        s[n].erase(i,j-i);
                    else
                        s[n].erase(i+1,j-i);
                }
            }
        ++n;
    }
    for (long i = 0; i < n; ++i)
        cout << mas[i] << '\n';
    cout << '\n';
    for (long i = 0; i < n; ++i)
    {
        if (s[i].length() == my_lovely_length || s[i].length() == 0)
            continue;
        while (s[i].length() > my_lovely_length)
        {
            long j = s[i].length() - 1;
            while (s[i][j] != ' ' && j > 0)
                --j;
            string s1 = s[i].substr(j+1);
            if (i+1 < n)
                s1 = s1 + ' ';
            else
            {
                ++n;
                s[i+1] = "";
            }
            s[i+1] = s1 + s[i+1];
            while (s[i][j] == ' ' && j > 0)
                --j;
            ++j;
            s[i].erase(j);
       //     cout << "#########" << s[i] << '\n';
        }

        bool flag = false;
        while (!flag)
        {
            if (s[i].length() != my_lovely_length)
            {
                for (long j = 1; j < s[i].length(); ++j)
                {
                    if (s[i][j] == ' ')
                    {
                        while (s[i][j] == ' ')
                            ++j;
                        --j;
                        s[i].insert(j," ");
                        ++j;
                    }
                }
            }
            else flag = true;
            while (s[i].length() > my_lovely_length)
            {
                long j = s[i].length() - 1;
                while (s[i][j] != ' '&& j > 0)
                    --j;
                string s1 = s[i].substr(j+1);
                if (i+1 < n)
                    s1 = s1 + ' ';
                else
                {
                    ++n;
                    s[i+1] = "";
                }
                s[i+1] = s1 + s[i+1];
                while (s[i][j] == ' ')
                    --j;
                ++j;
                s[i].erase(j);
            }
        }
        cout << s[i] << '\n';
    }
    return 0;
}
*/
