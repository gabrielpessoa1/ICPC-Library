int primitiveRoot(int p) {
  vector<int> fact;
  int phi = p - 1, n = phi;
  for (int i = 2; i * i <= n; i++) {
    if (n % i == 0) {
      fact.push_back(i);
      while (n % i == 0) {
        n /= i;
      }
    }
  }
  if (n > 1) {
    fact.push_back(n);
  }
  for (int res = 2; res <= p; res++) {
    bool ok = true;
    for (auto it : fact) {
      ok &= fexp(res, phi / it, p) != 1;
      if (!ok) {
        break;
      }
    }
    if (ok) {
      return res;
    }
  }
  return -1;
}
