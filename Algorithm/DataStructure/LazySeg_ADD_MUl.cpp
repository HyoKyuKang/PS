class lazy_seg {
public:
    vector<ll> tree, lazy_mul, lazy_add, A;
    int n;

    lazy_seg(int n) : n(n) {
        tree.assign(4 * n + 4, 0);
        lazy_mul.assign(4 * n + 4, 1); // 항등원
        lazy_add.assign(4 * n + 4, 0);
        A.assign(n + 1, 0);
    }

    ll init(int node, int s, int e) {
        if (s == e) return tree[node] = A[s] % mod;
        int mid = (s + e) >> 1;
        return tree[node] = (init(node << 1, s, mid) + init(node << 1 | 1, mid + 1, e)) % mod;
    }

    void apply(int node, int s, int e, ll mul, ll add) {
        tree[node] = (tree[node] * mul % mod + (e - s + 1) * add % mod) % mod;

        lazy_mul[node] = lazy_mul[node] * mul % mod;
        lazy_add[node] = (lazy_add[node] * mul % mod + add) % mod;
    }

    void push(int node, int s, int e) {
        if (lazy_mul[node] == 1 && lazy_add[node] == 0) return;
        if (s != e) {
            int mid = (s + e) >> 1;
            apply(node << 1, s, mid, lazy_mul[node], lazy_add[node]);
            apply(node << 1 | 1, mid + 1, e, lazy_mul[node], lazy_add[node]);
        }
        lazy_mul[node] = 1;
        lazy_add[node] = 0;
    }

    void update(int node, int s, int e, int l, int r, ll mul, ll add) {
        push(node, s, e);
        if (r < s || e < l) return;
        if (l <= s && e <= r) {
            apply(node, s, e, mul % mod, add % mod);
            return;
        }
        int mid = (s + e) >> 1;
        update(node << 1, s, mid, l, r, mul, add);
        update(node << 1 | 1, mid + 1, e, l, r, mul, add);
        tree[node] = (tree[node << 1] + tree[node << 1 | 1]) % mod;
    }

    ll query(int node, int s, int e, int l, int r) {
        push(node, s, e);
        if (r < s || e < l) return 0;
        if (l <= s && e <= r) return tree[node];
        int mid = (s + e) >> 1;
        return (query(node << 1, s, mid, l, r) +
                query(node << 1 | 1, mid + 1, e, l, r)) % mod;
    }
};
