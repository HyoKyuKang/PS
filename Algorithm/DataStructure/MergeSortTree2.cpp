// 구간 쿼리 [L,R,K] -> A_L ~ A_R 에서 k번째 수는 무엇인가?
// 7469 AC Code
vector<int> tree[n_ * 4 + 100];
ll find(int l, int r, int c) {
	l += base, r += base;
	int s = -1e9, e = 1e9, tl = l, tr = r;
	while (s <= e) {
		priority_queue<int, vector<int>, greater<> >pq;
		int mid = (s + e) / 2, cnt = 0;
		l = tl, r = tr;
		while (l <= r) {
			if (l % 2) {
				cnt += lower_bound(tree[l].begin(), tree[l].end(), mid) - tree[l].begin();
				if(*(tree[l].end()-1)>=mid)
				pq.push(*lower_bound(tree[l].begin(), tree[l].end(), mid));
				l++;
			}
			if (!(r % 2)) {
				cnt += lower_bound(tree[r].begin(), tree[r].end(), mid) - tree[r].begin();
				if (*(tree[r].end() - 1) >= mid)
				pq.push(*lower_bound(tree[r].begin(), tree[r].end(), mid));
				r--;
			}
			l /= 2, r /= 2;
		}
		if (cnt == c - 1)
			return pq.top();
		if (cnt > c - 1)e = mid - 1;
		if (cnt < c - 1)s = mid + 1;
	}
	return -1;
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	for (base = 1; base < n; base *= 2);
	for (int i = 0; i < n; i++) {
		cin >> a;
		tree[base + i].push_back(a);
	}
	for (int i = base - 1; i; i--) {
		tree[i].resize(tree[i * 2].size() + tree[i * 2 + 1].size());
		merge(tree[i * 2].begin(), tree[i * 2].end(), tree[i * 2 + 1].begin(), tree[i * 2 + 1].end(), tree[i].begin());
	}
	while (m--) {
		cin >> a >> b >> c;
		cout << find(a - 1, b - 1, c) << '\n';
	}
	return 0;
}
