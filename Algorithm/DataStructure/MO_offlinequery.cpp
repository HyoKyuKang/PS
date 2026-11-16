
#include <bits/stdc++.h>
using namespace std;

using ll = long long;

// ============================================================
// 1. Ordinary Mo's Algorithm
// ============================================================

struct Query {
    int idx, l, r;
};

int BLOCK;

bool mo_cmp(const Query& a, const Query& b) {
    int ab = a.l / BLOCK;
    int bb = b.l / BLOCK;

    if (ab != bb) return ab < bb;
    if (ab & 1) return a.r > b.r;
    return a.r < b.r;
}

/*
Usage:

BLOCK = max(1, (int)sqrt(N));
sort(qs.begin(), qs.end(), mo_cmp);

int L = 0, R = -1; // Current interval: [L, R]

for (const auto& q : qs) {
    while (L > q.l) add(--L);
    while (R < q.r) add(++R);
    while (L < q.l) del(L++);
    while (R > q.r) del(R--);

    ans[q.idx] = get_answer();
}

Implement add(pos), del(pos), and get_answer().
Queries are 0-indexed inclusive intervals [l, r].

Complexity: O((N + Q) * sqrt(N) * C) when Q = O(N),
where C is the cost of a single add/del operation.
*/


// ============================================================
// 2. Hilbert Order Mo's Algorithm
// ============================================================

ll hilbert_order(int x, int y, int pw, int rot = 0) {
    if (pw == 0) return 0;

    int h = 1 << (pw - 1);
    int seg;

    if (x < h)
        seg = (y < h ? 0 : 3);
    else
        seg = (y < h ? 1 : 2);

    seg = (seg + rot) & 3;

    static const int rotate_delta[4] = {3, 0, 0, 1};

    int nx = x & (h - 1);
    int ny = y & (h - 1);
    int nrot = (rot + rotate_delta[seg]) & 3;

    ll sub_size = 1LL << (2 * pw - 2);
    ll ord = 1LL * seg * sub_size;
    ll sub = hilbert_order(nx, ny, pw - 1, nrot);

    if (seg == 1 || seg == 2)
        ord += sub;
    else
        ord += sub_size - sub - 1;

    return ord;
}

struct HilbertQuery {
    int idx, l, r;
    ll ord;

    bool operator<(const HilbertQuery& q) const {
        return ord < q.ord;
    }
};

/*
Usage:

int pw = 0;
while ((1LL << pw) < N) ++pw;
// Requires 2^pw >= N, and 2 * pw <= 62.

for (auto& q : qs)
    q.ord = hilbert_order(q.l, q.r, pw);

sort(qs.begin(), qs.end());

int L = 0, R = -1;

for (const auto& q : qs) {
    while (L > q.l) add(--L);
    while (R < q.r) add(++R);
    while (L < q.l) del(L++);
    while (R > q.r) del(R--);

    ans[q.idx] = get_answer();
}

The add/del logic is identical to ordinary Mo.
Only the query ordering changes.
*/


// ============================================================
// Notes
// ============================================================

/*
Ordinary Mo:
- Sort by l / BLOCK, alternating r-order by block.
- Default choice for most offline range query problems.
- BLOCK = sqrt(N) is a standard starting point for Q ~= N.
- More generally, BLOCK ~= N / sqrt(Q) can be considered.

Hilbert Mo:
- Treat each query as a 2D point (l, r).
- Sort queries along a Hilbert space-filling curve.
- Often improves locality and reduces pointer movement.
- Not guaranteed to be faster in practice.
- No special add-before-del ordering is required.

Both methods:
- Require offline queries.
- Support arbitrary range statistics if add/del are efficient.
- If left/right updates differ, use separate functions:
  add_left, add_right, del_left, del_right.
*/
