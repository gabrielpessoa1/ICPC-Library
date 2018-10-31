int arr[4 * ms], seg[4 * ms], n;

void build(int idx = 0, int l = 0, int r = n - 1) {
  int mid = (l+r)/2, left = 2 * idx + 1, right = 2 * idx + 2;
  if(l == r) {
    seg[idx] = arr[l];
    return;
  }
  build(left, l, mid); build(right, mid + 1, r);
  seg[idx] = seg[left] + seg[right]; // Merge
}

int query(int L, int R, int idx = 0, int l = 0, int r = n - 1) {
  int mid = (l+r)/2, left = 2 * idx + 1, right = 2 * idx + 2;
  if(R < l || L > r) return 0; // Valor que nao atrapalhe
  if(L <= l && r <= R) return seg[idx];
  return query(L, R, left, l, mid) + query(L, R, right, mid + 1, r); // Merge
}

void update(int V, int I, int idx = 0, int l = 0, int r = n -1) {
  int mid = (l+r)/2, left = 2 * idx + 1, right = 2 * idx + 2;
  if(l > I || r < I) return;
  if(l == r) {
    arr[I] = V;
    seg[idx] = V; // Aplicar Update
    return;
  }
  update(V, I, left, l, mid); update(V, I, right, mid + 1, r);
  seg[idx] = seg[left] + seg[right]; // Merge
}
