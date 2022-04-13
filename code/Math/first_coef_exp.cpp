// by ijmg
vector<int> power(vector<int> &a, int k, int limit = -1) {
  while(a.back() == 0) a.pop_back();
  if(a.size() == 0 || limit == 0) return {};
  if(limit == -1) {
    limit = (a.size() - 1) * k;
  }
  vector<int> ans(limit + 1, 0);
  ans[0] = fexp(a[0], k);
  for(int i = 1; i <= limit; ++i) {
    for(int j = 1; j <= min(i, (int) a.size() - 1); ++j) {
      ans[i] += a[j] * ans[i - j] * (k * j - (i - j));
    }
    ans[i] /= i * a[0];
  }
  return ans;
}
