
class manacher {
   public:
    vector<ll> v, M;
    manacher(string s) {
        ll n = s.size();
        for (int i = 0; i < n; i++) {
            v.push_back(s[i]);
            v.push_back(0);
        }
        v.pop_back();
        n = v.size();
        M.resize(n);
        for (ll i = 0, r = 0, p = 0; i < n; i++) {
            if (i <= r) M[i] = min(M[2 * p - i], r - i);
            while (i - M[i] - 1 >= 0 && i + M[i] + 1 < n && v[i - M[i] - 1] == v[i + M[i] + 1]) M[i]++;
            if (r < i + M[i]) {
                r = i + M[i];
                p = i;
            }
        }
    }
    bool pal(ll s, ll e) {
        ll si = s * 2, ei = e * 2;
        ll mid = (si + ei) / 2;
        ll len;
        if (mid % 2) len = 2 * ((M[mid] + 1) / 2);
        else len = 2 * ((M[mid] / 2) + 1);
        return len >= e - s + 1;
    }
    // s[i]가 중심인 최대 팰린드롬의 길이는?
    ll get(ll i) {
        if (i % 2) return (M[i] + 1) / 2;
        return ((M[i] / 2) + 1);
    }
};
