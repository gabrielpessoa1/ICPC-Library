int bit[ms], n;

void update(int v, int idx) {
  while(idx <= n) {
    bit[idx] += v;
    idx += idx & -idx;
  }
}

int query(int idx) {
  int r = 0;
  while(idx > 0) {
    r += bit[idx];
    idx -= idx & -idx;
  }
  return r;
}