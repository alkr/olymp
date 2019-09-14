#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define sz(x)  ((int)x.size ())
#define all(x) (x).begin(), (x).end()
#define re return
#define mp make_pair
#define sqrt(x) sqrt (abs(x))
#define y0 y3451
#define y1 y4562
#define j0 j25624
#define j1 j45624
#define makeunique(x) sort(all(x)), (x).resize (unique(all(x)) - (x).begin())

typedef pair <int, int> ii;
typedef long long ll;
typedef unsigned long long ull;
typedef double D;
typedef long double ld;
typedef unsigned int uint;
typedef vector <string> vs;
typedef vector <int> vi;
typedef vector <ii> vii;
typedef vector <vi> vvi;
typedef vector <ll> vll;

template <class T> T abs (T x) { re x > 0 ? x : -x; }
template <class T> T sqr (T x) { re x * x; }
template <class T> T gcd (T a, T b) { re a ? gcd (b % a, a) : b; }
template <class T> int sgn (T x) { re x > 0 ? 1 : (x < 0 ? -1 : 0); }

#define filename ""

const int N = 2e5 + 20;
const int mod = 998244353;
const ll root = 15311432;
const ll revroot = 469870224;
const int degree = 1 << 22;

ll power (ll x, ll y = mod - 2) {
	ll ans = 1;
	while (y) {
		if (y & 1) ans = ans * x % mod;
		x = x * x % mod;
		y /= 2;
	}
	re ans;
}

int rev (int x, int p) {
	int ans = 0;
	for (int i = 0; i < p; i++, x /= 2) 
		ans = 2 * ans + (x & 1);
	re ans;
}

void fft (vll& a, int p, int inv = 0) {
	int n = (1 << p);
	for (int i = 0; i < n; i++) {
		int x = rev (i, p);
		if (x > i) swap (a[x], a[i]);
	}
	for (int len = 1; len < n; len *= 2) {
		ll w = inv ? revroot : root;
		w = power (w, degree / len);
		for (int i = 0; i < n; i += 2 * len) {
			ll cur = 1;
			for (int j = i; j < i + len; j++) {
				ll u = a[j];
				ll v = cur * a[j + len] % mod;
				a[j] = (u + v) % mod;
				a[j + len] = (mod + u - v) % mod;
				cur = cur * w % mod;
			}
		}
	}
	if (inv) {
		ll x = power(n);
		for (int i = 0; i < n; i++) 
			a[i] = a[i] * x % mod;
	}
}

void mult (vll& a, vll& b, int p) {
	fft (a, p);
	fft (b, p);
	for (int i = 0; i < (1 << p); i++)
		a[i] = a[i] * b[i] % mod;
	fft (a, p, 1);
}

vll inv (vll a, int n) {
	vll ans (2 * n);
	ans[0] = power(a[0]);
	for (int l = 1; (1 << l) <= n; l++) {
		int len = (1 << l);
		vll tmp (2 * len);
		for (int i = 0; i < min(len, sz(a)); i++) tmp[i] = a[i];
		fft (ans, l + 1); 
		fft (tmp, l + 1);
		for (int i = 0; i < 2 * len; i++) { 
			tmp[i] = (mod + 2 - tmp[i] * ans[i] % mod) % mod;
			ans[i] = ans[i] * tmp[i] % mod;
		}
		fft (ans, l + 1, 1);
		fill (ans.begin() + len, ans.end(), 0);
	}
	re ans;
}

vll lg (vll a, int n) {
	vll ans = inv (a, n);	
	vll tmp (2 * n);
	for (int i = 0; i < min(n, sz(a)) - 1; i++) tmp[i] = a[i + 1] * (i + 1) % mod;
	int p = __builtin_ctz(n) + 1;
	mult (ans, tmp, p);
	for (int i = 2 * n; i; i--) ans[i] = (i >= n) ? 0 : ans[i - 1] * power(i) % mod;
	ans[0] = 0;
	re ans;
}

vll ex (vll a, int n) {
	vll ans (2 * n);
	ans[0] = 1;
	for (int l = 1; (1 << l) <= n; l++) {
		int len = (1 << l);
		vll tmp = lg (ans, len);
		for (int i = 0; i < len; i++) tmp[i] = ((i < sz(a) ? a[i] : 0) + mod - tmp[i]) % mod;
		tmp[0]++;
		mult (ans, tmp, l + 1);
		fill (ans.begin() + len, ans.end(), 0);
	}					                     	
	re ans;
}

vll deg (vll a, ll k, int n) {
	vll ans = lg (a, n);
	for (int i = 0; i < n; i++) ans[i] = k * ans[i] % mod;
	ans = ex (ans, n);	
	re ans;
}

int main() {
	vll a = {1, 1};
	vll b = deg (a, mod - 1, 128);
	vll c = inv (a, 128);
	for (auto x : b) cout << x << " ";
	cout << endl;
	for (auto x : c) cout << x << " ";
}
