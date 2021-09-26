long long modinverse(long long a, long long b, long long s0 = 1, long long s1 = 0){
  if(!b) return s0;
  else return modinverse(b, a % b, s1, s0 - s1 * (a / b));
}

long long gcd(long long a, long long b){
  if(!b) return a;
  else return gcd(b, a % b);
}

ll mul(ll a, ll b, ll m) {
  ll q = (long double) a * (long double) b / (long double) m;
  ll r = a * b - q * m;
  return (r + 5 * m) % m;
}

long long safemod(long long a, long long m){
  return (a % m + m) % m;
}

struct equation{
  equation(long long a, long long m){mod = m, ans = a, valid = true;}
  equation(){valid = false;}
  equation(equation a, equation b) {
    if(!a.valid || !b.valid) {
      valid = false;
      return;
    }
    long long g = gcd(a.mod, b.mod);
    if((a.ans - b.ans) % g != 0) {
      valid = false;
      return;
    }
    valid = true;
    mod = a.mod * (b.mod / g);
    ans = a.ans +
    mul(
      mul(a.mod, modinverse(a.mod, b.mod), mod),
      (b.ans - a.ans) / g
      , mod);
    ans = safemod(ans, mod);
  }
  long long mod, ans;
  bool valid;

  void print()
  {
    if(!valid)
      std::cout << "equation is not valid\n";
    else
      std::cout << "equation is " << ans << " mod " << mod << '\n';
  }
};