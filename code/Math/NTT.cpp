const int MOD = 998244353;
const int me = 15;
const int ms = 1 << me;

#define add(x, y) x+y>=MOD?x+y-MOD:x+y

const int gen = 3; // use search() from PrimitiveRoot.cpp if MOD isn't 998244353

int bits[ms], root[ms];
void initFFT() {
  root[1] = 1;
  for(int len = 2; len < ms; len += len) {
    int z = fexp(gen, (MOD - 1) / len / 2);
    for(int i = len / 2; i < len; i++) {
      root[2 * i] = root[i];
      root[2 * i + 1] = (long long) root[i] * z % MOD;
    }
  }
}
void pre(int n) {
  int LOG = 0;
  while(1 << (LOG + 1) < n) {
    LOG++;
  }
  for(int i = 1; i < n; i++) {
    bits[i] = (bits[i >> 1] >> 1) | ((i & 1) << LOG);
  }
}
vector<int> fft(vector<int> a, bool inv = false) {
  int n = (int) a.size();
  pre(n);
  if(inv) {
    reverse(a.begin() + 1, a.end());
  }
  for(int i = 0; i < n; i++) {
    int to = bits[i];
    if(i < to) 
      swap(a[i], a[to]);
  }
  for(int len = 1; len < n; len *= 2) {
    for(int i = 0; i < n; i += len * 2) {
      for(int j = 0; j < len; j++) {
        int u = a[i + j], v = (ll) a[i + j + len] * root[len + j] % mod;
        a[i + j] = add(u, v);
        a[i + j + len] = add(u, mod - v);
      }
    }
  }
  if(inv) {
    int rev = fexp(n, mod-2, mod);
    for(int i = 0; i < n; i++)
      a[i] = (ll) a[i] * rev % mod;
  }
  return a;
}
std::vector<int> operator *(std::vector<int> a, std::vector<int> b) {
  while(!a.empty() && a.back() == 0) a.pop_back();
  while(!b.empty() && b.back() == 0) b.pop_back();
  if(a.empty() || b.empty()) return std::vector<int>(0, 0);
  int n = 1;
  while(n-1 < (int) a.size() + (int) b.size() - 2) n += n;
  a.resize(n, 0);
  b.resize(n, 0);
  a = fft(a, false);
  b = fft(b, false);
  for(int i = 0; i < n; i++) {
    a[i] = (int) ((long long) a[i] * b[i] % MOD); 
  }
  return fft(a, true);
}