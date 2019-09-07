mt19937 rng ((int) chrono::steady_clock::now().time_since_epoch().count());

typedef int Key;
typedef struct item * pitem;

struct item {
  item () {}
  item (Key k) {
    key = k;
    prio = uniform_int_distribution<int>() (rng);
    cnt = 1;
    rev = 0;
    l = r = NULL;
  }
  pitem l, r;
  Key key;
  int prio;
  int cnt;
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
    if (!it) return;
    if (it->rev) {
        it->rev = false;
        swap (it->l, it->r);
        if (it->l)  it->l->rev ^= true;
        if (it->r)  it->r->rev ^= true;
    }
}

void merge (pitem & t, pitem l, pitem r) {
  pushLazy (l);
  pushLazy (r);
  if (!l || !r)
    t = l ? l : r;
  else if (l->prio > r->prio)
    merge (l->r, l->r, r),  t = l;
  else
    merge (r->l, l, r->l),  t = r;
  fix (t);
}

void split (pitem t, pitem & l, pitem & r, int key, int add = 0) {
  if (!t)
    return void( l = r = 0 );
  pushLazy (t);
  int cur_key = add + cnt(t->l);
  if (key <= cur_key)
    split (t->l, l, t->l, key, add),  r = t;
  else
    split (t->r, t->r, r, key, add + 1 + cnt(t->l)),  l = t;
  fix (t);
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
