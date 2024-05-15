
struct seg{
	public:
	vector<ll>tree;
	ll base;
	seg(int n){
		for(base=1;base<=n;base*=2);
		//0~n쓰겠다
		tree.resize(n*4+4);
	}
	ll f(ll l,ll r){
		l+=base,r+=base;
		ll ret=0;
		while(l<=r){
			if(l%2)ret+=tree[l++];
			if(!(r%2))ret+=tree[r--];
			l/=2,r/=2;
		}
		return ret;
	}
	void update(ll i,ll v){
		i+=base;
		tree[i]+=v;
		i/=2;
		while(i){
			tree[i]=tree[i*2]+tree[i*2+1];
			i/=2;
		}
	}
	
};
