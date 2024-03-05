//Based on Dinic.cpp
struct edge {
	ll to, cap, rev;
	ll cost;
};
vector<edge> adj[n_];

void add_edge(int s, int e, int cap, ll cost) {
	adj[s].push_back({ e, cap, (int)adj[e].size(), cost });
	adj[e].push_back({ s, 0, (int)adj[s].size() - 1, -cost });
	return;
}

ll A[n_], pe[n_];
ll dist[n_];
ll inQ[n_];
bool spfa(int s, int t) {
	int now;
	fill(dist, dist + n_, inf);
	memset(inQ, 0, sizeof(inQ));

	queue<int> Q;
	Q.emplace(s); dist[s] = 0; inQ[s] = 1;
	while (Q.size()) {
		now = Q.front(); Q.pop();
		inQ[now] = 0;

		for (int i = 0; i < adj[now].size(); i++) {
			edge& e = adj[now][i];
			if (e.cap > 0 && dist[now] + e.cost < dist[e.to]) {
				dist[e.to] = dist[now] + e.cost;
				A[e.to] = now; pe[e.to] = i;
				if (!inQ[e.to]) {
					inQ[e.to] = 1;
					Q.emplace(e.to);
				}
			}
		}
	}
	return dist[t] != inf;
}
ll ret, flow_sum;
void mcmf(int s, int t) {
	ll flow, rev;
	while (spfa(s, t)) {
		flow = inf;
		for (int i = t; i != s; i = A[i])
			flow = min(flow, adj[A[i]][pe[i]].cap);
		ret += dist[t] * flow;
		flow_sum += flow;
		for (int i = t; i != s; i = A[i]) {
			rev = adj[A[i]][pe[i]].rev;
			adj[A[i]][pe[i]].cap -= flow;
			adj[i][rev].cap += flow;
		}
	}
	//ret->minimum cost
	//flow 계속 더하면 max flow도 구해갈 수 있음
	return;
}
