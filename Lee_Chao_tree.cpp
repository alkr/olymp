int vis[N << 2];
          
struct line {
    ll k, b;
    int num;
    line(ll _k = 0, ll _b = 0, int _num = 0) {
        k = _k; b = _b; num = _num;
    }
    ll get(ll x) {
        return k * x + b;
    }
} t[N << 2];

void modify(int v, int tl, int tr, line x)
{
	if (!vis[v]) { t[v] = x; vis[v] = 1; re; }
	if (t[v].get(tl) >= x.get(tl) && t[v].get(tr) >= x.get(tr)) re;
	if (t[v].get(tl) <= x.get(tl) && t[v].get(tr) <= x.get(tr)) { t[v] = x; re; }
	int c = (tl + tr) >> 1;
	if (t[v].get(tl) < x.get(tl)) swap(t[v], x);
	if (t[v].get(c) <= x.get(c)) { swap(t[v], x); modify(2 * v + 1, tl, c, x); }
	else modify(2 * v + 2, c + 1, tr, x); 
}

pair<ll, int> get(int v, int tl, int tr, int pos)
{
	if (!vis[v]) re {-inf, 0};
	pair<ll, int> ans = {t[v].get(pos), t[v].num};
	if (tl == tr) re ans;
	int c = (tl + tr) >> 1;
	if (pos > c) re max(ans, get(2 * v + 2, c + 1, tr, pos));
	else re max(ans, get(2 * v + 1, tl, c, pos));
}
