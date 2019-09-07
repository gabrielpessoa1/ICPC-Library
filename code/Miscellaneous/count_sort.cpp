int H[(1<<15)+1], to[mx], b[mx];
void sort(int m, int a[]) {
  memset(H, 0, sizeof H);
  for (int i = 1; i <= m; i++) {
    H[a[i] % (1<<15)]++;
  }
  for (int i = 1; i < 1<<15; i++) {
    H[i] += H[i-1];
  }
  for (int i = m; i; i--) {
    to[i] = H[a[i] % (1 << 15)]--;
  }
  for (int i = 1; i <= m; i++) {
    b[to[i]] = a[i];
  }
  memset(H, 0, sizeof H);
  for (int i = 1; i <= m; i++) {
    H[b[i]>>15]++;
  }
  for (int i = 1; i < 1<<15; i++) {
    H[i] += H[i-1];
  }
  for (int i = m; i ; i--) {
    to[i] = H[b[i]>>15]--;
  }
  for (int i = 1; i <= m; i++) {
    a[to[i]] = b[i];
  }
}
