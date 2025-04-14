//https://github.com/dong-gas/algorithm/blob/main/TREES/PST.cpp
struct PST {
    int l, r, v;
    PST() : l(0), r(0), v(0) {}
};

PST tree[300030]; //최악의 경우 생성 될 세그트리 노드의 개수만큼 넉넉히 만들기.
int tn; //새로 노드 만들 때, 인덱스임.

void update(int prv, int now, int s, int e, int idx, int v) {
    if(s==e) {
        tree[now].v=tree[prv].v+v;
        return;
    }
    int mid=s+e>>1;
    if(idx<=mid) {//왼쪽 자식 업데이트
        if(tree[now].l==0 || tree[now].l==tree[prv].l) tree[now].l=tn++;
        //왼쪽 자식이 없거나, 이전꺼랑 같으면 새로 만들어 줘야 함. tree[tn]이 그것
        
        if(tree[now].r==0) tree[now].r=tree[prv].r;
        //오른쪽 자식이 빈 노드면 이전 거 그대로 사용
        
        update(tree[prv].l,tree[now].l,s,mid,idx,v);
    }
    else {
        if(tree[now].r==0 || tree[now].r==tree[prv].r) tree[now].r=tn++;
        if(tree[now].l==0) tree[now].l=tree[prv].l;
        update(tree[prv].r,tree[now].r,mid+1,e,idx,v);
    }
    tree[now].v=tree[tree[now].l].v+tree[tree[now].r].v;
}

int query(int node, int s, int e, int l, int r) {
    if(l<=s && e<=r) return tree[node].v;
    if(s>r || e<l) return 0;
    int mid=s+e>>1;
    return query(tree[node].l,s,mid,l,r) + query(tree[node].r,mid+1,e,l,r);
}
