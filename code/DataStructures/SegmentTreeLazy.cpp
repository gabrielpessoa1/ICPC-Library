int arr[ms],  seg[4 * ms], lazy[4 * ms], n;

void build(int idx = 0, int l = 0, int r = n-1) {
  int mid = (l+r)/2;
  lazy[idx] = 0;
  if(l == r) {
    seg[idx] = arr[l];
    return;
  }
  build(2*idx+1, l, mid); build(2*idx+2, mid+1, r);
  seg[idx] = seg[2*idx+1] + seg[2*idx+2]; // Merge
}

void apply(int idx, int l, int r) {
  if(lazy[idx] && !canBreak) { // if not beats canBreak = false
    if(l < r) {
      lazy[2*idx+1] += lazy[idx];  // Merge de lazy
      lazy[2*idx+2] += lazy[idx];  // Merge de lazy
    }
    if(canApply) { // if not beats canApply = true
      seg[idx] += lazy[idx] * (r - l + 1); // Aplicar lazy no seg
    } else {
      apply(2*idx+1, l, mid); apply(2*idx+2, mid+1, r);
      seg[idx] = seg[2*idx+1] + seg[2*idx+2]; // Merge
    }
  }
  lazy[idx] = 0; // Limpar a lazy
}

int query(int L, int R, int idx = 0, int l = 0, int r = n-1) {
  int mid = (l+r)/2;
  apply(idx, l, r);
  if(l > R || r < L) return 0; // Valor que nao atrapalhe
  if(L <= l && r <= R) return seg[idx];
  return query(L, R, 2*idx+1, l, mid) + query(L, R, 2*idx+2, mid+1, r); // Merge
}

void update(int L, int R, int V, int idx = 0, int l = 0, int r = n-1) {
  int mid = (l+r)/2;
  apply(idx, l, r);
  if(l > R || r < L) return;
  if(L <= l && r <= R) {
    lazy[idx] = V;
    apply(idx, l, r);
    return;
  }
  update(L, R, V, 2*idx+1, l, mid); update(L, R, V, 2*idx+2, mid+1, r);
  seg[idx] = seg[2*idx+1] + seg[2*idx+2]; // Merge
}
