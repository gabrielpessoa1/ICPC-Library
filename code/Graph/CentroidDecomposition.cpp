template<typename T>
struct CentroidDecomposition {
  vector<int> sz, h, dad;
  vector<vector<pair<int, T>>> adj;
  vector<vector<T>> dis;
  vector<bool> removed;
  CentroidDecomposition (int n) {
    sz.resize(n);
    h.resize(n);
    dis.resize(n, vector<T>(30, 0));
    adj.resize(n);
    removed.resize(n, 0);
    dad.resize(n);
  }
  void add (int a, int b, T w = 1) {
    adj[a].push_back({b, w});
    adj[b].push_back({a, w});
  }
  void dfsSize (int v, int par){
    sz[v] = 1;
    for (auto u : adj[v]){
      if (u.x == par || removed[u.x]) continue;
      dfsSize(u.x, v);
      sz[v] += sz[u.x];
    }
  }
  int getCentroid (int v, int par, int tam){
    for (auto u : adj[v]) {
      if (u.x == par || removed[u.x]) continue;
      if ((sz[u.x]<<1) > tam) return getCentroid(u.x, v, tam);
    }
    return v;
  }
  void setDis (int v, int par, int nv){
    for (auto u : adj[v]) {
      if (u.x == par || removed[u.x]) continue;
      dis[u.x][nv] = dis[v][nv]+u.y;
      setDis(u.x, v, nv);
    }
  }
  void decompose (int v, int par = -1, int nv = 0){
    dfsSize(v, par);
    int c = getCentroid(v, par, sz[v]);
    dad[c] = par;
    removed[c] = 1;
    h[c] = nv;
    setDis(c, par, nv);
    for (auto u : adj[c]){
      if (!removed[u.x]){
        decompose(u.x, c, nv + 1);
      }
    }
  }
  int operator [] (const int idx) const {
    return dad[idx];
  }
  T dist (int u, int v) {
    if (h[u] < h[v]) swap(u, v);
    return dis[u][h[v]];
  }
};