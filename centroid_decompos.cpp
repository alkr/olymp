//#pragma GCC optimize("Ofast")
//#pragma GCC target("avx")
//#pragma GCC optimize ("unroll-loops")
int n, m;
vi g[N], cd[N];
int s[N], lev[N];
int d[25][N];

void getcen(int v, int size, int& c, int pr = -1) {
	s[v] = 1;
	int big = -1;
	for (auto x : g[v])
		if (lev[x] == - 1 && x != pr) {
			getcen(x, size, c, v);
			s[v] += s[x];
			big = max(big, s[x]);
		}
	if (2 * big < size && (pr == -1 || 2 * s[v] >= size)) c = v;
}

void make(int v, int level, int pr = -1) {
	for (auto x : g[v]) 
		if (x != pr && lev[x] == -1) {
			d[level][x] = d[level][v] + 1;
			make(x, level, v);
		}
}

void build(int v, int size, int level = 0, int last = -1) {
	int c = -1;
	getcen(v, size, c);
	make(c, level);
	if (last != -1) cd[last].pb(c);
	lev[c] = level;
	for (auto x : g[c])
		if (lev[x] == -1) {
			if (s[x] < s[c]) build(x, s[x], level + 1, c);
			else build (x, size - s[c], level + 1, c);
		}
}

int timer = 0;
int up[N][5];
int in[N], out[N];

void dfs(int v) {
	in[v] = timer++;
	for (auto x : cd[v]) {
		dfs(x);	
		up[x][0] = v;
		for (int i = 1; i < 5; i++)	
			if (up[x][i - 1] != -1) 
				up[x][i] = up[up[x][i - 1]][i - 1];
	}
	out[v] = timer - 1;
}			 	

bool ok(int a, int b) {
	re (in[a] <= in[b] && out[b] <= out[a]);
}

int lca(int a, int b) {
	if (ok(a, b)) re a;
	if (ok(b, a)) re b;
	for (int i = 4; i >= 0; i--) {
		if (up[a][i] == -1) continue;
		if (!ok(up[a][i], b)) a = up[a][i];
	}
	re up[a][0];
}

int dist(int a, int b) {
 	int cur = lca(a, b);
 	re d[lev[cur]][a] + d[lev[cur]][b];
}

int main() {
    memset(lev, -1, sizeof(lev));
    memset(up, -1, sizeof(up));
	cin >> n;
	for (int i = 0; i < n - 1; i++) {
		int x, y;
		scanf("%d%d", &x, &y);
		x--; y--;
		g[x].pb(y);
		g[y].pb(x);
	}
	build(1, n);
	int root = -1;
	for (int i = 0; i < n; i++) 
		if (lev[i] == 0) 
			root = i;
	dfs(root); 
}