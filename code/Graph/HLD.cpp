// HLD + Euler Tour by adamant

int sz[ms], par[ms], h[ms];
int t, in[ms], out[ms], rin[ms], nxt[ms];

void dfs_sz(int v = 0, int p = -1){
  sz[v] = 1;
  for(int i = 0; i < g[v].size(); i++){
    int &u = g[v][i];
    if(u == p) continue;
    h[u] = h[v]+1, par[u] = v;
    dfs_sz(u, v);
    sz[v] += sz[u];
    if(g[v][0] == p || sz[u] > sz[g[v][0]]){
      swap(u, g[v][0]);
    }
  }
}

void dfs_hld(int v = 0, int p = -1){
  in[v] = t++;
  rin[in[v]] = v;
  for(int i = 0; i < g[v].size(); i++){
    int &u = g[v][i];
    if(u == p) continue;
    nxt[u] = u == g[v][0] ? nxt[v] : u;
    dfs_hld(u, v);
  }
  out[v] = t;
}

int up(int v){
  return (nxt[v] != v) ? nxt[v] : (~par[v] ? par[v] : v); 
}

int getLCA(int a, int b){
  while(nxt[a] != nxt[b]){
    if(h[a] == 0 || h[up(a)] < h[up(b)]) swap(a, b);
    a = up(a);
  }
  return h[a] < h[b] ? a : b;
}

int queryUp(int a, int p = 0){
  int ans = 0;
  while(nxt[a] != nxt[p]){
    ans +=  query(in[nxt[a]], in[a]);
    a = par[nxt[a]];
  }
  ans += query(in[p] + 1, in[a]);
  return ans;
}

int queryPath(int u, int v) {
  int lca = getLCA(u, v);
  return queryUp(u, lca) + queryUp(v, lca) + queryUp(lca, lca);
}
