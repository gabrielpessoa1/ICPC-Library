void make_set(int v) {
  parent[v] = make_pair(v, 0);
  h[v] = 0;
}

pair<int, int> find_set(int v) {
  if (v != parent[v].first) {
    int parity = parent[v].second;
    parent[v] = find_set(parent[v].first);
    parent[v].second ^= parity;
  }
  return parent[v];
}

bool add_edge(int a, int b) {
  int x, y;
  tie(a, x) = find_set(a);
  tie(b, y) = find_set(b);
  if (a == b) {
    if (x == y)
      return false;
  } else {
    if (h[a] < h[b])
      swap (a, b);
    else if (h[a] == h[b])
      ++h[a];
    parent[b] = make_pair(a, x^y^1);
  }
  return true;
}
