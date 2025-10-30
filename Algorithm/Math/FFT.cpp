//Code From https://github.com/dong-gas/algorithm/blob/main/MATH/FFT.cpp
//FFT
//TLE 나면 double로 gogo
//boj.kr/11385(씽크스몰): double로 하면 틀림.
//기본을 long double로 가고, 시간 터지면 double로 하자...

//생성함수 유명한 등식
// ── Formal power series 기본(수렴 가정 불필요; 해석적 의미로는 |x|<1) ──

// [기하급수 Geometric series]
/*
1/(1 - x) = Σ_{n≥0} x^n
1/(1 - a x) = Σ_{n≥0} a^n x^n
(1 - x)^{-m} = Σ_{n≥0} C(n+m-1, m-1) x^n
[x^n] (1 - a x)^{-m} = a^n * C(n+m-1, m-1)
(1 - x^L)/(1 - x) = 1 + x + ... + x^{L-1}
*/

// [로그/지수 Log/Exp]
/*
-log(1 - x) = Σ_{n≥1} x^n / n
log(1/(1 - x)) = Σ_{n≥1} x^n / n            // 같은 식
-log(1 - x^k) = Σ_{r≥1} x^{kr} / r          // t = x^k 치환
exp(x) = Σ_{n≥0} x^n / n!
exp(ax) = Σ_{n≥0} a^n x^n / n!
log(1 + U) = Σ_{m≥1} (-1)^{m+1} U^m / m     // 상수항(U(0)) = 0일 때 형식적 정의
*/

#define double long double 
#define sz(v) ((int)(v).size())
typedef complex<double> base;

void fft(vector <base>& a, bool invert)
{
	int n = sz(a);
	vector<base>roots(n / 2);
	for (int i = 1, j = 0; i < n; i++) {
		int bit = n >> 1;
		for (; j >= bit; bit >>= 1) j -= bit;
		j += bit;
		if (i < j) swap(a[i], a[j]);
	}
	for (int i = 2; i <= n; i <<= 1) {
		vector<base> w(i / 2);
		for (int j = 0; j < i / 2; ++j) {
			double th = 2 * acos(-1.L)*j / i * (invert ? -1 : 1);
			w[j] = base(cos(th), sin(th));
		}
		for (int j = 0; j < n; j += i) {
			for (int k = 0; k < i / 2; ++k) {
				base u = a[j + k], v = a[j + k + i / 2] * w[k];
				a[j + k] = u + v;
				a[j + k + i / 2] = u - v;
			}
		}
	}
	if (invert)	for (int i = 0; i < n; i++)a[i] /= n;
}

void multiply(const vector<ll>& a, const vector<ll >& b, vector<ll>& res)
{
	vector <base> fa(all(a)), fb(all(b));
	ll n = 1;
	while (n < max(sz(a), sz(b))) n <<= 1;
	n <<= 1;
	fa.resize(n); fb.resize(n);
	fft(fa, false); fft(fb, false);
	for (int i = 0; i < n; i++) fa[i] *= fb[i];
	fft(fa, true);
	res.resize(n);
	for (int i = 0; i < n; i++) res[i] = ll(fa[i].real() + (fa[i].real() > 0 ? 0.5 : -0.5));
}
