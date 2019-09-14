const int N = 2e5 + 100;

int in[N], out[N], s[N], nxt[N], pr[N];
vi e, g[N];
int up[N][25];
int t[4 * N];

void dfs(int v) {
	s[v] = 1;
	for (int i = 0; i < sz(g[v]); i++)
		if (g[v][i] != pr[v]) {
		    int to = g[v][i];
		    up[to][0] = pr[to] = v;
		    for (int j = 1; j < 25; j++)
		    	if (up[to][j - 1] != -1)
		    		up[to][j] = up[up[to][j - 1]][j - 1];
		    dfs(to);
		    s[v] += s[to];
			if (g[v][0] == pr[v] || s[to] > s[g[v][0]])
				swap(g[v][i], g[v][0]);
		}
}									     

void hld(int v) {
	if (pr[v] == -1) nxt[v] = v;
	in[v] = sz(e);
	e.pb(v);
	for (auto x : g[v])
		if (x != pr[v]) {
			if (2 * s[x] >= s[v]) nxt[x] = nxt[v];
			else nxt[x] = x;
			hld(x);
		}
	out[v] = sz(e) - 1;
}	 					 

bool ok(int x, int y) {
	re (in[x] <= in[y] && out[x] >= out[y]);
}

int lca(int x, int y) {
	if (ok(x, y)) re x;
	if (ok(y, x)) re y;
	for (int i = 24; i >= 0; i--) {
		if (up[x][i] == -1) continue;
		if (!ok(up[x][i], y)) x = up[x][i];
	}
	re up[x][0];
}	


int jump(int x, int p) {
	int ans = -inf;
	while (in[nxt[x]] > in[p]) {
		ans = max(ans, get(in[nxt[x]], in[x]));
		x = pr[nxt[x]];
	}
	re max(ans, get(in[p], in[x]));
}

int query (int x, int y) {
	int z = lca (x, y);
	re max (jump(x, z), jump(y, z));
}

int main()
{
	memset(up, -1, sizeof(up));
	pr[0] = -1;
	dfs(0);
	hld(0);	
	
}