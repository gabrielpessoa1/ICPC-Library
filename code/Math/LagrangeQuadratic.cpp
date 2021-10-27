// O(n^2), receve v {x, y} e retorna o polinomio em fracao
vector<pair<int, int>> interpolate(vector<ii> v) {
  int n = v.size();
  vector<int> prod(n+1);
  prod[0] = 1;
  for(auto p : v) {
    for(int i = n; i > 0; i--) {
      prod[i] = prod[i-1] - p.first * prod[i];
    }
    prod[0] = -p.first * prod[0];
  }
  vector<pair<int, int>> ans(n+1);
  for(int i = 0; i <= n; i++) ans[i].second = 1;
  for(int i = 0; i < n; i++) {
    vector<int> pol(n+1); // (x - v[i].first)
    for(int j = n; j > 0; j--) {
      pol[j-1] = prod[j] + pol[j] * v[i].first;
    }
    for(int j = 0; j < n; j++) {
      pol[j] *= v[i].second;
    }
    int k = 1;
    for(int j = 0; j < n; j++) {
      if(i==j) continue;
      k *= v[i].first - v[j].first;
    }
    if(k < 0) {
      k = -k;
      for(auto &p : pol) p = -p;
    }
    for(int i = 0; i < n; i++) {
      ans[i] = {ans[i].first*k + pol[i]*ans[i].second, k*ans[i].second};
      if(ans[i].first == 0) ans[i].second = 1;
      else {
        int gc = __gcd(abs(ans[i].first), ans[i].second);
        ans[i].first /= gc;
        ans[i].second /= gc;
      }
    }
  }
  return ans;
}
