// 나중에 class로 만들어 사용할 계획입니다.
// thx to 1bin

struct edge {
	int to, cap, rev;
};
int lv[nmax], w[nmax];
vector<edge> adj[nmax];
void add_edge(int u, int v, int c) {
	adj[u].push_back({v, c, (int)adj[v].size()});
	adj[v].push_back({u, 0, (int)adj[u].size() - 1});
	return;
}
bool bfs(int s, int t) {
	memset(lv, 0, sizeof(lv));
	memset(w, 0, sizeof(w));
	queue<int> Q;
	Q.emplace(s);
	lv[s] = 1;
	while (Q.size()) {
		int now = Q.front();
		Q.pop();
		for (auto &e : adj[now]) {
			if (e.cap > 0 && !lv[e.to]) {
				lv[e.to] = lv[now] + 1;
				Q.emplace(e.to);
			}
		}
	}
	return lv[t];
}
