int n;
int cnt = 1, cur, pos;
map<char, int> to[N];
int len[N], f[N], link[N];
string s;

int make (int _pos, int _len) {
	len[cnt] = _len;
	f[cnt] = _pos;
	re cnt++;
}

void add (char c) {
	n++;
	pos++;
	int last = 0;
	while (pos) {
		while (pos > len[to[cur][s[n - pos]]]) {
			cur = to[cur][s[n - pos]];
			pos -= len[cur];
		}
		int& v = to[cur][s[n - pos]];
		if (!v) {
			v = make(n - pos, inf);
			link[last] = cur;
			last = 0;
		} else {
			char t = s[f[v] + pos - 1];
			if (t == c) {
				link[last] = cur;
				return;
			}
			int u = make(f[v], pos - 1);
			to[u][c] = make(n - 1, inf);
			to[u][t] = v;
			f[v] += pos - 1;
			len[v] -= pos - 1;
			v = u;
			link[last] = u;
			last = u;
		}
		if (cur) cur = link[cur];
		else pos--;
	}
}

int main () {
	len[0] = inf;
	cin >> s;
	for (auto x : s) add(x);
}