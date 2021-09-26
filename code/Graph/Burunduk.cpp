struct edge {
  int a, b, l, r;
};
typedef vector <edge> List;
int cnt[N + 1], ans[N], u[N], color[N], deg[N];
vi g[N];
void add (int a, int b) {
  g[a].pb(b), g[b].pb(a);
}
void dfs (int v, int value) {
  u[v] = 1, color[v] = value;
  forn(i, sz(g[v]))
    if (!u[g[v][i]])
      dfs(g[v][i], value);
}
int compress (List &v1, int vn, int &add_vn) {
  int vn1 = 0;
  forn (i, vn) u[i] = 0;
  forn (i, vn) {
    if (!u[i]) deg[vn1] = 0, dfs(i, vn1++);
  }
  forn (i, sz(v1)) {
    v1[i].a = color[v1[i].a];
    v1[i].b = color[v1[i].b];
    if (v1[i].a != v1[i].b)
      deg[v1[i].a]++, deg[v1[i].b]++;
  }
  vn = vn1, vn1 = 0;
  forn (i, vn) {
    u[i] = vn1, vn1 += (deg[i] > 0), add_vn += !deg[i];
  }
  forn (i, sz(v1)) {
    v1[i].a = u[v1[i].a];
    v1[i].b = u[v1[i].b];
  }
  return vn1;
}
void go (int l, int r, const List &v, int vn, int add_vn) {
  if (cnt[l] == cnt[r]) return;
  if (!sz(v)){
    while (l < r)
      ans[l++] = vn + add_vn;
    return;
  }
  List v1;
  forn (i, vn) {
    g[i].clear();
  }
  forn (i, sz(v)) {
    if (v[i].a != v[i].b){
      if (v[i].l <= l && v[i].r >= r)
        add(v[i].a, v[i].b);
      else if (l < v[i].r && r > v[i].l)
        v1.pb(v[i]);
    }
  }
  int vn1 = compress(v1, vn, add_vn);
  int m = (l + r) / 2;
  go(l, m, v1, vn1, add_vn);
  go(m, r, v1, vn1, add_vn);
}
