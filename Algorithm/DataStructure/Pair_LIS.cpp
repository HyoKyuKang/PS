//BOJ15977 thx to jinhan814
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
const ll n_ =5e3+100, inf = (ll)2e9 * (ll)1e9 + 7, mod = 998244353;
ll n, m, tc = 1, a, b, c, d, sum, x, y, z, base, ans, k;
ll gcd(ll x,ll y){
	if(!y)return x;
	return gcd(y,x%y);
}
struct node{
	set<P>S;
	bool operator < (P a){
		auto it=S.lower_bound(a);
		return it!=S.begin() && (--it)->second<a.second;
	}
	void add(P a){
		auto it=++S.insert(a).first;
		while(it!=S.end()&&a.second<it->second)it=S.erase(it);
	}
};
void solve(){
	cin>>m>>n;
	if(m==2){
		vector<P>arr(n);
		for(int i=0;i<n;i++)cin>>arr[i].first;
		for(int i=0;i<n;i++)cin>>arr[i].second;
		sort(all(arr));
		vector<ll>LIS;
		for(auto [a,b]:arr){
			if(LIS.empty() || LIS.back()<b)LIS.push_back(b);
			else{
				auto it=lower_bound(all(LIS),b);
				*it=b;
			}
		}
		cout<<LIS.size()<<endl;
	}
	else{
		vector<PP>arr(n);
		for(int i=0;i<n;i++)cin>>arr[i].first;
		for(int i=0;i<n;i++)cin>>arr[i].second.first;
		for(int i=0;i<n;i++)cin>>arr[i].second.second;
		sort(all(arr));
		vector<node>LIS;
		for(auto[a,cur]:arr){
			auto [b,c]=cur;
			if(LIS.empty()||LIS.back()<cur)LIS.push_back({{cur}});
			else lower_bound(all(LIS),cur)->add(cur);
		}
		cout<<LIS.size()<<endl;
	}
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0); 
	//cin >> tc;
	while (tc--)solve();
}
