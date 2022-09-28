//miller_rabin
typedef long long ll;
typedef unsigned long long ull;
 
ll mul(ull a, ull b, ull mod) { 
  ll ret = 0; 
  for (a %= mod, b %= mod; b != 0;
    b >>= 1, a <<= 1, a = a >= mod ? a - mod : a) {
    if (b&1) {
      ret += a;
      if (ret >= mod)	ret -= mod;
    }
  }
  return ret; 
}
 
ll mpow(ll a, ll b, ll mod) {
  ll ans = 1;
  for(; b; b>>=1, a = mul(a, a, mod))
    if (b&1) ans = mul(ans, a, mod);
  return ans;
}
 
bool witness (ll a, ll k, ll q, ll n) {
  ll t = mpow(a, q, n);
  if (t == 1 || t == n-1) return false;
  for (int i = 0; i < k-1; i++) {
    t = mul(t, t, n);
    if (t == 1) return true;
    if (t == n - 1) return false;
  }
  return true;
}
 
ll test[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 0};
bool isPrime(ll n) {
  if (n == 2) return true;
  if (n < 2 || !(n&1)) return false;  
  ll q = n-1, k = 0;
  while (!(q&1)) q >>= 1, k++;
  for (int i = 0; test[i] && test[i] < n; i++)
    if(witness(test[i], k, q, n)) return false;
    // use for big num two times rand()%(n-4) + 2;
  return true;
}
 
ll pollard_rho(ll n, ll c) {
  ll x = 2, y = 2, i = 1, k = 2, d;
  while (true) {
    x = (mul(x, x, n) + c);
    if (x >= n)	x -= n;
    d = __gcd(x - y, n);
    if (d > 1) return d;
    if (++i == k) y = x, k <<= 1;
  }
  return n;
}
 
void factorize(ll n, vector<ll> &f) {
  if (n == 1) return;
  if (isPrime(n)) {
    f.push_back(n);
    return;
  }
  ll d = n;
  for (int i = 2; d == n; i++)
    d = pollard_rho(n, i);
  factorize(d, f);
  factorize(n/d, f);
}
