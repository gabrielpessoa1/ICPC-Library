ll discreteLog (ll a, ll b, ll m) {
  a %= m; b %= m;
  ll n = (ll) sqrt (m + .0) + 1, an = 1;
  for (ll i = 0; i < n; i++) {
    an = (an * a) % m;
  }
  map<ll, ll> vals;
  for (ll i = 1, cur = an; i <= n; i++) {
    if (!vals.count(cur)) vals[cur] = i;
    cur = (cur * an) % m;
  }
  ll ans = 1e18; //inf
  for (ll i = 0, cur = b; i <= n; i++) {
    if (vals.count(cur)) {
      ans = min(ans, vals[cur] * n - i);
    }
    cur = (cur * a) % m;
  }
  return ans;
}
