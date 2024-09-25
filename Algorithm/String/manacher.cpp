#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using PP = pair<ll, P>;
const ll n_ = 5e5 + 10, inf = (ll)2e9 * (ll)1e9 + 7, mod = 1e9 + 7;
const int mod1 = 1234567891, mod2 = 998244353;
ll n, m, tc = 1, a, b, c, d, sum, x, y, z, base, ans, k;
string S;
ll dif[n_], pre[n_], suf[n_],odd[n_],even[n_];
bool all_same(ll s, ll e) {
    ll ret = dif[e] - dif[s];
    // cout<<s<<' '<<e<<' '<<ret<<endl;
    /*for (int i = s; i <= e; i++) {
        if (S[i] != S[s]) return false;
    }
    */
    return ret == 0;
}
vector<ll> v, manacher;
void make_pal() {
    string s = S;
    n = s.size();
    for (int i = 0; i < n; i++) {
        a = s[i];
        v.push_back(a);
        v.push_back(0);
    }
    v.pop_back();
    n = v.size();
    manacher.resize(n);
    for (ll i = 0, r = 0, p = 0; i < n; i++) {
        if (i <= r) manacher[i] = min(manacher[2 * p - i], r - i);
        while (i - manacher[i] - 1 >= 0 && i + manacher[i] + 1 < n && v[i - manacher[i] - 1] == v[i + manacher[i] + 1]) manacher[i]++;
        if (r < i + manacher[i]) {
            r = i + manacher[i];
            p = i;
        }
    }
}

ll pal(ll s, ll e) {
    // 0->0
    // 1->2
    // 2->4
    ll si = s * 2, ei = e * 2;
    ll mid = (si + ei) / 2;
    ll len;
    if (mid % 2) len = 2 * ((manacher[mid] + 1) / 2);
    else len = 2 * ((manacher[mid] / 2) + 1);
    return len >= e - s + 1;
}
void solve() {
    v.clear(), manacher.clear();
    make_pal();
    //pal함수: pal(s,e)?
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> tc;
    while (tc--) solve();
};
