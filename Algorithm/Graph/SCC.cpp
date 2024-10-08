#include<iostream>
#include<algorithm>
#include<vector>
#include<stack>
#include<cassert>


using namespace std;
using ll = long long;
const ll n_ = 10010;
ll V, E, n, m, a, b, c, d, x, y, cnt;
ll dfsn[n_], SN, sn[n_];
vector<ll>v[n_];
vector<vector<ll>>SCC;
stack<ll>st;
bool fin[n_];

ll dfs(ll x) {
	dfsn[x] = ++cnt;
	st.push(x);
	ll ret = dfsn[x];
	for (ll nxt : v[x]) {
		if (!dfsn[nxt])ret = min(ret, dfs(nxt));
		else if (!fin[nxt])ret = min(ret, dfsn[nxt]);
        else assert(1);
	}
	if (ret == dfsn[x]) {
		vector<ll>currSCC;
		while (1) {
			ll a = st.top();
			st.pop();
			currSCC.push_back(a);
			fin[a] = true;
			sn[a] = SN;
			if (a == x)break;
		}
		sort(currSCC.begin(), currSCC.end());
		SCC.push_back(currSCC);
		SN++;
	}
    return ret;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> V >> E;
	while (E--) {
		cin >> a >> b;
		v[a].push_back(b);
		//v[b].push_back(a);
	}
	for (int i = 1; i <= V; i++)
		if (!dfsn[i])dfs(i);
	sort(SCC.begin(), SCC.end());
	cout << SN << '\n';
	for (auto cur : SCC) {
		for (auto c : cur)
			cout << c << ' ';
		cout << "-1" << '\n';
	}
}