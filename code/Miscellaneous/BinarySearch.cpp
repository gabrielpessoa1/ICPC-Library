int smallestSolution(int l, int r) {
  while(l < r) {
    int m = (l+r)/2;
    if(check(m)) r = m;
    else l = m + 1;
  }
  return l;
}

int biggestSolution(int l, int r) {
  while(r - l > 1) {
    int m = (l+r)/2;
    if(check(m)) l = m;
    else r = m;
  }
  return check(r) ? r : l;
}
