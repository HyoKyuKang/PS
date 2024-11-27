#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
using namespace std;
using ll = long long;
const ll n_ = 2e5 + 10;
ll n, m, tc = 1;
ll pw(ll a, ll b, ll mod) {
    ll ret = 1;
    while (b) {
        if (b % 2) ret = ret * a % mod;
        a = a * a % mod;
        b /= 2;
    }
    return ret;
}
ll getpi(ll x) {
    ll ret = 1;
    for (ll i = 2; i * i <= x; i++) {
        if (x % i) continue;
        ll cnt = 0;
        while (!(x % i)) {
            x /= i;
            cnt++;
        }
        ret *= (pw(i, cnt, (ll)1e18) - pw(i, cnt - 1, (ll)1e18));
    }
    if (x != 1) ret *= (x - 1);
    return ret;
}

ll tower(vector<ll>& arr, ll l, ll r, ll mod) {
    //[arr[l],~ ,arr[r]] %mod를 return
    ll len = r - l + 1;
    if (len == 1) return arr[l] % mod;
    if (len <= 4) {
        ll val = arr[r];
        for (int i = r - 1; i >= l + 1; i--) {
            ll cnt = val;
            val = 1;
            for (int j = 0; j < cnt; j++) {
                val *= arr[i];
                if (val > 100) break;
            }
            if (val > 100) break;
        }
        if (val <= 100) {
            return pw(arr[l], val, mod);
        }
    }
    ll pi = getpi(mod);
    return pw(arr[l], tower(arr, l + 1, r, pi) + 100 * pi, mod);
}
void solve() {
    cin >> n;
    vector<ll> A(n);
    for (int i = 0; i < n; i++) cin >> A[i];
    ll idx = -1;
    for (int i = 0; i < n; i++) {
        if (A[i] == 1) {
            idx = i;
            break;
        }
    }
    if (idx != -1) {
        while (A.size() > idx) A.pop_back();
    }
    if (A.empty()) {
        cout << 1%m << '\n';
        return;
    }
    cout << tower(A, 0, A.size() - 1, m) << '\n';
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    cin >> tc >> m;
    while (tc--) solve();
};
