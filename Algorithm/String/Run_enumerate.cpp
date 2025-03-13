//출처 : https://infossm.github.io/blog/2024/06/27/run-enumerate-problem-solving/
struct String {
	vector<int> sa, r, nr, lcp, lyndon;
	vector<vector<int>> mn;
	vector<tuple<int,int,int>> runs;
	string s;
	int lg, n;
	String(string& s):s(s), n(s.size()) {}
	bool cmp(int i, int j, int d) {
		if(r[i] == r[j]) return r[i+d] < r[j+d];
		return r[i] < r[j];
	}
	void use_sa() {
		if(!sa.empty()) return;
		int m = max(256, n) + 1;
		sa = vector<int>(n); r = nr = vector<int>(n+n);
		vector<int> t[m];
		for(int i=0;i<n;i++) sa[i] = i, r[i] = s[i];
		for(int d=1;r[sa[n-1]]!=n;d<<=1) {
			for(int j=d;j>=0;j-=d) {
				for(int i=0;i<m;i++) t[i] = vector<int>();
				for(int i:sa) t[r[i+j]].push_back(i); sa.clear();
				for(int i=0;i<m;i++) for(int x:t[i]) sa.push_back(x);
			}
			nr[sa[0]] = 1;
			for(int i=1;i<n;i++) nr[sa[i]] = nr[sa[i-1]] + cmp(sa[i-1], sa[i], d);
			swap(r, nr);
		}
		for(int i=0;i<=n;i++) r[i]--;
	}
	void use_lcp() {
		if(!lcp.empty()) return;
		use_sa();
		lcp = vector<int>(n);
		int l = 0;
		for(int i=0;i<n;i++) {
			if(r[i]) {
				int j = sa[r[i]-1];
				while(s[i+l] == s[j+l]) l++;
				lcp[r[i]] = l;
			}
			if(l) l--;
		}
	}
	void use_query() {
		if(!mn.empty()) return;
		use_lcp();
		lg = 0;
		while(n >= (1 << lg)) lg++;
		mn = vector<vector<int>>(lg, vector<int>(n+n));
		for(int i=0;i<n;i++) mn[0][i] = lcp[i];
		for(int j=1;j<lg;j++) for(int i=0;i<n;i++) mn[j][i] = min(mn[j-1][i], mn[j-1][i + (1<<j-1)]);
	}
	int query(int a, int b) {
		use_query();
		if(a < 0 || b < 0 || a >= n || b >= n) return 0;
		if(a == b) return n - a;
		a = r[a], b = r[b];
		if(a>b) swap(a,b);
		a++;
		int l = b - a + 1;
		int ret = 1e9;
		for(int i=lg-1;i>=0;i--) if(l&(1<<i)) ret = min(ret, mn[i][a]), a += (1<<i);
		return ret;
	}
	void use_lyndon() {
		if(!lyndon.empty()) return;
		use_sa();

		lyndon = vector<int>(n);
		vector<int> t;
		t.push_back(n);
		for(int i=n-1;i>=0;i--) {
			while(!t.empty() && r[t.back()] > r[i]) t.pop_back();
			lyndon[i] = t.back();
			t.push_back(i);
		}
	}
	void use_runs() {
		if(!runs.empty()) return;
		string t = s;
		reverse(t.begin(), t.end());
		String rs(t);
		t = s;
		for(char& c:t) c = 'a' + 'z' - c;
		String is(t);

		use_query();
		use_lyndon();
		rs.use_query();
		is.use_lyndon();

		for(int i=0;i<n;i++) {
			ll j = lyndon[i];
			ll l = i - rs.query(n-i, n-j);
			ll r = j + query(i, j);
			ll p = j - i;
			if(r - l >= 2 * p) runs.push_back({p, l, r});
		}
		for(int i=0;i<n;i++) {
			ll j = is.lyndon[i];
			ll l = i - rs.query(n-i, n-j);
			ll r = j + query(i, j);
			ll p = j - i;
			if(r - l >= 2 * p) runs.push_back({p, l, r});
		}
		sort(runs.begin(), runs.end());
		runs.erase(unique(runs.begin(), runs.end()), runs.end());
	}
};
/*
S를 -S로 변환할 때 for(char& c:t) c = 'a' + 'z' - c;를 사용하며, 이는 문제에서 요구하는 알파벳의 범위에 따라 수정해서 사용하셔야 합니다.
 */
