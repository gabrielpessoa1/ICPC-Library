int del[me],adj[ms], to[me], ant[me], wt[me], z, n;
vector<int> pathE, pathV;
// Funcao de add e clear no dinic
void eulerPath(int u) {
  for(int &i = adj[u]; ~i; i = ant[i]) if(!del[i]) {
    del[i] = del[i^1] = 1;
    eulerPath(to[i]);
    pathE.emplace_back(i);
  }
  pathV.emplace_back(u);
}
