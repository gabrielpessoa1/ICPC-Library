string s;
int fz[ms], n;

void zfunc() {
  fz[0] = n;
  for(int i = 1, l = 0, r = 0; i < n; i++) {
    fz[i] = max(0, min(r-i, fz[i-l]));
    while(s[fz[i]] == s[i+fz[i]]) ++fz[i];
    if(i + fz[i] > r) {
      l = i;
      r = i + fz[i];
    }
  }
}
