#pragma GCC optimize("O3")
#include <bits/stdc++.h>

using namespace std;

#define fi first
#define se second
#define pb push_back
#define sz(x) ((int)x.size ())
#define all(x) (x).begin(), (x).end()
#define re return
#define mp make_pair
#define sqrt(x) sqrt (abs(x))
#define y0 y3451
#define y1 y4562
#define makeunique(x) sort(all(x)), (x).resize (unique(all(x)) - (x).begin())
#define endl '\n'

typedef pair <int, int> ii;
typedef long long ll;
typedef unsigned long long ull;
typedef double D;
typedef long double ld;
typedef unsigned int uint;
typedef vector <string> vs;
typedef vector <int> vi;
typedef vector <ii> vii;
typedef vector <ll> vll;
typedef vector <vi> vvi;

template <class T> T abs (T x) { re x > 0 ? x : -x; }
template <class T> T sqr (T x) { re x * x; }
template <class T> T gcd (T a, T b) { re a ? gcd (b % a, a) : b; }
template <class T> int sgn (T x) { re x > 0 ? 1 : (x < 0 ? -1 : 0); }

#define filename ""

const D pi = acos(-1.);
const int N = 3e5 + 20;
const int mod = 998244353;
const int root = 15311432;
const int revroot = 469870224;

ll power (ll x, ll y = mod - 2) {
	ll ans = 1;
	while (y) {
		if (y & 1) ans = ans * x % mod;
		x = x * x % mod;
		y >>= 1;
	}
	re ans;
}

