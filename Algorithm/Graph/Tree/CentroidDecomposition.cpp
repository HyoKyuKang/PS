//BOJ 29161
#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#define all(v) v.begin(),v.end()

using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using PP = pair<ll, P>;
const ll n_ = 2e5 + 100, inf = (ll)1e9 * (ll)1e9 + 7, mod = 1e9 + 7, sqrtN = 320;

ll dy[4] = { -1,0,1,0 }, dx[4] = { 0,1,0,-1 };
ll n, m, k, tc = 1, a, b, c, sum, x, y, z, base, ans, q;
ll gcd(ll x, ll y) {
	if (!y)return x;
	return gcd(y, x % y);
}
ll checked[n_], sz[n_], dist[n_], par_[n_], dp[n_],rev[n_];
vector<P>v[n_];
vector<ll>edge[n_];
vector<int>val[4000001],pre[4000001];
map<ll,int>mp[n_];
ll parent[n_][19], d[n_],d2[n_];
//v는 tree에서의 간선
//edge는 centeroid tree에서의 간선
ll get_sz(ll x, ll par) {
	ll ret = 1;
	for (auto [nxt,a] : v[x]) {
		if (nxt == par || checked[nxt])continue;
		ret += get_sz(nxt, x);
	}
	return sz[x] = ret;
}
ll centroid(ll x, ll par, ll N) {
	for (auto [nxt,a] : v[x]) {
		if (nxt == par || checked[nxt])continue;
		if (sz[nxt] * 2 > N)return centroid(nxt, x, N);
	}
	return x;
}
ll make_centroid(ll x) {
	x = centroid(x, 0, get_sz(x, 0));
	checked[x] = true;
	for (auto [nxt,a] : v[x]) {
		if (checked[nxt])continue;
		ll now = make_centroid(nxt);
		//cout<<x<<' '<<now<<endl;
		edge[x].push_back(now);
		par_[now] = x;
	}
	return x;
}

void dfs(int x, int par) {
	d[x] = d[par] + 1;
	for (auto [nxt,a] : v[x]) {
		if (nxt == par)continue;
		d2[nxt]=d2[x]+a;
		parent[nxt][0] = x;
		dfs(nxt, x);
	}
}
void func() {
	for (int i = 1; i < 19; i++)
		for (int j = 0; j < n; j++)
			parent[j][i] = parent[parent[j][i - 1]][i - 1];
}
int lca(int x, int y) {
	if (d[x] > d[y])swap(x, y);//항상 y의 depth가 더 깊게 만들어주자!
	for (int i = 18; i >= 0; i--)
		if (d[y] - d[x] >= (1 << i))
			y = parent[y][i];
	if (x == y)return x;
	for (int i = 18; i >= 0; i--) {
		if (parent[x][i] != parent[y][i]) {
			x = parent[x][i];
			y = parent[y][i];
		}
	}
	return parent[x][0];
}
ll get_dist(ll x, ll y) {
	ll z = lca(x, y);
	return abs(d2[z] - d2[x]) + abs(d2[z] - d2[y]);
}
ll in[n_],out[n_];
void dfs2(ll x){
	in[x]=base++;
	rev[in[x]]=x;
	for(auto nxt:edge[x]){
		//cout<<x<<' '<<nxt<<endl;
		dfs2(nxt);
	}
	out[x]=base-1;
}
void solve() {
	cin >> n >> m;
	for (int i = 1; i < n; i++) {
		cin >> a >> b >> c;
		a--,b--;
		v[a].push_back({b,c});
		v[b].push_back({a,c});
	}
	dfs(0, -1);
	func();
	ll root=make_centroid(0);
	dfs2(root);
	base=0;
	for(int i=0;i<n;i++){
		for(int j=in[i];j<=out[i];j++){
			x=get_dist(i,rev[j]);
			if(mp[i].find(x)==mp[i].end())mp[i][x]=base++;
            if(val[mp[i][x]].size()==0)val[mp[i][x]].push_back(-1);
			val[mp[i][x]].push_back(j);
		}
	}
	for(int i=0;i<base;i++){
		pre[i].resize(val[i].size());
		for(int j=1;j<pre[i].size();j++)pre[i][j]=pre[i][j-1]^(rev[val[i][j]]+1);
	}
	while(m--){
		cin>>a>>b;
		a--;
		x=a;
		ans=0;
		if(mp[x].find(b)!=mp[x].end()){
			ll idx=mp[x][b];
			ans^=pre[idx].back();
		}
		ll bef=x;
		while(x!=root){
			x=par_[x];
			ll dist=get_dist(a,x);
			if(dist<=b){
				ll left=b-dist;
				if(mp[x].find(left)!=mp[x].end()){
					ll idx=mp[x][left];
					ans^=pre[idx].back();
					ll l=in[bef],r=out[bef];
					r=upper_bound(all(val[idx]),r)-val[idx].begin();
					r--;
					ans^=pre[idx][r];
					l=lower_bound(all(val[idx]),l)-val[idx].begin();
					l--;
					ans^=pre[idx][l];
				}
			}
			bef=x;
		}
		cout<<ans<<'\n';
	}
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	//cin >> tc;
	while (tc--)solve();
}
