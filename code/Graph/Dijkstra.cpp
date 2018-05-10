typedef pair<int, int> ii;

int dis[ms];
priority_queue<ii, vector<ii>, greater<ii>> pq;

void dijkstra(int x) {
    memset(dis, 63, sizeof dis);
    dis[x] = 0;
    pq.push(ii(0, x));
    while(!pq.empty()) {
        ii x = pq.top(); pq.pop();
        v = x.second;
        if(x.first > dis[v]) continue;
        for(int i = adj[v]; i > -1; i = ant[i]) {
            if(dis[v]+wt[i] < dis[to[i]]) {
                dis[to[i]] = dis[v] + wt[i];
                pq.push(ii(dis[to[i]], to[i]));
            }
        }
    }
}