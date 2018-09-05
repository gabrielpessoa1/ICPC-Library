string s;
int fz[ms], n;

void zfunc() {
  fz[0] = n;
  for(int i = 1, l = 0, r = 0; i < n; i++) {
    if(l &&  i + fz[i-l] < r)
      fz[i] = fz[i-l];
    else {
      int j = min(l ? fz[i-l] : 0, i > r ? 0 : r - i);
      while(s[i+j] == s[j] && ++j);
      fz[i] = j; l = i; r = i + j;
    }
  }
}