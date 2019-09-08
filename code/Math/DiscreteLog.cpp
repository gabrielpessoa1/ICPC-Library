ll discreteLog(ll a, ll b, ll m) {
  // a^ans == b mod m
  // ou -1 se nao existir
  ll cur = a, on = 1;
  for(int i = 0; i < 100; i++) {
    cur = cur * a % m;
  }
  while(on * on <= m) {
    cur = cur * a % m;
    on++;
  }
  map<ll, ll> position;
  for(ll i = 0, x = 1; i * i <= m; i++) {
    position[x] = i * on;
    x = x * cur % m;
  }
  for(ll i = 0; i <= on + 20; i++) {
    if(position.count(b)) {
      return position[b] - i;
    }
    b = b * a % m;
  }
  return -1;
}
