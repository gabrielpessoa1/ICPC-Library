const int ms = 212345;
vector<int> g[ms];
int idx[ms], low[ms], z, comp[ms], ncomp;
stack<int> st;
int dfs(int u) {
  if(~idx[u]) return idx[u] ? idx[u] : z;
  low[u] = idx[u] = z++;
  st.push(u);
  for(int v : g[u]) {
    low[u] = min(low[u], dfs(v));
  }
  if(low[u] == idx[u]) {
    while(st.top() != u) {
      int v = st.top();
      idx[v] = 0;
      low[v] = low[u];
      comp[v] = ncomp;
      st.pop();
    }
    idx[st.top()] = 0;
    st.pop();
    comp[u] = ncomp++;
  }
  return low[u];
}
bool solveSat(int n) {
  memset(idx, -1, sizeof idx);
  z = 1; ncomp = 0;
  for(int i = 0; i < 2*n; i++) dfs(i);
  for(int i = 0; i < 2*n; i++) if(comp[i] == comp[i^1]) return false;
  return true;
}
int trad(int v) { return v < 0 ?(~v)*2^1 : v * 2; }
void add(int a, int b) { g[trad(a)].push_back(trad(b)); }
void addOr(int a, int b) { add(~a, b); add(~b, a); }
void addImp(int a, int b) { addOr(~a, b); }
void addEqual(int a, int b) { addOr(a, ~b); addOr(~a, b); }
void addDiff(int a, int b) { addEqual(a, ~b); }
// value[i] = comp[trad(i)] < comp[trad(~id)];