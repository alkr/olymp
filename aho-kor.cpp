int to[N][26];
int gt[N][26];
int link[N], pr[N];
int pc[N], ok[N];
int cnt = 1;

void add(string& s) {
	int cur = 0;
	for (auto x : s) {
		int p = (int) (x - 'a');
		if (to[cur][p] == -1) {
			to[cur][p] = cnt++;
			gt[cur][p] = cnt - 1;
			pr[cnt - 1] = cur;
			pc[cnt - 1] = p;
		}
		cur = to[cur][p];
	}
	ok[cur] = 1;
}

int go(int v, int c) {
	if (gt[v][c] != -1) re gt[v][c];
	if (!v) re 0;
	re gt[v][c] = go(link[v], c);
}

void make() {
	queue<int> q;
	q.push(0);
	while (!q.empty()) {
		int best = q.front();
		q.pop();
		if (best && pr[best]) 
			link[best] = go(link[pr[best]], pc[best]); 
		ok[best] |= ok[link[best]];
		for (int i = 0; i < 26; i++)
			if (to[best][i] != -1) 
				q.push(to[best][i]);
	}
}
        
int main() {
	cin >> s;
	for (auto x : s) add(x);
	make(0);
}