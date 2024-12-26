//BOJ 9250 AC code


#include <bits/stdc++.h>
#define all(v) v.begin(), v.end()
using namespace std;
using ll = long long;
const ll n_ = 3e5 + 100;

const int nmax = 1e4 + 1;
class aho {
   public:
    // 최대 단어개수?
    int fail[nmax], fin[nmax], num = 1;
    char last[nmax];
    vector<pair<char, int>> edge[nmax];  // edge[x]={c,y}->c를 만나면 y로 이동
    int in(int node, char go) {
        for (auto nxt : edge[node]) {
            if (nxt.first == go) return nxt.second;
        }
        return -1;
    }
    void add(string S) {
        ll now = 0;
        for (auto nxt : S) {
            ll go = in(now, nxt);
            if (go == -1) {
                last[num] = nxt;
                edge[now].push_back({nxt, num});
                now = num++;
            }
            else now = go;
        }
        fin[now] = 1;
    }
    aho(vector<string> S) {
        for (auto nxt : S) add(nxt);
        queue<int> q;
        q.push(0);
        while (q.size()) {
            auto cur = q.front();
            q.pop();
            for (auto [a, nxt] : edge[cur]) {
                ll f = fail[cur];
                while (f && in(f, a) == -1) f = fail[f];
                if (in(f, a) != -1) f = in(f, a);
                if (!cur) f = 0;
                fin[nxt] |= fin[f];
                fail[nxt] = f;
                q.push(nxt);
            }
        }
    }
    int match(string s) {
        int now = 0;
        for (auto nxt : s) {
            while (now > 0 && in(now, nxt) == -1) now = fail[now];
            if (in(now, nxt) != -1) now = in(now, nxt);
            if (fin[now]) return 1;
        }
        return 0;
    }
};
void solve() {
    ll n;
    cin >> n;
    vector<string> S(n);
    for (int i = 0; i < n; i++) cin >> S[i];
    aho A(S);
    cin >> n;
    for (int i = 0; i < n; i++) {
        string s;
        cin >> s;
        if (A.match(s)) cout << "YES";
        else cout << "NO";
        cout << '\n';
    }
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0), cout.tie(0);
    ll tc = 1;
    // cin >> tc;
    while (tc--) solve();
};
