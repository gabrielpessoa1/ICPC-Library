vector<int> g[ms];
int vis[ms], topo[ms], topoLen;

void dfs(int u) {
  if(vis[u]) return;
  vis[u] = true;
  for(int v : g[u]) dfs(v);
  topo[topoLen++] = u;
}

void dfs() {
  memset(vis, 0, sizeof vis);
  for(int i = 0; i < n; i++) dfs(i);
  reverse(topo, topo + n);
}
