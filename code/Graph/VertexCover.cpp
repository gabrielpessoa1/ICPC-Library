// + Dinic
vector<int> coverU, U, coverV, V; // ITA - Partição U LEFT, partição V RIGHT, 0 indexed
bool Zu[mx], Zv[mx];
int pairU[mx], pairV[mx];
void getreach(int u) {
  if (u == -1 || Zu[u]) return;
  Zu[u] = true;
  for (int i = adj[u]; ~i; i = ant[i]) {
    int v = to[i];
    if (v == SOURCE || v == pairU[u]) continue;
    Zv[v] = true;
    getreach(pairV[v]);
  }
}

void minimumcover () {
  memset(pairU, -1, sizeof pairU);
  memset(pairV, -1, sizeof pairV);
  for (auto i : U) {
    for (int j = adj[i]; ~j; j = ant[j]) {
      if (!(j&1) && !wt[j]) {
        pairU[i] = to[j], pairV[to[j]] = i;
      }
    }
  }
  memset(Zu, 0, sizeof Zu);
  memset(Zv, 0, sizeof Zv);
  for (auto u : U) {
    if (pairU[u] == -1) getreach(u);
  }
  coverU.clear(), coverV.clear();
  for (auto u : U) {
    if (!Zu[u]) coverU.push_back(u);
  }
  for (auto v : V) {
    if (Zv[v]) coverV.push_back(v);
  }
}
