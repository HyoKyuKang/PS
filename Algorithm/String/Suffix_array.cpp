//BOJ 9048 AC CODE
#include<iostream>
#include<algorithm>
#include<vector>
#include<cmath>
#include<queue>
#include<string>
#include<cstring>
#include<stack>
#include<map>
#include<set>
#include<deque>
#include<functional>
#include<unordered_map>
#include<list>

//#define double long double
//s.erase(unique(s.begin(),s.end()),s.end())
//written by djs100201
#define all(v) v.begin(),v.end()
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using PP = pair<ll, P>;
const ll n_ = 1e6 + 100, inf = 1e18, mod = 1e9 + 7, sqrtN = 333;
ll n, m, k, tc = 1, a, b, c, d, x, y, z, ans;
string s;
ll gcd(ll x, ll y) {
	if (!y)return x;
	return gcd(y, x % y);
}

ll group[n_], sa[n_], num[n_], cnt[n_], temp[n_], rev_sa[n_], lcp[n_];
bool cmp(ll x, ll y) {
	if (group[x] != group[y])return group[x] < group[y];
	x += d, y += d;
	if (x < n && y < n)return group[x] < group[y];
	return x > y;
}
void make_lcp(string& s) {
	n = s.size();
	for (int i = 0; i < n; i++) {
		group[i] = s[i]-'a'+1;
		sa[i] = i;
	}
	m = max((ll)(27), n + 1);
	for (d = 1; d < n; d *= 2) {
		fill(num, num + m, 0);
		for (int i = 0; i < n; i++)num[group[i + d]]++;
		for (int i = 1; i < m; i++)num[i] += num[i - 1];
		for (int i = n - 1; i >= 0; i--)cnt[--num[group[i + d]]] = i;

		fill(num, num + m, 0);
		for (int i = 0; i < n; i++) num[group[i]]++;
		for (int i = 1; i < m; i++) num[i] += num[i - 1];
		for (int i = n - 1; i >= 0; i--) sa[--num[group[cnt[i]]]] = cnt[i];

		temp[0] = 1;
		for (int i = 1; i < n; i++)temp[i] = temp[i - 1] + cmp(sa[i - 1], sa[i]);
		for (int i = 0; i < n; i++)group[sa[i]] = temp[i];
		if (temp[n - 1] == n)break;
	}
	for (int i = 0; i < n; i++)rev_sa[sa[i]] = i;
	ll len = 0;
	for (int i = 0; i < n; i++) {
		if (!rev_sa[i])continue;
		for (int j = sa[rev_sa[i] - 1]; s[i + len] == s[j + len]; len++);
		lcp[rev_sa[i]] = len;
		len--;
		if (len < 0)len++;
	}
    
	/*디버깅용 코드
	for (int i = 0; i < n; i++) {
		cout << s.substr(sa[i], n - sa[i]);
		cout << endl;
	}
	*/
}
void solve() {
	string s;
	cin >> s;
	make_lcp(s);
	for (int i = 0; i < n; i++)cout << sa[i] + 1 << ' ';
	cout << '\n';
	cout << "x ";
	for (int i = 1; i < n; i++)cout << lcp[i] << ' ';
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	//cin >> tc;
	while (tc--)solve();
}
