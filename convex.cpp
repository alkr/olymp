#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace __gnu_pbds;
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

template <class T> using _tree = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
template <class T> T abs (T x) { re x > 0 ? x : -x; }
template <class T> T sqr (T x) { re x * x; }
template <class T> T gcd (T a, T b) { re a ? gcd (b % a, a) : b; }
template <class T> int sgn (T x) { re x > 0 ? 1 : (x < 0 ? -1 : 0); }

#define filename ""

const int N = 2e5 + 20;
const int inf = 1e9 + 1;

struct point {
	int x, y;
} a[N];

bool operator<(const point& a, const point& b) {
	if (a.x == b.x) re a.y < b.y;
	re a.x < b.x;
}
             
ll vec(point& a, point& b, point& c, point& d) {
	re (b.x - a.x) * (d.y - c.y) - (b.y - a.y) * (d.x - c.x);
}

ll dist(point& a, point& b) {
	re sqr(a.x - b.x) + sqr(a.y - b.y);
}

ll diam(vector<point>& p)
{
	ll res = 0;
	int n = sz(p);
	for (int i = 0, j = (n < 2) ? 0 : 1; i < j; ++i)
    	for (;; j = (j + 1) % n) {
      		res = max(res, dist(p[i], p[j]));
      		if (vec(p[i], p[i + 1], p[j], p[(j + 1) % n]) >= 0)  break;
    	}
	re res;
}

int main () {
	int n;
	cin >> n;
    for (int i = 0; i < n; i++) {
    	int x, y;
    	cin >> x >> y;
    	a[i] = {x, y};
	}
	sort(a, a + n);
	vector<point> fi, se;
	for (int i = 0; i < n; i++) {
		while (sz(fi) > 1 && vec(fi[sz(fi) - 2], fi.back(), fi.back(), a[i]) >= 0) fi.pop_back();
		while (sz(se) > 1 && vec(se[sz(se) - 2], se.back(), se.back(), a[i]) <= 0) se.pop_back();
		fi.pb(a[i]); se.pb(a[i]);
	}

	for (int i = sz(se) - 2; i > 0; i--) fi.pb(se[i]);
	cout << sqrt((D) diam(fi));
	re 0;	                   
}