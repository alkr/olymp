vi g[N];
int s, t;
int pr[N], d[N], p[N];

struct edge {
	int fr, to, c, f;
};
vector<edge> e;

void make(int a, int b, int c, int f) {
	g[a].pb(sz(e));
	g[b].pb(sz(e) + 1);
	e.pb({a, b, c, f});
	e.pb({b, a, -c, 0});
}

bool comp(int a, int b) {
	if (d[a] == d[b]) re a < b;
	re d[a] < d[b];
}

ii go() {
	memset(pr, -1, sizeof(pr[0]) * (t + 1));
	for (int i = 0; i <= t; i++) {
		p[i] = min(inf, p[i] + d[i]);
		d[i] = inf;
	}
	set<int, bool(*)(int, int)> st(comp);
	d[s] = 0;
	st.insert(s);
	while (!st.empty()) {
	    int best = *st.begin();
	    st.erase(best);
		for (auto x : g[best]) 
			if (e[x].f > 0 && d[e[x].to] > d[best] + p[best] + e[x].c - p[e[x].to]) {
			    if (st.count(e[x].to)) st.erase(e[x].to);
				d[e[x].to] = d[best] + p[best] + e[x].c - p[e[x].to];
				st.insert(e[x].to);
				pr[e[x].to] = x;
			}
	}
	if (d[t] == inf) re {0, 0};
	int cur = t;
	int flow = inf;
	while (pr[cur] != -1) {
		flow = min(flow, e[pr[cur]].f);
		cur = e[pr[cur]].fr;
	}
	cur = t;
	while (pr[cur] != -1) {
		e[pr[cur]].f -= flow;
		e[pr[cur] ^ 1].f += flow;
		cur = e[pr[cur]].fr;
	}
	re {flow, flow * (d[t] + p[t])};
}		



ii go() {
	for (int i = 0; i <= t; i++) 
		d[i] = inf, in[i] = 0, pr[i] = -1;
	d[s] = 0;
	int l = 0;
	int r = 1;
	q[0] = s;
	while (l < r) {
		int best = q[l++];
		in[best] = 0;
		for (auto x : g[best]) 
			if (e[x].f && d[e[x].to] > d[best] + e[x].c) {
				d[e[x].to] = d[best] + e[x].c;
				pr[e[x].to] = x;
				if (!in[e[x].to]) { 
					in[e[x].to] = 1;
					q[r++] = e[x].to;
				}
			}
	}	                  
	if (d[t] == inf) re {0, 0};
	int cur = t;
	int flow = inf;
	while (pr[cur] != -1) {
		flow = min(flow, e[pr[cur]].f);
		cur = e[pr[cur]].fr;
	}
	cur = t;
	while (pr[cur] != -1) {
		e[pr[cur]].f -= flow;
		e[pr[cur] ^ 1].f += flow;
		cur = e[pr[cur]].fr;
	}
	re {flow, flow * d[t]};
}		
	