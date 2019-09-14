#include <bits/stdc++.h>

using namespace std;

#define pb push_back
#define sz(x) ((int)x.size ())
#define all(x) (x).begin(), (x).end()
#define re return

typedef long long ll;
typedef vector <ll> vll;

const ll inf = 1e10 + 7;

ll n;

ll mul (ll x, ll y, ll mod) {
	ll ans = 0;
	while (y) {
		if (y & 1) ans = (ans + x) % mod;
		x = (x + x) % mod;
		y >>= 1;
	}
	re ans;
}

ll power (ll x, ll p, ll mod) {
	ll ans = 1 % mod;
	while (p) {
	 	if (p & 1) ans = mul (ans, x, mod);
	 	x = mul (x, x, mod);
	 	p /= 2;
	}
	re ans;
}

ll myrand() {
	ll a = rand() + (rand() << 15);
	re rand() + (rand() << 15) + (a << 30);
}

bool get (ll s, ll d, ll n) {
	ll a = 1 + myrand() % (n - 1);
	if (power (a, n - 1, n) != 1) re false;
	a = power (a, d, n);
	if (a == 1) re true;
	for (int i = 0; i < s; i++) {
		if (a == n - 1) re true;
		a = mul (a, a, n);
	}
	re false;
}

bool is_prime (ll n) {
	ll s = 0, d = n - 1;
	while (d % 2 == 0) { s++; d /= 2; }
	for (int i = 0; i < 10; i++)
		if (!get (s, d, n)) re false;
	re true;
}

ll func (ll x, ll n) {
	re (mul (x, x, n) + 1) % n;
}

void go (ll n, vll& ans) {
	if (n < inf) {
		for (ll j = 2; j * j <= n; j++)
			while (n % j == 0) {
				ans.pb(j);
				n /= j;
			}
	  	if (n > 1) ans.pb(n);
	  	re;
	}
	if (is_prime(n)) { ans.pb(n); re; }
	ll x = 1 + rand() % (n - 1);
	ll y = x;
	ll d = 1;
	while (d == 1) {
		x = func (x, n);
		y = func (func (y, n), n);
		d = (n + y - x) % n;
		d = __gcd(d, n);
	}
	go (d, ans);
	go (n / d, ans);
}

vll fact (ll n) {
	vll ans;
	go (n, ans);
//	sort (all(ans));
	re ans;
}

int main() {
	srand(time(0));
	cin >> n;
	auto ans = fact (n);
}
