struct edge {
  int u, v;
  int w;
  int id;
  edge () {};
  edge (int u, int v, int w = 0, int id = 0) : u(u), v(v), w(w), id(id) {};
  bool operator < (edge &other) const { return w < other.w; };
};

vector<edge> boruvka (vector<edge> &edges, int n) {
  vector<edge> mst;
  vector<edge> best(n);
  initDSU(n);
  bool f = 1;
  while (f) {
    f = 0;
    for (int i = 0; i < n; i++) best[i] = edge(i, i, inf);
    for (auto e : edges) {
      int pu = root(e.u), pv = root(e.v);
      if (pu == pv) continue;
      if (e < best[pu]) best[pu] = e;
      if (e < best[pv]) best[pv] = e;
    }
    for (int i = 0; i < n; i++) {
      edge e = best[root(i)];
      if (e.w != inf) {
        join(e.u, e.v);
        mst.push_back(e);
        f = 1;
      }
    }
  }
  return mst;
}
