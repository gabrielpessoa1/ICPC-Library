vector<vector<int>> table;
vector<int> lg2;

void build(int n, vector<int> v) {
  lg2.resize(n + 1);
  lg2[1] = 0;
  for (int i = 2; i <= n; i++) {
    lg2[i] = lg2[i >> 1] + 1;
  }
  table.resize(lg2[n] + 1);
  for (int i = 0; i < lg2[n] + 1; i++) {
    table[i].resize(n + 1);
  }
  for (int i = 0; i < n; i++) {
    table[0][i] = v[i];
  }
  for (int i = 0; i < lg2[n]; i++) {
    for (int j = 0; j < n; j++) {
      if (j + (1 << i) >= n) break;
      table[i + 1][j] = min(table[i][j], table[i][j + (1 << i)]);
    }
  }
}

int get(int l, int r) {
  int k = lg2[r - l + 1];
  return min(table[k][l], table[k][r - (1 << k) + 1]);
}
