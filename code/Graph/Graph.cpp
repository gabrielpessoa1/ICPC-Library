const int ms = 1e3; // Quantidade maxima de vertices
const int me = 1e5; // Quantidade maxima de arestas

int adj[ms], to[me], ant[me], wt[me], z, n;

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