int pathV[me], szV, del[me], pathE, szE;
int adj[ms], to[me], ant[me], wt[me], z, n;
// Funcao de add e clear no dinic
void eulerPath(int u) {
  for(int i = adj[u]; ~i; i = ant[u]) if(!del[i]) {
    del[i] = del[i^1] = 1;
    eulerPath(to[i]);
    pathE[szE++] = i;
  }
  pathV[szV++] = u;
}