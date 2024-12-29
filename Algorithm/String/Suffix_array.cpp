//9248 AC code

#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
using namespace std;
using ll = long long;
const ll n_ = 3e6 + 100;
const int nmax = 9e6 + 1;

class LCP {
   public:
    string s;
    int n, d, lim;
    vector<int> group, sa, num, cnt, temp, rev_sa, lcp;
    bool cmp(ll x, ll y) {
        if (group[x] != group[y]) return group[x] < group[y];
        x += d, y += d;
        if (x < n && y < n) return group[x] < group[y];
        return x > y;
    }
    void make_lcp() {
        int n, m;
        n = s.size();
        m = lim;
        for (d = 1; d < n; d *= 2) {
            for (int i = 0; i <= m; i++) num[i] = 0;
            for (int i = 0; i < n; i++) num[group[i + d]]++;
            for (int i = 1; i < m; i++) num[i] += num[i - 1];
            for (int i = n - 1; i >= 0; i--) cnt[--num[group[i + d]]] = i;

            for (int i = 0; i <= m; i++) num[i] = 0;
            for (int i = 0; i < n; i++) num[group[i]]++;
            for (int i = 1; i < m; i++) num[i] += num[i - 1];
            for (int i = n - 1; i >= 0; i--) sa[--num[group[cnt[i]]]] = cnt[i];

            temp[0] = 1;
            for (int i = 1; i < n; i++) temp[i] = temp[i - 1] + cmp(sa[i - 1], sa[i]);
            for (int i = 0; i < n; i++) group[sa[i]] = temp[i];
            if (temp[n - 1] == n) break;
        }
        for (int i = 0; i < n; i++) rev_sa[sa[i]] = i;
        ll len = 0;
        for (int i = 0; i < n; i++) {
            if (!rev_sa[i]) continue;
            for (int j = sa[rev_sa[i] - 1]; s[i + len] == s[j + len]; len++);
            lcp[rev_sa[i]] = len;
            len--;
            if (len < 0) len++;
        }

        /*디버깅용 코드
        for (int i = 0; i < n; i++) {
            cout << s.substr(sa[i], n - sa[i]);
            cout << endl;
        }
        */
    }
    LCP(string S) {
        s = S;
        n = s.size();
        lim = max(27, n + 1);  // 글자의 개수 counting sort를 위해 필요
        group.resize(lim*2 + 1), sa.resize(lim*2 + 1), num.resize(lim*2 + 1), cnt.resize(lim*2 + 1);
        temp.resize(lim*2 + 1), rev_sa.resize(lim*2 + 1), lcp.resize(lim*2 + 1);
        for (int i = 0; i < n; i++) {
            group[i] = s[i] - 'a' + 1;
            sa[i] = i;
        }
        make_lcp();
    }
};
void solve() {
    string s;
    cin >> s;
    LCP L(s);
    for (int i = 0; i < s.size(); i++) cout << L.sa[i] + 1 << ' ';
    cout << '\n';
    cout << "x ";
    for (int i = 1; i < s.size(); i++) cout << L.lcp[i] << ' ';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    ll tc = 1;
    // cin >> tc;
    while (tc--) solve();
};
