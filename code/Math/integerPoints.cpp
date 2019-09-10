//p and q have to be coprimes
ll get(ll p, ll q, ll n, bool floor = true) {
  if (n == 0) {
      return 0;
  }
  if (p % q == 0) {
      return n * (n + 1) / 2 * (p / q); 
  }
  if (p > q){
      return n * (n + 1) / 2 * (p / q) + get(p % q, q, n, floor);
  }
  ll new_n = p * n / q;
  ll ans = (n + 1) * new_n - get(q, p, new_n, false);
  if (!floor){
    ans += n - n / q;
  }
  return ans;
}