void fft (vll& a, vi& rev, int p, int inv) {
	int n = 1 << p;
	for (int i = 1; i < n; i++) 
		if (rev[i] > i) 
			swap (a[i], a[rev[i]]);
	for (int len = 1; len < n; len <<= 1) {
		ll w = inv ? revroot : root;
		w = power (w, (1 << 22) / len);
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

void init_rev (vi& rev, int p) {
	rev.resize(1 << p);
	for (int i = 1; i < (1 << p); i++) 
		rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (p - 1));
}

void fft (vll& a, int p, int inv) {
	vi rev;
	init_rev(rev, p);
	fft (a, rev, p, inv);
}

void mult (vll& a, vll& b, int p) {
	vi rev;
	init_rev(rev, p);
	fft (a, rev, p, 0);
	fft (b, rev, p, 0);
	for (int i = 0; i < (1 << p); i++)
		a[i] = a[i] * b[i] % mod;
	fft (a, rev, p, 1);
}

vll vinv (vll a, int n) {
	vll ans (2 * n);
	ans[0] = power(a[0]);
	for (int l = 1; (1 << l) <= n; l++) {
		int len = (1 << l);
		vll tmp (2 * len);
		for (int i = 0; i < min(len, sz(a)); i++) tmp[i] = a[i];
		vi rev;
		init_rev(rev, l + 1);
		fft (ans, rev, l + 1, 0); 
		fft (tmp, rev, l + 1, 0);
		for (int i = 0; i < 2 * len; i++) { 
			tmp[i] = (mod + 2 - tmp[i] * ans[i] % mod) % mod;
			ans[i] = ans[i] * tmp[i] % mod;
		}
		fft (ans, rev, l + 1, 1);
		fill (ans.begin() + len, ans.end(), 0);
	}
	re ans;
}

vll vlg (vll a, int n) {
	vll ans = vinv (a, n);	
	vll tmp (2 * n);
	for (int i = 0; i < min(n, sz(a)) - 1; i++) tmp[i] = a[i + 1] * (i + 1) % mod;
	int p = __builtin_ctz(n) + 1;
	mult (ans, tmp, p);
	for (int i = 2 * n; i; i--) ans[i] = (i >= n) ? 0 : ans[i - 1] * power(i) % mod;
	ans[0] = 0;
	re ans;
}

vll vex (vll a, int n) {
	vll ans (2 * n);
	ans[0] = 1;
	for (int l = 1; (1 << l) <= n; l++) {
		int len = (1 << l);
		vll tmp = vlg (ans, len);
		for (int i = 0; i < len; i++) tmp[i] = ((i < sz(a) ? a[i] : 0) + mod - tmp[i]) % mod;
		tmp[0]++;
		mult (ans, tmp, l + 1);
		fill (ans.begin() + len, ans.end(), 0);
	}					                     	
	re ans;
}

vll vdeg (vll a, int n, ll num, ll denum = 1) {
	vll ans = vlg (a, n);
	ll k = num * power(denum) % mod;
	for (int i = 0; i < n; i++) ans[i] = k * ans[i] % mod;
	ans = vex (ans, n);	
	re ans;
}

int get_deg (int n) {
	re n ? (32 - __builtin_clz(n - 1)) : 0;
}

class poly {
	public:
		vll p;	
		poly () {}
		poly (int s) { p.resize(s); }
		poly (const vll& a) {
			 p = a;
		}
		void resize (int n) {
			p.resize(n);
		}
		int size() const {
			re sz(p);
		}
		poly inv (int n) const {
			int m = 1 << get_deg(n);
			vll ans = vinv(p, m);
			ans.resize(n);
			re poly(ans);
		}
		poly lg (int n) const {
			int m = 1 << get_deg(n);
			vll ans = vlg(p, m);
			ans.resize(n);
			re poly(ans);
		}
		poly ex (int n) const {
			int m = 1 << get_deg(n);
			vll ans = vex(p, m);
			ans.resize(n);
			re poly(ans);
		}
		poly deg (int n, ll num, ll denum = 1) const {
			int m = 1 << get_deg(n);
			vll ans = vdeg(p, m, num, denum);
			ans.resize(n);
			re poly(ans);
		}
		vll get (const vll& x) const;
};

poly operator+(const poly& a, const poly& b) {
	poly ans;
	ans.resize(max(sz(a), sz(b)));
	for (int i = 0; i < sz(ans); i++) {
		if (i < sz(a)) ans.p[i] = (ans.p[i] + a.p[i]) % mod;
		if (i < sz(b)) ans.p[i] = (ans.p[i] + b.p[i]) % mod;
	}
	while (sz(ans.p) > 1 && ans.p.back() == 0) ans.p.pop_back();
	re ans;
}

poly operator-(const poly& a, const poly& b) {
	poly ans;
	ans.resize(max(sz(a), sz(b)));
	for (int i = 0; i < sz(ans); i++) {
		if (i < sz(a)) ans.p[i] = (ans.p[i] + a.p[i]) % mod;
		if (i < sz(b)) ans.p[i] = (mod + ans.p[i] - b.p[i]) % mod;
	}
	while (sz(ans.p) > 1 && ans.p.back() == 0) ans.p.pop_back();
	re ans;
}

poly operator*(const poly& a, const ll& b) {
	poly ans = a;
	for (auto& x: ans.p) x = x * b % mod;
	re ans;	
}

poly operator*(const poly& a, const poly& b) {
	vll x = a.p;
	vll y = b.p;
	if (sz(x) < sz(y)) swap(x, y);
	if (sz(y) < 10) {
		vll ans (sz(x) + sz(y) - 1);
		for (int i = 0; i < sz(x); i++)
			for (int j = 0; j < sz(y); j++)
				ans[i + j] = (ans[i + j] + x[i] * y[j]) % mod;
		while (sz(ans) > 1 && ans.back() == 0) ans.pop_back();
		re poly(ans);				 
	}
	int p = get_deg(sz(x) + sz(y) - 1);
	x.resize(1 << p);
	y.resize(1 << p);
	vi rev;
	init_rev(rev, p);
	fft (x, rev, p, 0);
	fft (y, rev, p, 0);
	for (int i = 0; i < (1 << p); i++)
		x[i] = x[i] * y[i] % mod;
	fft (x, rev, p, 1);
	while (sz(x) > 1 && x.back() == 0) x.pop_back();
	re poly(x);
}

poly operator/(const poly& a, const ll& x) {
	vll ans(sz(a) - 1);
	ll y = a.p.back();
	for (int i = sz(a.p) - 2; i >= 0; i--) {
		ans[i] = y;
		y = (y * x + a.p[i]) % mod;
	}
	re poly(ans);
}

poly operator/(const poly& a, const poly& b) {
	if (sz(b) == 2 && b.p[1] == 1) {
		ll x = (mod - b.p[0]) % mod;
		re a / x;
	}
	int n = sz(a) - 1;
	int m = sz(b) - 1;
	if (n < m) re poly({0});
	poly ans = b;
	reverse(all(ans.p));
	ans = ans.inv(n - m + 1);
	poly tmp = a;
	reverse(all(tmp.p)), tmp.resize(n - m + 1); 
	tmp = tmp * ans;
	tmp.resize(n - m + 1);
	reverse (all(tmp.p));
	while (sz(tmp.p) > 1 && tmp.p.back() == 0) tmp.p.pop_back();
	re tmp;
}

poly operator%(const poly& a, const poly& b) {
	poly ans = a / b;
	ans = ans * b;
	ans = a - ans;
	while (sz(ans.p) > 1 && ans.p.back() == 0) ans.p.pop_back();
	re ans;
}

vll poly::get (const vll& x) const {
	int n = sz(x);
	vll ans(n);
	vector<poly> t(2 * n);
	for (int i = 0; i < n; i++) {
		ll z = (mod - x[i]) % mod;
		t[n + i] = poly({z, 1});
	}
	for (int i = n - 1; i > 1; i--)
		t[i] = t[i << 1] * t[i << 1 | 1];
	t[1] = *this;
	for (int i = 1; i < n; i++) {
		t[i << 1] = t[i] % t[i << 1];	
		t[i << 1 | 1] = t[i] % t[i << 1 | 1];	
	}
	for (int i = 0; i < n; i++) 
		ans[i] = t[i + n].p[0];
	t.clear();
	re ans;
}

poly interpolate (vii& a) {
    poly cur(1);
    cur.p[0] = 1; 
    for (int i = 0; i < sz(a); i++) {
    	auto tmp = poly({(mod - a[i].fi) % mod, 1});
    	cur = cur * tmp;
    }
    poly ans;
    for (int k = 0; k < sz(a); k++) {
    	ll x = a[k].fi;
    	poly tmp = cur / x;
    	ll z = 1;
    	for (int i = 0; i < sz(a); i++)
			if (i != k) 
				z = z * (mod + x - a[i].fi) % mod;
		z = a[k].se * power(z) % mod;
		tmp = tmp * z;
		ans = ans + tmp;	
	}	
	re ans;
}

poly massey (vll& a) {
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
	re poly(ans);
}

poly gen_rec (vll& a, int n) {
	poly cur = massey(a);
	vll nu(sz(cur) - 1);
	for (int i = 0; i < sz(cur) - 1; i++)
		nu[i] = a[i];
	poly ans(nu);
	ans = ans * cur;
	ans.resize(sz(cur) - 1);
	cur = cur.inv(n);
	re ans * cur;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	
}
