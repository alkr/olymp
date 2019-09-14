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
const int N = 5e2 + 20;
const int inf = 1e9 - 1;

int n, m, s, t;
vi g[N];
int was[N];
int timer = 1;

struct edge {
	int fr, to, f;
};

vector<edge> e;

void make (int a, int b, int c) {
	g[a].pb(sz(e));
	e.pb({a, b, c});
	g[b].pb(sz(e));
	e.pb({b, a, 0});
}                  

int go (int v, int z, int flow = inf) {
	was[v] = timer;
	if (v == t) re flow;
	for (auto i : g[v])
		if (e[i].f >= z && was[e[i].to] != timer) {
			int push = go (e[i].to, z, min (flow, e[i].f));
			if (push) {
				e[i].f -= push;
				e[i^1].f += push;
				re push;
			}
		}
	re 0;
}

ll get() {	
	ll flow = 0;
	for (int i = inf; i; i /= 2, timer++) {
		int tmp = 0;
		while (tmp = go(s, i)) {
			flow += tmp;
			timer++;	
		}
	}	
	re flow;
}

bool comp (int a, int b) {
	re e[a].f > e[b].f;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	cin >> n >> m;
	t = n - 1;
	for (int i = 0; i < m; i++) {
		int x, y, z;
		cin >> x >> y >> z;
		x--; y--;
		make (x, y, z);
	}
	for (int i = 0; i < n; i++)
		sort (all(g[i]), comp);
	cout << get();	
}
