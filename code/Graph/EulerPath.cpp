int path[me], sz, del[me];
int adj[ms], to[me], ant[me], wt[me], z, n;

// Funcao de add e clear no dinic

void eulerPath(int u) {
    for(int i = adj[u]; i > -1; i = ant[u]) {
        if(del[i]) continue;
        del[i] = 1; del[i^1] = 1;
        eulerPath(to[i]);
    }
    path[sz++] = v;
}