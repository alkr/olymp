struct node {
	int pr, val, cnt;
	node* left, * right;
	node (int x){
		cnt = 1;
		val = x;
		pr = rand() | (rand() << 15);
		left = right = 0;
	}
};

inline int func(node* t) {
	if (!t) re 0;
	else re t->cnt;
}

inline void upd(node* t) {
	if (t) t->cnt = 1 + func(t->left) + func(t->right);
}

void merg(node*& t, node* l, node* r) {
	if (!l || !r) { t = l ? l : r; re; }
	if (l->pr > r->pr)
		merg (l->right, l->right, r), t = l, upd(t);
	else 
		merg (r->left, l, r->left), t = r, upd(t);
}

void split(node* t, node*& l, node*& r, int pos, int cur = 0) {
	if (!t) { l = r = 0; re; }
	int k = cur + func(t->left);
	if (k >= pos)
		split (t->left, l, t->left, pos, cur), r = t, upd(r);
	else 
		split (t->right, t->right, r, pos, k + 1), l = t, upd(l);
}

void in (node*& t, node* x, int pos, int cur = 0) {
	if (!t) { t = x; re; }
	if (t->pr < x->pr) {
		split (t, x->left, x->right, pos, cur);
		upd(x); t = x;
		re;
	}
	int k = func(t->left) + cur;
	if (k >= pos) in (t->left, x, pos, cur);
	else in (t->right, x, pos, k + 1);
	upd(t);
}

void insert (node*& t, int x, int pos) {
	node* r = new node(x);
	in (t, r, pos);
}

void del(node*& t, int pos, int cur = 0) {
	int k = cur + func(t->left);
	if (k == pos) {
		merg (t, t->left, t->right);
		re;
	}
	if (k > pos) del (t->left, pos, cur);
	else del (t->right, pos, k + 1);
	upd(t);
}

int get (node* t, int pos, int cur = 0) {
	int k = func(t->left) + cur;
	if (k == pos) re t->val;
	if (k > pos) re get(t->left, pos, cur);
	else re get(t->right, pos, k + 1);
}
 