void dfs(int v, int par = -1, bool keep = 0) {
    int big = -1;
    for (int u : adj[v]) {
        if (u == par) continue;
        if (big == -1 || sz[u] > sz[big]) {
            big = u;
        }
    }
    for (int u : adj[v]) {
        if (u == par || u == big) {
            continue;
        }
        dfs(u, v, 0);
    }
    if (big != -1) {
        dfs(big, v, 1);
    }
    for (int u : adj[v]) {
        if (u == par || u == big) {
            continue;
        }
        put(u, v);
    }
    if (!keep) {
        
    }
}
