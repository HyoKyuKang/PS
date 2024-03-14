//BOJ 13537 AC CODE
#include<iostream>
#include<algorithm>
#include<vector>
#include<cstring>

using namespace std;
int n, a, base, m, b, c, x, k;
vector<int> tree[100000 * 4 + 100];
int find(int l, int r) {
	l += base, r += base;
	int sum = 0;
	while (l <= r) {
		if (l % 2) {
			sum += tree[l].end() - upper_bound(tree[l].begin(), tree[l].end(), k);
			l++;
		}
		if (!(r % 2)) {
			sum += tree[r].end() - upper_bound(tree[r].begin(), tree[r].end(), k);
			r--;
		}
		l /= 2, r /= 2;
	}
	return sum;
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (base = 1; base < n; base *= 2);
	for (int i = 0; i < n; i++) {
		cin >> x;
		tree[base + i].push_back(x);
	}
	for (int i = base - 1; i; i--) {
		tree[i].resize(tree[i * 2].size() + tree[i * 2 + 1].size());
		merge(tree[i * 2].begin(), tree[i * 2].end(), tree[i * 2 + 1].begin(), tree[i * 2 + 1].end(), tree[i].begin());
	}
	cin >> m;
	for (int i = 0; i < m; i++) {
		cin >> a >> b >> k;
		cout << find(a - 1, b - 1) << '\n';
	}

	return 0;
}
