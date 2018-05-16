int dis[ms], q[ms], front, rear;

void bfs(int x) {
    memset(dis, -1, sizeof dis);
    dis[x] = 0;	front = 0; rear = 0;
    q[rear++] = x;
    while(front < rear) {
        int v = q[front++];
        for(int i = adj[v]; i > -1; i = ant[i]) {
            if(~dis[to[i]]) continue;
            dis[to[i]] = dis[v] + 1;
            q[rear++] = to[i];
        }
    }
}
