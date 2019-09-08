int gcd_ext(int a, int b, int& x, int &y) {
  if (b == 0) {
    x = 1, y = 0;
    return a;
  }
  int nx, ny;
  int gc = gcd_ext(b, a % b, nx, ny);
  x = ny;
  y = nx - (a / b) * ny;
  return gc;
}

vector<int> diophantine(int D, vector<int> l) {
  int n = l.size();
  vector<int> gc(n), ans(n);
  gc[n - 1] = l[n - 1];
  for (int i = n - 2; i >= 0; i--) {
    int x, y;
    gc[i] = gcd_ext(l[i], gc[i + 1], x, y);
  }
  if (D % gc[0] != 0) {
    return vector<int>();
  }
  for (int i = 0; i < n; i++) {
    if (i == n - 1) {
      ans[i] = D / l[i];
      D -= l[i] * ans[i];
      continue;
    }
    int x, y;
    gcd_ext(l[i] / gc[i], gc[i + 1] / gc[i], x, y);
    ans[i] = (long long int) D / gc[i] * x % (gc[i + 1] / gc[i]);
    if (D < 0 && ans[i] > 0) {
      ans[i] -= (gc[i + 1] / gc[i]);
    }
    if (D > 0 && ans[i] < 0) {
      ans[i] += (gc[i + 1] / gc[i]);
    }
    D -= l[i] * ans[i];
  }
  return ans;
}
