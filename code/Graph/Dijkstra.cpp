typedef pair<int, int> ii;

vector<ii> g[ms];
int dis[ms];
priority_queue<ii, vector<ii>, greater<ii>> pq;

void dijkstra(int x) {
    memset(dis, 63, sizeof dis);
    dis[x] = 0;
    pq.push(ii(0, x));
    while(!pq.empty()) {
        ii x = pq.top(); pq.pop();
        int u = x.second;
        if(x.first > dis[u]) continue;
        for(auto e : g[u]) {
            int v = e.first, w = e.second;
            if(dis[u]+w < dis[v]) {
                dis[v] = dis[u] + w;
                pq.push(ii(dis[v], v));
            }
        }
    }
}