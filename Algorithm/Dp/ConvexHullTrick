#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
using namespace std;
using ll = long long;
const ll nmax = 202020;

class CHT {
private:
    using P = pair<ll, ll>;

public:
    vector<P> st;
    ll now = 0;
    double cross(ll x, ll y) { return (double)(st[y].second - st[x].second) / (st[x].first - st[y].first); }

    void insert(ll x, ll y) {
        ll sz = st.size();
        st.push_back({x, y});
        while (sz > 1 && cross(sz - 1, sz - 2) > cross(sz - 1, sz)) {
            st[sz - 1] = st[sz];
            st.pop_back();
            sz--;
        }
    }

    ll query(ll x) {
        ll l = 0, r = st.size() - 1, mid;
        while (l < r) {
            mid = (l + r) / 2;
            if (cross(mid, mid + 1) <= x) l = mid + 1;
            else r = mid;
        }
        return st[l].first * x + st[l].second;
    }

    ll query2(ll x) {
        while (now + 1 < st.size() && cross(now, now + 1) <= x)now++;
        return st[now].first * x + st[now].second;
    }
};

void solve() {
    CHT C;
    vector<ll>a, b, dp;
    ll n;
    cin>>n;
    a.resize(n), b.resize(n), dp.resize(n);
    for (int i = 0; i < n; i++)cin >> a[i];
    for (int i = 0; i < n; i++)cin >> b[i];
    C.insert(b[0], 0);
    for (int i = 1; i < n; i++) {
        dp[i] = C.query2(a[i]);
        C.insert(b[i], dp[i]);
    }
    cout << dp[n - 1] << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    ll tc = 1;
    // cin >> tc;
    while (tc--) solve();
}
