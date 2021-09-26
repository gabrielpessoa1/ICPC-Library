struct range {
  int l, r;
  int v;
  range(int l = 0, int r = 0, int v = 0) : l(l), r(r), v(v) {}
  bool operator < (const range &a) const {
    return l < a.l;
  }
};
set<range> ranges;
vector<range> update(int l, int r, int v) { // [l, r)
  vector<range> ans;
  if(l >= r) return ans;
  auto it = ranges.lower_bound(l);
  if(it != ranges.begin()) {
    it--;
    if(it->r > l) {
      auto cur = *it;
      ranges.erase(it);
      ranges.insert(range(cur.l, l, cur.v));
      ranges.insert(range(l, cur.r, cur.v));
    }
  }
  it = ranges.lower_bound(r);
  if(it != ranges.begin()) {
    it--;
    if(it->r > r) {
      auto cur = *it;
      ranges.erase(it);
      ranges.insert(range(cur.l, r, cur.v));
      ranges.insert(range(r, cur.r, cur.v));
    }
  }
  for(it = ranges.lower_bound(l); it != ranges.end() && it->l < r; it++) {
    ans.push_back(*it);
  }
  ranges.erase(ranges.lower_bound(l), ranges.lower_bound(r));
  ranges.insert(range(l, r, v));
  return ans;
}
int query(int v) { // Substituir -1 por flag para quando nao houver resposta
  auto it = ranges.upper_bound(v);
  if(it == ranges.begin()) {
    return -1;
  }
  it--;
  return it->r >= v ? it->v : -1;
}
