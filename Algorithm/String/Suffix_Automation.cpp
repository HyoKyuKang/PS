#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
using namespace std;
using ll = long long;
using P = pair<ll, ll>;
using PP = pair<ll, P>;
const ll n_ = 1e6 + 10, inf = (ll)2e9 * (ll)1e9 + 7, mod = 998244353;
ll n, m, tc = 1, a, b, c, d, sum, x, y, z, base, ans, k;

const int MAXA = 26;
//S.total ->최종 문자열 
//sa 최대 사이즈 -> 2n-1, 최대간선 3n-4
struct SuffixAutomaton {
    struct node {
        int nxt[MAXA], len, slink;
        node() {
            memset(nxt, -1, sizeof(nxt));
            len = slink = 0;
        }
        node(int _len, int _slink) {
            memset(nxt, -1, sizeof(nxt));
            len = _len;
            slink = _slink;
        }
    };
    vector<node> sa;
    int total;
    SuffixAutomaton() {
        total = 0;
        // sa.reserve(2000005);
        sa.push_back(node(0, -1));
    }
    void addChar(int c) {
        assert(0 <= c && c < MAXA);
        sa.push_back(node(sa[total].len + 1, 0));
        int p = total;
        total = (int)sa.size() - 1;
        while (p != -1 && sa[p].nxt[c] == -1) {
            sa[p].nxt[c] = total;
            p = sa[p].slink;
        }
        if (p != -1) {
            int prv = sa[p].nxt[c];
            int upd = sa[p].nxt[c];
            if (sa[p].len + 1 < sa[prv].len) {
                upd = (int)sa.size();


                node nd = sa[prv];
                nd.len = sa[p].len + 1;
                sa.push_back(nd);
                sa[prv].slink = upd;
                for (int j = p; j != -1 && sa[j].nxt[c] == prv; j = sa[j].slink) {
                    sa[j].nxt[c] = upd;
                }
            }
            sa[total].slink = upd;
        }
    }
};

void solve() {
    string s;
    cin >> s;
    SuffixAutomaton S;
    for (auto nxt : s) {
        if (nxt == '?') {
            cout << ans << '\n';
        }
        else {
            S.addChar(nxt - 'a');
            ll last = S.total;
            ans += S.sa[last].len - S.sa[S.sa[last].slink].len;
        }
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    // cin >> tc;
    while (tc--) solve();
};
