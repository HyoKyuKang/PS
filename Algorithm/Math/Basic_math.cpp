
ll R[n_], L[n_];
ll pw(ll a, ll b) {
	ll ret = 1;
	while (b) {
		if (b % 2)ret = ret * a%mod;
		a = a * a%mod;
		b /= 2;
	}
	return ret;
}
ll inv(ll x) { return pw(x, mod - 2); }

ll ncr(ll n, ll r) { return R[n] * L[r] % mod * L[n - r] % mod; }

ll nhr(ll n, ll r) { return ncr(n + r - 1, r); }
void solve() {
	R[0] = 1;
	for (int i = 1; i < n_; i++) R[i] = R[i - 1] * i % mod;
	L[n_-1] = inv(R[n_-1]);
	for (int i = n_ - 2; i >= 0; i--) L[i] = L[i + 1] * (i + 1) % mod;
	cin >> m;
	while (m--) {
		cin >> a >> b;
		cout << ncr(a, b) << '\n';
	}
}
