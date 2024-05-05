
class lazy_seg{
	public:
	vector<ll> tree, lazy, A;
	lazy_seg(int n)
	{
		// 0~n까지 쓰겠다.
		tree.resize(n * 4);
		lazy.resize(n * 4);
		A.resize(n * 4);
	}
	ll init(ll N, ll s, ll e)
	{
		if (s == e)
			return tree[N] = inf;
		ll mid = (s + e) / 2;
		return tree[N] = min(init(N * 2, s, mid) , init(N * 2 + 1, mid + 1, e));
	}
	void update_lazy(ll N, ll s, ll e)
	{
		if (!lazy[N])
			return;
		tree[N] +=  lazy[N];
		if (s != e)
		{
			lazy[N * 2] += lazy[N];
			lazy[N * 2 + 1] += lazy[N];
		}
		lazy[N] = 0;
	}
	void update(ll N, ll s, ll e, ll l, ll r, ll val)
	{
		update_lazy(N, s, e);
		if (l > e || r < s)
			return;
		if (l <= s && e <= r)
		{
			lazy[N] = val;
			update_lazy(N, s, e);
			return;
		}
		ll mid = (s + e) / 2;
		update(N * 2, s, mid, l, r, val);
		update(N * 2 + 1, mid + 1, e, l, r, val);
		tree[N] = min(tree[N * 2] , tree[N * 2 + 1]);
	}
	ll f(ll N, ll s, ll e, ll l, ll r)
	{
		update_lazy(N, s, e);
		if (l > e || r < s)
			return inf;
		if (l <= s && e <= r)
			return tree[N];
		ll mid = (s + e) / 2;
		return min(f(N * 2, s, mid, l, r) , f(N * 2 + 1, mid + 1, e, l, r));
	}
};
