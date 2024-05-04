//BOJ17539 AC Code
#include<iostream>
#include<algorithm>
#include<vector>


using namespace std;
using ll = long long;
typedef vector<vector<ll> >matrix;
const ll MOD = 1e9 + 7;
matrix operator *(const  matrix &a, const  matrix &b) {
	ll size = a.size(), size2 = b[0].size(), size3 = b.size();
	matrix res(size, vector<ll>(size2));
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size2; j++) {
			for (int k = 0; k < size3; k++) {
				res[i][j] += a[i][k] * b[k][j];
				res[i][j] %= MOD;
			}
			res[i][j] %= MOD;
		}
	return res;
}
matrix power(matrix a, ll n) {//a행렬을 n제곱 하겠다!
	ll size = a.size();
	matrix res(size, vector<ll>(size));
	for (int i = 0; i < size; i++)res[i][i] = 1;//단위 행렬 생성
	while (n) {
		if (n % 2)res = res * a;
		n /= 2;
		a = a * a;

	}
	return res;
}

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0), cout.tie(0);
	ll n, m, a;
	cin >> n;
	if (n == 1) {
		cout << "2";
		return 0;
	}
	if (n == 2) {
		cout << "24";
		return 0;
	}
	matrix mm;
	mm.push_back({ 2,16,0,4 });
	mm.push_back({ 0,2,4,1 });
	mm.push_back({ 0,1,0,0 });
	mm.push_back({ 0,0,0,2 });

	matrix res = power(mm, n - 3);
	matrix ANS;
	ANS.push_back({ 48 });
	ANS.push_back({ 6 });
	ANS.push_back({ 1 });
	ANS.push_back({ 4 });
	res = res * ANS;
	cout << (res[0][0] * 2) % MOD << '\n';
}
