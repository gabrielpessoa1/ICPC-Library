class HLD {
public:
  void init(int n) { /* resize everything */ }
  void addEdge(int u, int v) {
    edges[u].push_back(v);
    edges[v].push_back(u);
  }
  void setRoot(int r) {
    t = 0;
    p[r] = r;
    h[r] = 0;
    prep(r, r);
    nxt[r] = r;
    hld(r);
  }
  int getLCA(int u, int v) {
    while(!inSubtree(nxt[u], v)) u = p[nxt[u]];
    while(!inSubtree(nxt[v], u)) v = p[nxt[v]];
    return in[u] < in[v] ? u : v;
  }
  // is v in the subtree of u?
  bool inSubtree(int u, int v) { 
    return in[u] <= in[v] && in[v] < out[u];
  }
  // returns ranges [l, r) that the path has
  vector<pair<int, int>> getPath(int u, int anc) {
    vector<std::pair<int, int>> ans;
    //assert(inSubtree(anc, u)); 
    while(nxt[u] != nxt[anc]) {
      ans.emplace_back(in[nxt[u]], in[u] + 1);
      u = p[nxt[u]];
    }
    // this includes the ancestor! care
    ans.emplace_back(in[anc], in[u] + 1);
    return ans;
  }
private:
  vector<int> in, out, p, rin, sz, nxt, h;
  vector<vector<int>> edges;
  int t;
  void prep(int on, int par) {
    sz[on] = 1;
    p[on] = par;
    for(int i = 0; i < (int) edges[on].size(); i++) {
      int &u = edges[on][i];
      if(u == par) {
        swap(u, edges[on].back());
        edges[on].pop_back();
        i--;
      } else {
        h[u] = 1 + h[on];
        prep(u, on);
        sz[on] += sz[u];
        if(sz[u] > sz[edges[on][0]]) {
          swap(edges[on][0], u);
        }
      }
    }
  }
  void hld(int on) {
    in[on] = t++;
    rin[in[on]] = on;
    for(auto u : edges[on]) {
      nxt[u] = (u == edges[on][0] ? nxt[on] : u);
      hld(u);
    }
    out[on] = t;
  }
};