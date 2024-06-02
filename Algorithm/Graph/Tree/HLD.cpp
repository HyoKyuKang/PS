//https://codeforces.com/contest/1975/problem/E 
//class로 템플릿화할 필요가 있는데 나중에 천천히 할 예정...

#include<bits/stdc++.h>
#pragma GCC optimize("O3")
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("avx2")
#define all(v) v.begin(),v.end()
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using PP = pair<ll, P>;
const ll n_ =1e6+100, inf = (ll)2e9 * (ll)1e9 + 7, mod = 1e9+7;
ll n, m, tc = 1, a, b, c, d, sum, x, y, z, base, ans, k;
ll gcd(ll x,ll y){
	if(!y)return x;
	return gcd(y,x%y);
}
ll color[n_];
ll nn, num[n_], idx[n_], top[n_], dpt[n_], par[n_], sz[n_];
ll tree[n_ * 4];
vector<ll>v[n_];
void dfs(ll x, ll parent) {
	sz[x] = 1;
	for (auto nxt : v[x]) {
		if (nxt == parent)continue;
		dpt[nxt] = dpt[x] + 1;
		par[nxt] = x;
		dfs(nxt, x);
		sz[x] += sz[nxt];
	}
}
void dfs2(ll x) {
	ll c = -1;
	num[x] = nn++, idx[num[x]] = x;
	for (auto nxt : v[x]) {
		if (par[nxt] == x && (c == -1 || sz[nxt] > sz[c]))c = nxt;
	}
	if (c != -1) {
		top[c] = top[x];
		dfs2(c);
	}
	for (auto nxt : v[x]) {
		if (nxt == par[x] || nxt == c)continue;
		top[nxt] = nxt;
		dfs2(nxt);
	}
}
void init_hld(ll r) {
	top[r] = par[r] = r;
	dfs(r, 0); dfs2(r);
}
void init_seg() {
	for (base = 1; base < n + 1; base *= 2);
	for (int i = 0; i <=n*4; i++)tree[i] = 0;
	for (int i = 1; i <= n; i++)tree[base + num[i]] = color[i];
	for(int i=base-1;i;i--)tree[i]=tree[i*2]+tree[i*2+1];
}
ll f(ll l, ll r) {
	//max seg
	l += base, r += base;
	ll ret=0;
	while (l <= r) {
		if (l % 2)ret+=tree[l++];
		if (!(r % 2))ret+=tree[r--];
		l /= 2, r /= 2;
	}
	return ret;
}
void update(ll idx, ll val) {
	idx += base;
	tree[idx]=val;
	idx /= 2;
	while (idx) {
		tree[idx]=tree[idx*2]+tree[idx*2+1];
		idx /= 2;
	}
}
ll query(ll a, ll b) {
	ll ret=0;
	while (top[a] != top[b]) {
		if (dpt[top[a]] < dpt[top[b]])swap(a, b);
		ret+=f(num[top[a]], num[a]);
		a = par[top[a]];
	}
	if (dpt[a] > dpt[b])swap(a, b);
	ret+=f(num[a],num[b]);
	return ret;
}
ll lca(ll a, ll b) {
	while (top[a] != top[b]) {
		if (dpt[top[a]] < dpt[top[b]])swap(a, b);
		a = par[top[a]];
	}
	if (dpt[a] > dpt[b])swap(a, b);
	return a;
}
void solve(){
	cin>>n>>m;
	ll cnt=0;
	for(int i=1;i<=n;i++){
		cin>>color[i];
		if(color[i])cnt++;
	}
	for(int i=1;i<n;i++){
		cin>>a>>b;
		v[a].push_back(b);
		v[b].push_back(a);
	}
	init_hld(1);
	init_seg();
	
	vector<int>child_num(n+1);
	set<int>st;
	set<P>st2;
	//st2는 최소 dep
	//st는 밑에 노드가 없는 것들 최소 1개고 2개 이하여야 체인 가능성이 있음.
	for(int i=2;i<=n;i++){
		if(color[i])child_num[par[i]]++;
	}
	for(int i=1;i<=n;i++){
		if(!color[i])continue;
		if(child_num[i]==0)st.insert(i);
		st2.insert({dpt[i],i});
	}
	while(m--){
		cin>>a;
		color[a]^=1;
		if(color[a]){
			//새로 생겼습니다...
			update(num[a],1);
			st2.insert({dpt[a],a});
			if(child_num[a]==0)st.insert(a);
			if(a!=1){
				child_num[par[a]]++;
				if(color[par[a]] && child_num[par[a]]==1)st.erase(par[a]);
			}
			cnt++;
		}
		else{
			update(num[a],0);
			st2.erase({dpt[a],a});
			if(child_num[a]==0)st.erase(a);
			if(a!=1){
				child_num[par[a]]--;
				if(color[par[a]] && child_num[par[a]]==0)st.insert(par[a]);
			}
			cnt--;
		}
		if(cnt==0){
			cout<<"No"<<'\n';
		}
		else if(cnt==1){
			cout<<"Yes"<<'\n';
		}
		else{
			if(st.size()>=3 || st.size()==0)cout<<"No"<<'\n';
			else if(st.size()==1){
				//일직선이면 ok입니당...
				auto it=st2.begin();
				x=(*it).second;
				y=*st.begin();
				ll node_num=dpt[y]-dpt[x]+1;
				if(cnt==node_num && cnt==query(x,y))cout<<"Yes"<<'\n';
				else cout<<"No"<<'\n';
			}
			else if(st.size()==2){
				auto it=st.begin();
				x=*it;
				it++;
				y=*it;
				ll val=query(x,y);
				auto it2=st2.begin();
				z=(*it2).second;
				ll node_num=dpt[x]-dpt[z]+dpt[y]-dpt[z]+1;
				if(lca(x,y)==z && cnt==node_num && cnt==val)cout<<"Yes"<<'\n';
				else cout<<"No"<<'\n';
			}
		}
	}
	nn=0;
	for(int i=1;i<=n;i++)v[i].clear();
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);  
	cin >> tc;
	while (tc--)solve();
}
