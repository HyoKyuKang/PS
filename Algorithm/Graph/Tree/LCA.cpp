//11438 AC Code
#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;
int n, m;
const int n_ = 100000 + 1;
vector<int>v[n_];
int  parent[n_][21], d[n_], a, b;//parent[x][i]는 x의 2의 i제곱번째 부모!
void dfs(int x, int par) {
	d[x] = d[par] + 1;
	for (int nxt : v[x]) {
		if (nxt == par)continue;
		parent[nxt][0] = x;
		dfs(nxt, x);
	}
}
void func() {
	for (int i = 1; i < 21; i++)
		for (int j = 1; j <= n; j++)
			parent[j][i] = parent[parent[j][i - 1]][i - 1];
}
int lca(int x, int y) {
	if (d[x] > d[y])swap(x, y);//항상 y의 depth가 더 깊게 만들어주자!
	for (int i = 20; i >= 0; i--)
		if (d[y] - d[x] >= (1 << i))
			y = parent[y][i];
	if (x == y)return x;
	for (int i = 20; i >= 0; i--) {
		if (parent[x][i] != parent[y][i]) {
			x = parent[x][i];
			y = parent[y][i];
		}
	}
	return parent[x][0];
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		cin >> a >> b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	dfs(1, 0);
	func();
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> a >> b;
		cout << lca(a, b) << '\n';
	}
}
