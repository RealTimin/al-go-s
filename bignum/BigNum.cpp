#include <iostream>
#include <string>
#include <vector>

using namespace std;

string BigNumAdd(string &n1, string &n2)
{
    // assume that all characters are 'numbers'
    // n[0] is the LSB
    string result;
    int c = 0, sum, s1 = n1.size(), s2 = n2.size();
    int nb = s1 > s2 ? s1 : s2;

    int i = 0;
    while (i < nb)
    {
        if (i >= s1)
            sum = c + (int)(n1[i] - '0');
        else if (i >= s2)
            sum = c + (int)(n2[i] - '0');
        else
            sum = c + (int)(n1[i] - '0') + (int)(n2[i] - '0');
        c = sum >= 10 ? 1 : 0;
        result.push_back((sum % 10) + '0');
        i++;
    }
    if (c)
        result.push_back(c + '0');

    return result;
}

string BigNumSubtract(string &n1, string &n2)
{
    // assume that all characters are 'numbers'
    // assume that n1 is bigger than n2
    // n[0] is the LSB
    string result;
    int c = 0, dif, s1 = n1.size(), s2 = n2.size();
    // vector<int> c(s1, 0);
    int nb = s1 > s2 ? s1 : s2;

    int i = 0, temp;
    while (i < s2)
    {
        if (n1[i] < n2[i])
        {
            // borrow
            temp = i;
            while (n1[++temp] == '0')
                ;
            n1[temp]--;
            while (--temp != i)
                n1[temp] = '9';
            c = 10;
        }
        else
            c = 0;
        // if (i >= s1)
        //     dif = c + (int)(n1[i] - '0');
        // else if (i >= s2)
        //     dif = c + (int)(n2[i] - '0');
        // else
        dif = c + (int)(n1[i] - '0') - (int)(n2[i] - '0');

        result.push_back(dif + '0');
        i++;
    }

    while (i < s1)
        result.push_back(n1[i++]);

    while (--i >= 0 && result[i] == '0')
        result.pop_back();

    return result;
}

string BigNumMultiply(string &n1, string &n2)
{
    // assume that all characters are 'numbers'
    // n[0] is the LSB
    // time complexity: O(n^2)
    string result;
    int c = 0, mul, s1 = n1.size(), s2 = n2.size();
    int sr = result.size(), i, i1, i2;
    for (i1 = 0; i1 < s1; i1++)
    {
        c = 0;
        for (i2 = 0; i2 < s2; i2++)
        {
            i = i1 + i2;
            if (i < sr)
            {
                mul = c + (int)(result[i] - '0') + (int)(n1[i1] - '0') * (int)(n2[i2] - '0');
                result[i] = (mul % 10) + '0';
            }
            else
            {
                mul = c + (int)(n1[i1] - '0') * (int)(n2[i2] - '0');
                result.push_back((mul % 10) + '0');
                sr++;
            }
            c = mul / 10;
        }
        i = i1 + i2;
        while (c != 0)
        {
            if (i < sr)
            {
                mul = c + (int)(result[i] - '0');
                result[i] = (mul % 10) + '0';
            }
            else
            {
                mul = c;
                result.push_back((mul % 10) + '0');
                sr++;
            }
            c = mul / 10;
            i++;
        }
    }
    return result;
}

int main()
{
    string n1 = "00000000000001";
    string n2 = "2";

    string s3;
    s3 = BigNumSubtract(n1, n2);
    for (auto it = s3.rbegin(); it != s3.rend(); it++)
    {
        cout << (*it);
    }

    return 0;
}