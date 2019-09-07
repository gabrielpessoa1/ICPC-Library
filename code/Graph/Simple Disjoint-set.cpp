struct dsu {
  vector<int> hist, par, sz;
  vector<ii> changes;
  int n;
  dsu (int n) : n(n) {
    hist.assign(n, 1e9);
    par.resize(n);
    iota(par.begin(), par.end(), 0);
    sz.assign(n, 1);
  }
  
  int root (int x, int t) {
    if(hist[x] > t) return x;
    return root(par[x], t);
  }
  
  void join (int a, int b, int t) {
    a = root(a, t);
    b = root(b, t);
    if (a == b) { changes.emplace_back(-1, -1); return; }
    if (sz[a] > sz[b]) swap(a, b);
    par[a] = b;
    sz[b] += sz[a];
    hist[a] = t;
    changes.emplace_back(a, b);
    n--;
  }
  
  bool same (int a, int b, int t) {
    return root(a, t) == root(b, t);
  }
  
  void undo () {
    int a, b;
    tie(a, b) = changes.back();
    changes.pop_back();
    if (a == -1) return;
    sz[b] -= sz[a];
    par[a] = a;
    hist[a] = 1e9;
    n++;
  }
  
  int when (int a, int b) {
    while (1) {
      if (hist[a] > hist[b]) swap(a, b);
      if (par[a] == b) return hist[a];
      if (hist[a] == 1e9) return 1e9;
      a = par[a];
    }
  }
};
