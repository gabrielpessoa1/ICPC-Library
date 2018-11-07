int n, m, mid[ms][ms];
ll dp[ms][ms];

void knuth() {
  for(int i = n; i >= 0; i--) { // limites entre 0 e n
    dp[i][i+1] = 0; mid[i][i+1] = i; // caso base
    for(int j = i+2; j <= n; j++) {
      dp[i][j] = inf; // long long inf
      for(int k = mid[i][j-1]; k <= mid[i+1][j]; k++) {
        if(dp[i][j] > dp[i][k] + dp[k][j]) {
          dp[i][j] = dp[i][k] + dp[k][j];
          mid[i][j] = k;
        }
      }
      dp[i][j] += c(i, j); // custo associado ao intervalo 
    }
  }
}