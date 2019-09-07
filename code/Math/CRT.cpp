//by leon

#include<bits/stdc++.h>
using namespace std;
const long long N = 20;

long long GCD(long long a, long long b) { 
  return (b == 0) ? a : GCD(b, a % b); 
}
inline long long get_LCM(long long a, long long b) { 
  return a / GCD(a, b) * b; 
}
inline long long normalize(long long x, long long mod) { 
  x %= mod; 
  if (x < 0) x += mod; 
  return x; 
}

struct GCD_type { 
  long long x, y, d; 
};
GCD_type ex_GCD(long long a, long long b){
  if (b == 0) return {1, 0, a};
  GCD_type pom = ex_GCD(b, a % b);
  return {pom.y, pom.x - a / b * pom.y, pom.d};
}

long long testCases;
long long t;
long long a[N], n[N], ans, LCM;

int main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  t = 2;
  long long T;
  cin >> T;
  while(T--) {
    for(long long i = 1; i <= t; i++) {
      cin >> a[i] >> n[i];
      normalize(a[i], n[i]);
    }
    ans = a[1];
    LCM = n[1];
    bool impossible = false;
    for(long long i = 2; i <= t; i++) {
      auto pom = ex_GCD(LCM, n[i]);
      long long x1 = pom.x;
      long long d = pom.d;
      if((a[i] - ans) % d != 0) {
        impossible = true;
      }
      ans = normalize(ans + x1 * (a[i] - ans) / d % (n[i] / d) * LCM, LCM * n[i] / d);
      LCM = get_LCM(LCM, n[i]);
    }
    if (impossible) cout << "no solution\n";
    else cout << ans << " " << LCM << endl;
  }
  return 0;
}