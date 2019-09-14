vll mul (vll& a, vll& b) {
	vll ans (sz(a) + sz(b) - 1);
	for (int i = 0; i < sz(a); i++)
		for (int j = 0; j < sz(b); j++)
			ans[i + j] = (ans[i + j] + a[i] * b[j] % mod) % mod;
	re ans;
}

vll interpolation (vector<pair<ll, ll>>& a) {
    vll cur = {1};
    for (int i = 0; i < sz(a); i++) {
    	vll tmp = {(mod - a[i].fi) % mod, 1};
    	cur = mul (cur, tmp);
    }
    vll ans(sz(a)), tmp(sz(a));
    for (int k = 0; k < sz(a); k++) {
    	ll x = a[k].fi;
    	ll y = cur.back();
    	ll z = 1;
    	for (int i = sz(ans) - 1; i >= 0; i--) {
    		tmp[i] = y;
    		y = (y * x % mod + cur[i]) % mod;
			if (i != k) z = z * (mod + x - a[i].fi) % mod;
		}
		z = a[k].se * power(z) % mod;
		for (int i = 0; i < sz(ans); i++)
			ans[i] = (ans[i] + z * tmp[i] % mod) % mod;
	}	
	re ans;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);

}