int adj[ms], to[me], ant[me], z;
int num[ms], low[ms], timer;
bool art[ms], bridge[me], f[me];
int bc[ms], nbc;
stack<int> st, stk;
vector<vector<int>> comps;

void clear() { // Lembrar de chamar no main
  memset(adj, -1, sizeof adj);
  z = 0;
}

void add(int u, int v) {
  to[z] = v;
  ant[z] = adj[u];
  adj[u] = z++;
}

void generateBc (int v) {
  while (!st.empty()) {
    int u = st.top();
    st.pop();
    bc[u] = nbc;
    if (v == u) break;
  }
  ++nbc;
}

void dfs (int v, int p) {
  st.push(v), stk.push(v);
  low[v] = num[v] = ++timer;
  for (int i = adj[v]; i != -1; i = ant[i]) {
    if (f[i] || f[i^1]) continue;
    f[i] = 1;
    int u = to[i];
    if (num[u] == -1) {
      dfs(u, v);
      low[v] = min(low[v], low[u]);
      if (low[u] > num[v]) bridge[i] = bridge[i^1] = 1; 
      if (low[u] >= num[v]) {
        art[v] = (num[v] > 1 || num[u] > 2);
        comps.push_back({v});
        while (comps.back().back() != u)
          comps.back().push_back(stk.top()), stk.pop();
      }
    } else {
      low[v] = min(low[v], num[u]);
    }
  }
  if (low[v] == num[v]) generateBc(v);
}

void biCon (int n) {
  nbc = 0, timer = 0;
  memset(num, -1, sizeof num);
  memset(bc, -1, sizeof bc);
  memset(bridge, 0, sizeof bridge);
  memset(art, 0, sizeof art);
  memset(f, 0, sizeof f);
  for (int i = 0; i < n; i++) {
    if (num[i] == -1) {
      timer = 0;
      dfs(i, 0);
    }
  }
}

vector<int> g[ms];
int id[ms];
void buildBlockCut (int n) {
  int z = 0;
  for (int u = 0; u < n; ++u) {
    if (art[u]) id[u] = z++;
  }
  for (auto &comp : comps) {
    int node = z++;
    for (int u : comp) {
      if (!art[u]) id[u] = node;
      else {
        g[node].push_back(id[u]);
        g[id[u]].push_back(node);
      }
    }
  }
}
