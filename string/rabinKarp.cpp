#include <iostream>
#include <string>
#include <vector>
using namespace std;

int getHash(string &p, int s, int e) {
    int h = 0;
    e = e < p.size() ? e : p.size();
    s = s >= 0 ? s : 0;
    s = s < e ? s : e;
    e = s < e ? e : s;
    for (int i = s; i <= e; i++) {
        h *= 2;
        h += p[i];
    }
    return h;
}

vector<int> rabinKarp(string &s, string &p) {
    int n = s.size(), m = p.size();
    int hp = getHash(p, 0, m - 1);
    int x = (1 << (m - 1));
    vector<int> result;
    if (m > n)
        return result;
    int hs = getHash(s, 0, m - 1);
    hs -= s[m - 1];
    int i = 0, j;
    bool isSame;
    for (i = 0; i <= n - m; i++) {
        hs += s[i + m - 1];
        if (hs == hp) {
            isSame = true;
            for (j = 0; j < m; j++) {
                if (s[i + j] != p[j])
                    isSame = false;
            }
            if (isSame)
                result.push_back(i);
        }
        hs -= s[i] * x;
        hs *= 2;
    }
    return result;
}

int main() {
    string s, p;
    cin >> s >> p;
    vector<int> result = rabinKarp(s, p);
    cout << result.size();

    return 0;
}