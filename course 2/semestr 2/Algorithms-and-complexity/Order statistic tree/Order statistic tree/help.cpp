#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ifstream fin("data.txt");
    ofstream fout("needed.txt");
    string s;
    int counter = 0;
    for (int i = 0;i < 10000; ++i)
    {
        getline(fin, s);
        bool ok = true;
        for (int j = 0;j < s.length(); ++j)
        {
            if (s[j] <= 0 || s[j] > 127)
            {
                ok = false;
                break;
            }
        }
        if (ok)
        {
            ++counter;
            fout << s << '\n';
        }
    }
    cout << counter << '\n';
}
