int dis[ms];
queue<int> q;

void bfs(int x) {
    memset(vis, 0, sizeof dis);
    dis[x] = 0;
    q.push(x);
    while(!q.empty()) {
        int v = q.front(); q.pop();
        // process node v;
        for(int i = adj[v]; i > -1; i = ant[i]) {
            int u = to[i];
            if(vis[u]) continue;
            vis[u] = true;
            dis[u] = dis[v] + 1;
            q.push(u);
        }
    }
}