const int inf = 0x3f3f3f3f;
int g[ms][ms], dis[ms][ms], n;

void clear() {
  memset(g, 0x3f, sizeof g);
  for(int i = 0; i < n; i++) g[i][i] = 0;
}

void add(int u, int v, int w) {
  g[u][v] = min(w, g[u][v]);
}

void floydWarshall() {
  memcpy(g, dis, sizeof g);
  for(int k = 0; k < n; k++) {
    for(int i = 0; i < n; i++) { 
      for(int j = 0; j < n; j++) {
        dis[i][j] = min(dis[i][j], dis[i][k] + dis[k][j]);
      }
    }
  }
}
