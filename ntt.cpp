/*
167772161   g=3
469762049   g=3 
1107296257  g=10
1711276033  g=29
1811939329  g=13 
2013265921  g=31 
2113929217  g=5
*/


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

int main() {

}
