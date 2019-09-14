int n, m;
int p[N];
int timer = 1;
int was[N];
vi g[N];

bool go (int v) {
	was[v] = timer;
	for (auto x : g[v]) 
		if (p[x] == -1) {
			p[x] = v;
			p[v] = x;
			re true;
		}
	for (auto x : g[v]) {
		int y = p[x];
		if (was[y] < timer && go(y)) {
			p[x] = v;
			p[v] = x;
			re true;
		}
	}
	re false;
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0); cout.tie(0);
	memset(p, -1, sizeof(p));
	int k;
	cin >> n >> m >> k;
	for (int i = 0; i < k; i++) {
		int x, y;
		cin >> x >> y;
		x--; y += n - 1;
		g[x].pb(y);
		g[y].pb(x);
	}	
	int ans = 0;
	while (1) {
	 	timer++;
	 	bool ok = false;
	 	for (int i = 0; i < n; i++) 
	 		if (p[i] == -1 && go(i)) { ok = true; ans++; }
		if (!ok) break;
	}
	cout << ans << endl;
	for (int i = 0; i < n; i++)
		if (p[i] != -1) cout << i + 1 << " " << p[i] - n + 1 << endl;
}
