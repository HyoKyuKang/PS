//1bin 코드
int lv[NMAX], sa, sb, A[NMAX], B[NMAX], w[NMAX];
vector<int> adj[NMAX];

void bfs() {
	queue<int> q;
	memset(w, 0, sizeof(w));
	lv[0] = inf;
	for (int i = 1; i <= sa; i++) {
		if (!A[i]) {
			lv[i] = 0; q.emplace(i);
		}
		else lv[i] = inf;
	}

	while (q.size()) {
		int a = q.front(); q.pop();
		for (int& b : adj[a]) 
			if (lv[B[b]] == inf) {
				lv[B[b]] = lv[a] + 1;
				q.emplace(B[b]);
			}
	}
	return;
}

bool dfs(int a) {
	for (int& i = w[a]; i < adj[a].size(); i++) {
		int b = adj[a][i];
		if (!B[b] || lv[B[b]] == lv[a] + 1 && dfs(B[b])) {
			A[a] = b; B[b] = a;
			return 1;
		}
	}
	return 0;
}

int hop() {
	int ret = 0, f;
	while (1) {
		bfs();
		f = 0;
		for (int i = 1; i <= sa; i++)
			if (!A[i] && dfs(i)) f++;
		if (!f) break;
		ret += f;
	}
	return ret;
}
