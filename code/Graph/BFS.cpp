int dis[ms], q[ms], front, rear;

void bfs(int x) {
    memset(vis, 0, sizeof dis);
    dis[x] = 0;	front = 0; rear = 0;
    q[rear++] = x;
    while(front < rear) {
        int v = q[front++];
        for(int i = adj[v]; i > -1; i = ant[i]) {
            if(vis[to[i]]) continue;
            vis[to[i]] = true;
            dis[to[i]] = dis[v] + 1;
            q[rear++] = to[i];
        }
    }
}