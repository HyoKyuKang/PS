//https://github.com/dong-gas/algorithm/blob/main/TREES/PST.cpp

struct PST {
    ll l, r, v, cnt;

    PST() : l(0), r(0), v(0), cnt(0) {
    }
};

vector<ll> T;
PST tree[5050050]; //최악의 경우 생성 될 세그트리 노드의 개수만큼 넉넉히 만들기.
int tn; //새로 노드 만들 때, 인덱스임.
void update(int prv, int now, int s, int e, int idx, ll v) {
    tree[now].cnt = tree[prv].cnt + 1;
    tree[now].v = tree[prv].v + v;
    if (s == e)return;
    int mid = s + e >> 1;
    if (idx <= mid) {
        //왼쪽 자식 업데이트
        if (tree[now].l == 0) tree[now].l = ++tn;
        //왼쪽 자식이 없거나, 이전꺼랑 같으면 새로 만들어 줘야 함. tree[tn]이 그것

        tree[now].r = tree[prv].r;
        //오른쪽 자식이 빈 노드면 이전 거 그대로 사용
        update(tree[prv].l, tree[now].l, s, mid, idx, v);
    }
    else {
        if (tree[now].r == 0) tree[now].r = ++tn;
        tree[now].l = tree[prv].l;
        update(tree[prv].r, tree[now].r, mid + 1, e, idx, v);
    }
}

ll query(ll now, ll prv, ll s, ll e, ll k) {
    if (s == e) {
        return T[s] * k;
        if (tree[now].cnt - tree[prv].cnt < k)return -(ll)1e18;
        return T[s] * k;
    }
    ll mid = (s + e) / 2, cnt = tree[tree[now].r].cnt - tree[tree[prv].r].cnt;
    if (k <= cnt)return query(tree[now].r, tree[prv].r, mid + 1, e, k);
    else return query(tree[now].l, tree[prv].l, s, mid, k - cnt) + tree[tree[now].r].v - tree[tree[prv].r].v;
}

