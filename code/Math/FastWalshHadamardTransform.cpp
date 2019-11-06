vector<ll> FWHT(char oper, vector<ll> a, const bool inv = false) {
  int n = (int) a.size();
  for(int len = 1; len < n; len += len) {
    for(int i = 0; i < n; i += 2 * len) {
      for(int j = 0; j < len; j++) {
        auto u = a[i + j] % mod, v = a[i + j + len] % mod;
        if(oper == '^') {
          a[i + j] = (u + v) % mod;
          a[i + j + len] = (u - v + mod) % mod;
        }
        if(oper == '|') {
          if(!inv) {
            a[i + j + len] = (u + v) % mod;
          } else {
            a[i + j + len] = (v - u + mod) % mod;
          }
        }
        if(oper == '&') {
          if(!inv) {
            a[i + j] = (u + v) % mod;
          } else {
            a[i + j] = (u - v + mod) % mod;
          }
        }
      }
    }
  }
  if(oper == '^' && inv) {
    ll rev = fexp(n, mod - 2);
    for(int i = 0; i < n; i++) {
      a[i] = a[i] * rev % mod;
    }
  }
  return a;
}
 
vector<ll> multiply(char oper, vector<ll> a, vector<ll> b) {
  int n = 1;
  while (n < (int) max(a.size(), b.size())) {
    n <<= 1;
  }
  vector<ll> ans(n);
  while (a.size() < ans.size()) a.push_back(0);
  while (b.size() < ans.size()) b.push_back(0);
  a = FWHT(oper, a);
  b = FWHT(oper, b);
  for (int i = 0; i < n; i++) {
    ans[i] = a[i] * b[i] % mod;
  }
  ans = FWHT(oper, ans, true);
  return ans;
}
 
const int mxlog = 17;
 
vector<ll> subset_multiply(vector<ll> a, vector<ll> b) {
  int n = 1;
  while (n < (int) max(a.size(), b.size())) {
    n <<= 1;
  }
  vector<ll> ans(n);
  while (a.size() < ans.size()) a.push_back(0);
  while (b.size() < ans.size()) b.push_back(0);
  vector<vector<ll>> A(mxlog + 1, vector<ll>(a.size())), B(mxlog + 1, vector<ll>(b.size()));
  for (int i = 0; i < n; i++) {
    A[__builtin_popcount(i)][i] = a[i];
    B[__builtin_popcount(i)][i] = b[i];
  }
  for (int i = 0; i <= mxlog; i++) {
    A[i] = FWHT('|', A[i]);
    B[i] = FWHT('|', B[i]);
  }
  for (int i = 0; i <= mxlog; i++) {
    vector<ll> C(n);
    for (int x = 0; x <= i; x++) {
      int y = i - x;
      for (int j = 0; j < n; j++) {
        C[j] = (C[j] + A[x][j] * B[y][j] % mod) % mod;
      }
    }
    C = FWHT('|', C, true);
    for (int j = 0; j < n; j++) {
      if (__builtin_popcount(j) == i) {
        ans[j] = (ans[j] + C[j]) % mod;
      }
    }
  }
  return ans;
}
