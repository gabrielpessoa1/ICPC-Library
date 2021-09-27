mt19937 rng ((int) chrono::steady_clock::now().time_since_epoch().count());
typedef int Value;
typedef struct item * pitem;
struct item {
  item () {}
  item (Value v) { // add key if not implicit
    value = v;
    prio = uniform_int_distribution<int>() (rng);
    cnt = 1;
    rev = 0;
    l = r = 0;
  }
  pitem l, r;
  Value value;
  int prio, cnt;
  bool rev;
};
int cnt (pitem it) {
  return it ? it->cnt : 0;
}
void fix (pitem it) {
  if (it)
    it->cnt = cnt(it->l) + cnt(it->r) + 1;
}
void pushLazy (pitem it) {
  if (it && it->rev) {
    it->rev = false;
    swap(it->l, it->r);
    if (it->l)  it->l->rev ^= true;
    if (it->r)  it->r->rev ^= true;
  }
}
void insert (pitem & t, pitem it) {
  if (!t)
    t = it;
  else if (it->prio > t->prio)
    split (t, it->key, it->l, it->r),  t = it;
  else
    insert (t->key <= it->key ? t->r : t->l, it);
}
void merge (pitem & t, pitem l, pitem r) {
  pushLazy (l); pushLazy (r);
  if (!l || !r) t = l ? l : r;
  else if (l->prio > r->prio)
    merge (l->r, l->r, r),  t = l;
  else
    merge (r->l, l, r->l),  t = r;
  fix (t);
}
void erase (pitem & t, int key) {
  if (t->key == key) {
    pitem th = t;
    merge (t, t->l, t->r);
    delete th;
  }
  else
    erase (key < t->key ? t->l : t->r, key);
}
void split (pitem t, pitem & l, pitem & r, int key) {
  if (!t) return void( l = r = 0 );
  pushLazy (t);
  int cur_key = cnt(t->l); // t->key if not implicit
  if (key <= cur_key)
    split (t->l, l, t->l, key),  r = t;
  else
    split (t->r, t->r, r, key - (1 + cnt(t->l))),  l = t;
  fix (t);
}
void reverse (pitem t, int l, int r) {
  pitem t1, t2, t3;
  split (t, t1, t2, l);
  split (t2, t2, t3, r-l+1);
  t2->rev ^= true;
  merge (t, t1, t2);
  merge (t, t, t3);
}
void unite (pitem & t, pitem l, pitem r) {
  if (!l || !r) return void ( t = l ? l : r );
  if (l->prio < r->prio)  swap (l, r);
  pitem lt, rt;
  split (r, lt, rt, l->key);
  unite (l->l, l->l, lt);
  unite (l-> r, l->r, rt);
  t = l;
}
pitem kth_element(pitem t, int k) {
	if(!t) return NULL;
	if(t->l) {
		if(t->l->size >= k) return kth_element(t->l, k);
		else k -= t->l->cnt;
	}
	return (k == 1) ? t : kth_element(t->r, k - 1);
}
int countLeft(pitem t, int key) {
	if(!t) {
		return 0;
	} else if(t->key < key) {
		return 1 + (t->l ? t->l->size : 0) + countLeft(t->r, key);
	} else {
		return countLeft(t->l, key);
	}
}

