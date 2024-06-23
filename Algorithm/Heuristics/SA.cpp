//BOJ 17008 AC CODE
#include<bits/stdc++.h>
#include<random>
#define all(v) v.begin(),v.end()
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using PP = pair<ll, P>;
const ll n_ = 5e5 + 105, inf = (ll)1e9 * (ll)1e9 + 7, mod = 1e9 + 7, sqrtN = 320;
ll dy[4] = { -1,0,1,0 }, dx[4] = { 0,1,0,-1 };
ll n, m, k, tc = 1, a, b, c, d, sum, x, y, z, base, ans, q;
ll gcd(ll x, ll y) {
	if (!y)return x;
	return gcd(y, x % y);
};
mt19937_64 seed(212121);
uniform_real_distribution<double>rng(0, 1), dd(0.99995, 1);
int checked[10100], A[10100], B[10100], C[10100], fix[10100];
vector<int>v[n_];
ll score = 0;
int cal(int i) {
	int now = 0;
	if (A[i] < 0 && !checked[-A[i]])now = 1;
	else if (A[i] > 0 && checked[A[i]])now = 1;

	if (B[i] < 0 && !checked[-B[i]])now = 1;
	else if (B[i] > 0 && checked[B[i]])now = 1;

	if (C[i] < 0 && !checked[-C[i]])now = 1;
	else if (C[i] > 0 && checked[C[i]])now = 1;
	return now;
}
void update(ll idx) {
	for (auto nxt : v[idx]) {
		ll bef = cal(nxt);
		checked[idx] ^= 1;
		ll now = cal(nxt);
		score += now;
		score -= bef;
		checked[idx] ^= 1;
	}
	checked[idx] ^= 1;
}
double T = 1, K = 2;
void sa() {
	random_device rd;
	mt19937 gen(rd());
	uniform_int_distribution<long long> R(1, n), I(0, 1);
	ll cnt = 0;
	vector<int>N;
	for (int i = 1; i <= n; i++) {
		if (fix[i] || v[i].empty())continue;
		checked[i] = I(gen);
		cnt++;
		N.push_back(i);
	}
	for (int i = 1; i <= m; i++)score += cal(i);
	if (N.size()) {
		uniform_int_distribution<long long> R(0, N.size() - 1);
		for (int j = 0; j < 1; j++) {
			T = 1;
			for (int i = 1; i <= n; i++) {
				if (fix[i] || v[i].empty())continue;
				checked[i] = I(gen);
			}
			score = 0;
			for (int i = 1; i <= m; i++)score += cal(i);
			for (int ii = 1; ii <= 1200300; ii++) {
				double now, nxt;
				now = score;
				if (score == m) {
					cout << "1" << '\n';
					for (int i = 1; i <= n; i++)cout << checked[i] << ' ';
					return;
				}
				int idx = N[R(gen)];
				update(idx);
				nxt = score;
				double pr = exp(-(now - nxt) / (K * T));
				if (pr < rng(seed))update(idx);
				idx = N[R(gen)];
				//0.0001확률로 무작위 업데이트
				if (rng(seed) < 0.0001)update(idx);
				T *= dd(seed);
			}
		}
	}
	else {
		if (score == m) {
			cout << "1" << '\n';
			for (int i = 1; i <= n; i++)cout << checked[i] << ' ';
			return;
		}
	}
	cout << "0";
}
void solve() {
	cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		cin >> A[i] >> B[i] >> C[i];
		int a = abs(A[i]), b = abs(B[i]), c = abs(C[i]);
		if (a == b && A[i] * B[i] < 0)continue;
		if (b == c && C[i] * B[i] < 0)continue;
		if (a == c && A[i] * C[i] < 0)continue;
		v[a].push_back(i);
		v[b].push_back(i);
		v[c].push_back(i);
		if (A[i] == B[i] && A[i] == C[i]) {
			ll now = abs(A[i]);
			fix[now] = 1;
			if (A[i] < 0)checked[now] = 0;
			else checked[now] = 1;
		}

	}
	for (int i = 1; i <= n; i++) {
		sort(all(v[i]));
		v[i].erase(unique(all(v[i])), v[i].end());
	}
	sa();
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	//cin >> tc;
	while (tc--)solve();
}
