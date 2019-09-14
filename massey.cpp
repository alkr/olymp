const int mod = 998244353;

ll power (ll x, ll y = mod - 2) {
	ll ans = 1;
	while (y) {
		if (y & 1) ans = ans * x % mod;
		x = x * x % mod;
		y /= 2;
	}
	re ans;
}

vll massey (vll& a) {
	vll ans(1, 1), last(1, 1);
	int len = 0, p = 1;
	ll b = 1;
	for (int n = 0; n < sz(a); n++, p++) {
		ll d = 0;
		for (int i = 0; i <= len; i++) 
			d = (d + mod + a[n - i] * ans[i] % mod) % mod;
		if (d == 0) continue;
		auto prv = ans;
		if (sz(ans) < sz(last) + p) ans.resize(sz(last) + p, 0);
		ll r = d * power(b) % mod;
		for (int i = 0; i < sz(last); i++)
			ans[i + p] = (ans[i + p] + mod - r * last[i] % mod) % mod;
		if (2 * len <= n) {
			len = n + 1 - len;
			b = d;
			last = prv;
			p = 0;
		}
	}
	ans.resize(len + 1);
	re ans;
}