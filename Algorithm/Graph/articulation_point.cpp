//BOj 11266 AC CoDe
#include<bits/stdc++.h>
#define all(v) v.begin(),v.end()
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using PP = pair<ll, P>;
const ll n_ = 2e5 + 505, inf = (ll)2e9 * (ll)1e9 + 7, mod = 998244353;
ll dy[8] = { -1,0,1,0,1,1,-1,1-1 }, dx[8] = { 0,1,0,-1,1,-1,1,-1};
ll n, m, tc = 1, a, b, c, d, sum, x, y, z, base, ans,k;
ll gcd(ll x, ll y) {
	if (!y)return x;
	return gcd(y, x % y);
};

vector<ll>v[n_],res;
ll checked[n_],dep[n_],low[n_];
void dfs(ll x,ll par){
    dep[x]=low[x]=base++;
    bool flag=0;
    int cnt=0;
    for(auto nxt:v[x]){
        if(nxt==par)continue;
        if(checked[nxt]){
            low[x]=min(low[x],dep[nxt]);
            continue;
        }
        checked[nxt]=true;
        dfs(nxt,x);
        if(par && dep[x]<=low[nxt])flag=1;
        low[x]=min(low[x],low[nxt]);
        cnt++;
    }
    if(par==0 && cnt>=2)flag=true;
    if(flag)res.push_back(x);
    
}
void solve(){
    cin>>n>>m;
    while(m--){
        cin>>a>>b;
        v[a].push_back(b);
        v[b].push_back(a);
    }
    for(int i=1;i<=n;i++){
        if(checked[i])continue; 
        checked[i]=true;
        dfs(i,0);
    }
    cout<<res.size()<<endl;
    sort(all(res));
    for(auto nxt:res)cout<<nxt<<' ';
    
    
}
int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);	
#ifndef ONLINE_JUDGE
    //freopen("input.txt", "r", stdin);
#endif
	//cin >> tc;
	while (tc--)solve();
}
