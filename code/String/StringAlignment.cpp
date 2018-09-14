int pd[ms][ms];

int edit_distance(string &a, string &b) {
  int n = a.size(), m = b.size();
  for(int i = 0; i <= n; i++) pd[i][0] = i;
  for(int j = 0; j <= m; j++) pd[0][j] = j;
  for(int i = 1; i <= n; i++) {
    for(int j = 1; j <= m; j++) {
      int del = pd[i][j-1] + 1;
      int ins = pd[i-1][j] + 1;
      int mod = pd[i-1][j-1] + (a[i-1] != b[j-1]);
      pd[i][j] = min(del, min(ins, mod));
    }
  }
  return pd[n][m];
}