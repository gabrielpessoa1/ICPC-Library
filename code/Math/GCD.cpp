ll gcd(ll a, ll b) {
  while(b) a %= b, swap(a, b);
  return a;
}