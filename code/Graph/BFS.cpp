vector<int> g[ms];
int dis[ms];
queue<int> q;

void bfs(int x) {
    memset(dis, 63, sizeof dis);
    dis[x] = 0;
    q.push(x);
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        for(int v : g[u]) {
            if(dis[v] > dis[u] + 1) {
                dis[v] = dis[u] + 1;
                q.push(v);
            }
       }
    }
}
