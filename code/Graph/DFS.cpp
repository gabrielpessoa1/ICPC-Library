int vis[ms], topo[ms], topoLen;

void dfs(int v) {
    if(vis[v]) return;
    vis[v] = true;
    for(int i = adj[v]; i > -1; i = ant[i]) dfs(to[i]);
    topo[topoLen++] = v;
}

void dfs() {
    memset(vis, 0, sizeof vis);
    for(int i = 0; i < n; i++) dfs(i);
    reverse(topo, topo + n);
}
