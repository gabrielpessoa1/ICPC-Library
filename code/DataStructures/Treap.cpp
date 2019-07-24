typedef struct item * pitem;
struct item {
	int prior, value, cnt; 
	bool rev;
	pitem l, r;
};

int cnt (pitem it) { return it ? it->cnt : 0; };

void upd_cnt (pitem it) {
	if (it) it->cnt = cnt(it->l) + cnt(it->r) + 1;
}

void push (pitem it) {
	if (it && it->rev) {
		it->rev = false;
		swap (it->l, it->r);
		if (it->l)  it->l->rev ^= true;
		if (it->r)  it->r->rev ^= true;
	}
}

void merge (pitem & t, pitem l, pitem r) {
	push (l), push (r);
	if (!l || !r) t = l ? l : r;
	else if (l->prior > r->prior)
		merge (l->r, l->r, r),  t = l;
	else
		merge (r->l, l, r->l),  t = r;
	upd_cnt (t);
}

void split (pitem t, pitem & l, pitem & r, int key) {
	if (!t) return void( l = r = 0 );
	push (t);
	int cur_key = cnt(t->l); // t->key if not implicit
	if (key <= cur_key)
		split (t->l, l, t->l, key),  r = t;
	else
		split (t->r, t->r, r, key - (1 + cnt(t->l))),  l = t;
	upd_cnt (t);
}

void reverse (pitem t, int l, int r) {
	pitem t1, t2, t3;
	split (t, t1, t2, l);
	split (t2, t2, t3, r-l+1);
	t2->rev ^= true;
	merge (t, t1, t2);
	merge (t, t, t3);
}

pitem unite (pitem l, pitem r) {
	if (!l || !r) return l ? l : r;
	if (l->prior < r->prior)  swap (l, r);
	pitem lt, rt;
	split (r, lt, rt, l->key);
	l->l = unite (l->l, lt);
	l->r = unite (l->r, rt);
	return l;
}
