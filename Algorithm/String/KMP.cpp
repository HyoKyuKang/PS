#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
using namespace std;
using ll = long long;
const ll n_ = 2e5 + 10;
ll n, m, tc = 1;
void solve() {
    string s, t;
    getline(cin, s), getline(cin, t);
    n = s.size(), m = t.size();
    vector<int> fail(m + 1), res;
    for (int i = 1, j = 0; i < m; i++) {
        while (j > 0 && t[i] != t[j]) j = fail[j - 1];
        if (t[i] == t[j]) fail[i] = ++j;
    }
    for (int i = 0, j = 0; i < n; i++) {
        while (j > 0 && s[i] != t[j]) j = fail[j - 1];
        if (s[i] == t[j]) {
            if (j == m - 1) {
                res.push_back(i + 1);
                j = fail[j];
            }
            else j++;
        }
    }

    cout << res.size() << endl;
    for (auto nxt : res) cout << nxt - m + 1 << ' ';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    // cin >> tc;
    while (tc--) solve();
};
