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
const ll n_ =1e6+100, inf = (ll)2e9 * (ll)1e9 + 7, mod = 998244353;
ll n, m, tc = 1, a, b, c, d, sum, x, y, z, base, ans, k;
ll gcd(ll x,ll y){
	if(!y)return x;
	return gcd(y,x%y);
}
class seg{
	public:
	vector<ll>tree;
	ll base;
	seg(int n){
		for(base=1;base<=n;base*=2);
		//0~n쓰겠다
		tree.resize(n*4+4);
		for(int i=0;i<tree.size();i++)tree[i]=-inf;
	}
	ll f(ll l,ll r){
		l+=base,r+=base;
		ll ret=-inf;
		while(l<=r){
			if(l%2)ret=max(ret,tree[l++]);
			if(!(r%2))ret=max(ret,tree[r--]);
			l/=2,r/=2;
		}
		return ret;
	}
	void update(ll i,ll v){
		i+=base;
		tree[i]=max(tree[i],v);
		i/=2;
		while(i){
			tree[i]=max(tree[i*2],tree[i*2+1]);
			i/=2;
		}
	}
};
void solve(){
	cin>>n;
	vector<ll>A(n+1),B(n+1),pre(n*2+1);
	for(int i=1;i<=n;i++){
		cin>>A[i];
		A.push_back(A[i]);
	}
	for(int i=1;i<=n;i++){
		cin>>B[i];
		B.push_back(B[i]);
	}
	for(int i=1;i<=n;i++)pre[i]=pre[i-1]+A[i];



}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0); 
	//cin >> tc;
	while (tc--)solve();
}
