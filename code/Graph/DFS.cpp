int vis[ms], topo[ms], topoLen;

void dfs(int v) {
    if(vis[v]) return;
    vis[v] = true;
    // process node v
    for(int i = adj[v]; i > -1; i = ant[i]) {
        dfs(to[i]);
    }
    topo[topoLen++] = v;
}

void dfs() {
    memset(vis, 0, sizeof vis);
    for(int i = 0; i < n; i++) dfs(i);
    reverse(topo, topo + n);
}

int dis[ms];
queue<int> q;
priority_queue<ii, vector<ii>, greater<ii>> pq;
const int inf = 0x3f3f3f3f;
//BFS usado para shortest path num grafo sem peso
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

//Dijkstra para shortest path num grafo com peso
void dijkstra(int x) {
    memset(dis, 63, sizeof dis);
    dis[x] = 0;
    pq.push(ii(0, x));
    while(!pq.empty()) {
        ii x = pq.top(); pq.pop();
        v = x.second;
        if(x.first > dis[v]) continue;
        for(int i = adj[v]; i > -1; i = ant[i]) {
            int u = to[i], w = wt[i];
            if(dis[v]+w < dis[u]) {
                dis[u] = dis[v] + w;
                pq.push(ii(dis[u], u));
            }
        }
    }
}