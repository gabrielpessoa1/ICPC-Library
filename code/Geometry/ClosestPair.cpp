double closestPair(vector<PT> p) {
  int n = p.size(), k = 0;
  sort(p.begin(), p.end());
  double d = inf;
  set<PT> ptsInv;
  for(int i = 0; i < n; i++) {
    while(k < i && p[k].x < p[i].x - d) {
      ptsInv.erase(swapCoord(p[k++]));
    }
    for(auto it = ptsInv.lower_bound(PT(p[i].y - d, p[i].x - d)); 
      it != ptsInv.end() && it->x <= p[i].y + d; it++) {
      d = min(d, dist(p[i] - swapCoord(*it), PT(0, 0)));
    }
    ptsInv.insert(swapCoord(p[i]));
  }
  return d;
}
