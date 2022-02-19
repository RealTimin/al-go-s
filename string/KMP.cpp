#include <iostream>
#include <string>
#include <vector>
using namespace std;

vector<int> getPi(const string &p) {
    int m = p.size();
    vector<int> pi(m, 0);
    int i, j = 0;
    for (i = 1; i < m; i++) {
        while (j > 0 && p[i] != p[j]) {
            j = pi[j - 1];
        }

        if (p[i] == p[j]) {
            pi[i] = ++j;
        }
    }
    return pi;
}

vector<int> getKMP(const string &s, const string &p) {
    vector<int> ans;
    int n = s.size(), m = p.size();
    int i = 0, j = 0;
    vector<int> pi = getPi(p);
    for (i = 0; i < n; i++) {
        while (j > 0 && s[i] != p[j]) {
            j = pi[j - 1];
        }

        if (s[i] == p[j]) {
            if (j == m - 1) {
                ans.push_back(i - m + 1);
                j = pi[j];
            } else {
                j++;
            }
        }
    }
    return ans;
}

int main() {
    string s, p;
    getline(cin, s);
    getline(cin, p);
    vector<int> ans = getKMP(s, p);
    cout << ans.size() << endl;
    for (auto it = ans.begin(); it != ans.end(); it++) {
        cout << (*it) + 1 << ' ';
    }

    return 0;
}