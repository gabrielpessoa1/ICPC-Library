typedef pair<int, int> ii;
const int ms = 1e3; // Quantidade maxima de vertices
const int me = 1e5; // Quantidade maxima de arestas
const int inf = 0x3f3f3f3f;

int adj[ms], to[me], ant[me], wt[me], z, vis[ms], dis[ms], n, topo[ms], topoLen;
queue<int> q;
priority_queue<ii, vector<ii>, greater<ii>> pq;

void clear() {
    memset(adj, -1, sizeof adj);
    z = 0;
}

void add(int u, int v, int w = 1) {
    to[z] = v;
    ant[z] = adj[u];
    wt[z] = w;
    adj[u] = z++;
}


// DFS com Toposort como exemplo
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