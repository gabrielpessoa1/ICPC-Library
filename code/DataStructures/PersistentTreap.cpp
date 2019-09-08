mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
 
typedef int Key;
struct Treap {
  Treap(){}
  Treap(char k) {
    key = 1;
    size = 1;
    l = r = NULL;
    val = k;
  }
  
  Treap *l, *r;
  Key key;
  char val;
  int size;
};
 
typedef Treap * PTreap;
 
bool leftSide(PTreap l, PTreap r) {
  return (int) (rng() % (l->size + r->size)) < l->size;
}
 
void fix(PTreap t) {
  if (t == NULL) {
    return;
  }
  t->size = 1;
  t->key = 1;
  if (t->l) {
    t->size += t->l->size;
    t->key += t->l->size;
  }
  if (t->r) {
    t->size += t->r->size;
  }
}
 
void split(PTreap t, Key key, PTreap &l, PTreap &r) {
  if (t == NULL) {
    l = r = NULL;
  } else if (t->key <= key) {
    l = new Treap();
    *l = *t;
    split(t->r, key - t->key, l->r, r);
    fix(l);
  } else {
    r = new Treap();
    *r = *t;
    split(t->l, key, l, r->l);
    fix(r);
  }
}
 
void merge(PTreap &t, PTreap l, PTreap r) {
  if (!l || !r) {
    t = l ? l : r;
    return;
  }
  t = new Treap();
  if (leftSide(l, r)) {
    *t = *l;
    merge(t->r, l->r, r);
  } else {
    *t = *r;
    merge(t->l, l, r->l);
  }
  fix(t);
}
 
vector<PTreap> ver = {NULL};
 
PTreap build(int l, int r, string& s) {
  if (l >= r) return NULL;
  int mid = (l + r) >> 1;
  auto ans = new Treap(s[mid]);
  ans->l = build(l, mid, s);
  ans->r = build(mid + 1, r, s);
  fix(ans);
  return ans;
}
 
int last = 0;
 
void go(PTreap t, int f) {
  if (!t) return;
  go(t->l, f);
  cout << t->val;
  last += (t->val == 'c') * f;
  go(t->r, f);
}
 
void insert(PTreap t, int pos, string& s) {
  PTreap l, r;
  split(t, pos + 1, l, r);
  PTreap mid = build(0, s.size(), s);
  merge(mid, l, mid);
  merge(mid, mid, r);
  ver.push_back(mid);
}
 
void erase(PTreap t, int L, int R) {
  PTreap l, mid, r;
  split(t, L, l, mid);
  split(mid, R - L + 1, mid, r);
  merge(l, l, r);
  ver.push_back(l);
}
