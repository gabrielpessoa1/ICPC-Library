struct LazyContext { 
  LazyContext() {}
  void reset() {}
  void operator += (LazyContext &o) {}
  // add attributes
};
struct Node {
  Node() {} // neutral element or empty node
  Node() {} // init 
  Node(Node &l, Node &r) {} // merge
  void apply(LazyContext &lazy) {}
  // add attributes
};
template <class i_t, class e_t, class lazy_cont = int> //internal node, external node
class SegmentTree { // Range update, range query segment tree
public:
  void init(vector<e_t> base) {
    n = base.size();
    h = 0;
    while((1 << h) < n) h++;
    tree.resize(2 * n);
    dirty.assign(n, false);
    lazy.resize(n);
    for(int i = 0; i < n; ++i) {
      tree[i + n] = i_t(base[i]); //add arguments if needed to init
    }
    for(int i = n - 1; i > 0; --i) {
      tree[i] = i_t(tree[i << 1], tree[i << 1 | 1]);
      lazy[i].reset();
    }
  }
  i_t qry(int l, int r) { // [l, r)
    if(l >= r) return i_t();
    l += n, r += n;
    push(l);
    push(r - 1);
    i_t lp, rp;
    for(; l < r; l >>= 1, r >>= 1) {
      if(l & 1) lp = i_t(lp, tree[l++]);
      if(r & 1) rp = i_t(tree[--r], rp);
    }
    return i_t(lp, rp);
  }
  void upd(int l, int r, lazy_cont lc) { // [l, r)
    if(l >= r) return;
    l += n, r += n;
    push(l);
    push(r - 1);
    int l0 = l, r0 = r;
    for(; l < r; l >>= 1, r >>= 1) {
      if(l & 1) apply(l++, lc);
      if(r & 1) apply(--r, lc);
    }
    build(l0);
    build(r0 - 1);
  }
private:
  int n, h;
  vector<bool> dirty;
  vector<i_t> tree;
  vector<lazy_cont> lazy;
  void apply(int p, lazy_cont &lc) {
    tree[p].apply(lc);
    if(p < n) {
      dirty[p] = true;
      lazy[p] += lc;
    }
  }
  void push(int p) {
    for(int s = h; s > 0; --s) {
      int i = p >> s;
      if(dirty[i]) {
        apply(i << 1, lazy[i]);
        apply(i << 1 | 1, lazy[i]);
        lazy[i].reset();
        dirty[i] = false;
      }
    }
  }
  void build(int p) {
    for(p >>= 1; p > 0; p >>= 1) {
      tree[p] = i_t(tree[p << 1], tree[p << 1 | 1]);
      if(dirty[p]) {
        tree[p].apply(lazy[p]);
      }
    }
  }
};