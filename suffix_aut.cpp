map<char, int> to[N];
int len[N], link[N];
int last, cnt = 1;

void add (char c) {
	int cur = cnt++;
	len[cur] = len[last] + 1;
	int p = last;
	last = cur;
	for (; p != -1; p = link[p]) {
		if (to[p].count(c)) break;
		to[p][c] = cur;
	}
	if (p == -1) {
		link[cur] = 0;
		return;
	}
	int q = to[p][c];
	if (len[p] + 1 == len[q]) {
		link[cur] = q;
		return;
	}
	int clone = cnt++;
	to[clone] = to[q];
	link[clone] = link[q];
	len[clone] = len[p] + 1;
	link[cur] = link[q] = clone;
	for (; p != -1 && to[p][c] == q; p = link[p]) {
		to[p][c] = clone;
	}
}

int main() {
	link[0] = -1;
	re 0;
}


/*
void add (int c) {
	int cur = cnt++;
	len[cur] = len[last] + 1;
	int p = last;
	last = cur;
	for (; p != -1 && !to[p][c]; p = link[p]) to[p][c] = cur;
	if (p == -1) { link[cur] = 0; re; }
	int q = to[p][c];
	if (len[q] == len[p] + 1) { link[cur] = q; re; }
	int clone = cnt++;
	for (int i = 0; i < 26; i++) to[clone][i] = to[q][i];
	link[clone] = link[q];
	len[clone] = len[p] + 1;
	link[q] = link[cur] = clone;
	for (; p != -1 && to[p][c] == q; p = link[p]) to[p][c] = clone;
}
*/	