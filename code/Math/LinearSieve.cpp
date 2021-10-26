//check long long
vector <int> prime;
bool is_composite[MAXN];
int cnt[MAXN];
long long primePow[MAXN];
long long func[MAXN];

long long getFunction(int i, int p) {
  return cnt[i] + 1;
}

void sieve (int n) {
  fill(is_composite, is_composite + n, false);
  func[1] = 1;
  for (int i = 2; i < n; ++i) {
    if (!is_composite[i]) {
      prime.push_back (i);
      func[i] = 1; // base case
      cnt[i] = 1; primePow[i] = i;
    }
    for (int j = 0; j < prime.size () && i * prime[j] < n; ++j) {
      is_composite[i * prime[j]] = true;
      if (i % prime[j] == 0) { 
        func[i * prime[j]] = func[i / primePow[i]] * getFunction(i, prime[j]); // f(ip) = f(i / primePow[i]) * f(primePow[i] * prime[j])
        cnt[i * prime[j]] = cnt[i] + 1;
        primePow[i * prime[j]] = primePow[i] * prime[j];
        break;
      } else { 
        func[i * prime[j]] = func[i] * func[prime[j]]; // f(ip) = f(i) * f(p)
        cnt[i * prime[j]] = 1;
        primePow[i * prime[j]] = prime[j];
      }
    }
  }
}
