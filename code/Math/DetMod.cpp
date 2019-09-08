// by zchao1995
// Determinante com coordenadas inteiras usando Mod

ll mat[ms][ms];

ll det (int n) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      mat[i][j] %= mod;
    }
  }
  ll res = 1;
  for (int i = 0; i < n; i++) {
    if (!mat[i][i]) {
      bool flag = false;
      for (int j = i + 1; j < n; j++) {
        if (mat[j][i]) {
          flag = true;
          for (int k = i; k < n; k++) {
            swap (mat[i][k], mat[j][k]);
          }
          res = -res;
          break;
        }
      }
      if (!flag) {
        return 0;
      }
    }
    for (int j = i + 1; j < n; j++) {
      while (mat[j][i]) {
        ll t = mat[i][i] / mat[j][i];
        for (int k = i; k < n; k++) {
          mat[i][k] = (mat[i][k] - t * mat[j][k]) % mod;
          swap (mat[i][k], mat[j][k]);
        }
        res = -res;
      }
    }
    res = (res * mat[i][i]) % mod;
  }
  return (res + mod) % mod;
}
