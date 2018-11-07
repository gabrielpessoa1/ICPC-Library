struct LazyContext {
  int v;

  LazyContext(int v = 0) : v(v) { }
  
  void reset() {
  v = 0;
  }
  
  void operator += (LazyContext o) {
  v += o.v;
  }
};

struct Node {
  int sz, v;

  Node() { // neutral element
        v = 0; sz = 0;
  }
  
  Node(int i) { // init
        v = i; sz = 1;
  }
  
  Node(Node &l, Node &r) { // merge
        sz = l.sz + r.sz;
        v = l.v + r.v;
  }
  
  void apply(LazyContext lazy) {
  v += lazy.v * sz;
  }
};

Node tree[2*ms];
LazyContext lazy[ms];
bool dirty[ms];
int n, h, a[ms];

void init() {
    h = 0;
    while((1 << h) < n) h++;
    for(int i = 0; i < n; i++) {
        tree[i + n] = Node(a[i]);
    }
    for(int i = n - 1; i > 0; i--) {
        tree[i] = Node(tree[i + i], tree[i + i + 1]);
        lazy[i].reset();
        dirty[i] = 0;
    }
}

void apply(int p, LazyContext &lc) {
    tree[p].apply(lc);
    if(p < n) {
        dirty[p] = true;
        lazy[p] += lc;
    }
}

void push(int p) {
    for(int s = h; s > 0; s--) {
        int i = p >> s;
        if(dirty[i]) {
            apply(i + i, lazy[i]);
            apply(i + i + 1, lazy[i]);
            lazy[i].reset();
            dirty[i] = false;
        }
    }
}

void build(int p) {
    for(p /= 2; p > 0; p /= 2) {
        tree[p] = Node(tree[p + p], tree[p + p + 1]);
        if(dirty[p]) {
            tree[p].apply(lazy[p]);
        }
    }
}

Node query(int l, int r) {
    if(l > r) return Node();
    l += n, r += n+1;
    push(l);
    push(r - 1);
    Node lp, rp;
    for(; l < r; l /= 2, r /= 2) {
        if(l & 1) lp = Node(lp, tree[l++]);
        if(r & 1) rp = Node(tree[--r], rp);
    }
    return Node(lp, rp);
}

void update(int l, int r, LazyContext lc) {
    if(l > r) return;
    l += n, r += n+1;
    push(l);
    push(r - 1);
    int l0 = l, r0 = r;
    for(; l < r; l /= 2, r /= 2) {
        if(l & 1) apply(l++, lc);
        if(r & 1) apply(--r, lc);
    }
    build(l0);
    build(r0 - 1);
}