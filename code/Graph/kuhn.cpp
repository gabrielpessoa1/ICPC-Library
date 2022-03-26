int n, m;
vector<vector<int>> g;
vector<int> mt;
vector<bool> used;

bool try_kuhn(int v) {
  if (used[v]) return false;
  used[v] = true;
  for (int to : g[v]) {
    if (mt[to] == -1 || try_kuhn(mt[to])) {
      mt[to] = v;
      return true;
    }
  }
  return false;
}

int main () {
  mt.assign(m, -1);
  vector<bool> used1(n, false);
  for (int i = 0; i < n; i++) {
    for (int to : g[i]) {
      if (mt[to] == -1) {
        mt[to] = i;
        used1[i] = true;
        break;
      }
    }
  }
  
  for (int i = 0; i < n; i++) {
    used.assign(n, false);
    try_kuhn(i);
  }
}
