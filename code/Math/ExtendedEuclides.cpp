// euclides estendido: acha u e v da equacao:
// u * x + v * y = gcd(x, y);
// u eh inverso modular de x no modulo y
// v eh inverso modular de y no modulo x

pair<ll, ll> euclides(ll a, ll b) {
  ll u = 0, oldu = 1, v = 1, oldv = 0;
  while(b) {
    ll q = a / b;
    oldv = oldv - v * q;
    oldu = oldu - u * q;
    a = a - b * q;
    swap(a, b);
    swap(u, oldu);
    swap(v, oldv);
  }
  return make_pair(oldu, oldv);
}
