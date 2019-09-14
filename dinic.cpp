int n, m, s, t;
vi g[N];
int was[N], d[N], w[N];
int timer = 1;

struct edge{
	int fr, to, f;
};

vector<edge> e;

void make(int a, int b, int f)
{
	g[a].pb(sz(e));
	g[b].pb(sz(e) + 1);
	e.pb({a, b, f});
	e.pb({b, a, 0});
}

bool bfs() {
	for (int i = 0; i <= t; i++)
		d[i] = -1;
	d[s] = 0;   	
	w[0] = s;
	int cnt = 0;
	int last = 1;
	while (cnt < last){
		int q = w[cnt++];
		for (auto i : g[q]) 
			if (d[e[i].to] == -1 && e[i].f) {
				d[e[i].to] = d[q] + 1;
				w[last++] = e[i].to;
			}
	}
	re d[t] != -1;
}

int dfs(int v, int flow = inf) {
	was[v] = timer;
	if (v == t) re flow;
	for (auto i : g[v]) {
		if (d[e[i].to] - 1 == d[v] && e[i].f && was[e[i].to] != timer) {
			int push = dfs(e[i].to, min(flow, e[i].f));
			if (push) {
				e[i].f -= push;
				e[i ^ 1].f += push;
				re push;
			}
		}
	}
	re 0;
}

int get()
{	
	int flow = 0;
	while (bfs()) {
		timer++;
		for (;;) {
			was[s] = was[t] = 0;
			int k = dfs(s);
			if (!k) break;
			flow += k;
		}
	}
	re flow;
}