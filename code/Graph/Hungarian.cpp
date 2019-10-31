//input: matrix n x m, n <= m
//return vector p of size n, where p[i] is the match for i
// and minimum cost
// time complexity: O(n^2 * m)

int u[ms], v[ms], p[ms], way[ms], minv[ms];
bool used[ms];

pair<vector<int>, int> solve(const vector<vector<int>> &matrix) {
  int n = matrix.size();
  if(n == 0) return {vector<int>(), 0};
  int m = matrix[0].size();
  assert(n <= m);
  memset(u, 0, (n+1)*sizeof(int));
  memset(v, 0, (m+1)*sizeof(int));
  memset(p, 0, (m+1)*sizeof(int));
  for(int i = 1; i <= n; i++) {
    memset(minv, 0x3f, (m+1)*sizeof(int));
    memset(way, 0, (m+1)*sizeof(int));
    for(int j = 0; j <= m; j++) used[j] = 0;
    p[0] = i;
    int k0 = 0;
    do {
      used[k0] = 1;
      int i0 = p[k0], delta = inf, k1;
      for(int j = 1; j <= m; j++) {
        if(!used[j]) {
          int cur = matrix[i0-1][j-1] - u[i0] - v[j];
          if (cur < minv[j]) {
            minv[j] = cur;
            way[j] = k0;
          }
          if(minv[j] < delta) {
            delta = minv[j];
            k1 = j;
          }
        }
      }
      for(int j = 0; j <= m; j++) {
        if(used[j]) {
          u[p[j]] += delta;
          v[j] -= delta;
        } else {
          minv[j] -= delta;
        }
      }
      k0 = k1;
    } while(p[k0]);
    do {
      int k1 = way[k0];
      p[k0] = p[k1];
      k0 = k1;
    } while(k0);
  }
  vector<int> ans(n, -1);
  for(int j = 1; j <= m; j++) {
    if(!p[j]) continue;
    ans[p[j] - 1] = j - 1;
  }
  return {ans, -v[0]};
}