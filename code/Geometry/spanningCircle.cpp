typedef pair<PT, double> circle;
bool inCircle (circle c, PT p){
  return cmp(dist(c.first, p), c.second) <= 0;
}

PT circumcenter (PT p, PT q, PT r){
  PT a = p-r, b = q-r;
  PT c = PT(dot(a, p+r)/2, dot(b, q+r)/2);
  return PT(cross(c, PT(a.y,b.y)), cross(PT(a.x,b.x), c)) / cross(a, b);
}

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
circle spanningCircle (vector<PT> &v) {
  int n = v.size();
  shuffle(v.begin(), v.end(), rng);
  circle C(PT(), -1);
  for (int i = 0; i < n; i++) if (!inCircle(C, v[i])) {
    C = circle(v[i], 0);
    for (int j = 0; j < i; j++) if (!inCircle(C, v[j])) {
      C = circle((v[i]+v[j])/2, dist(v[i], v[j])/2);
      for(int k = 0; k < j; k++) if (!inCircle(C, v[k])){
        PT o = circumcenter(v[i], v[j], v[k]);
        C = circle(o,dist(o,v[k]));
      }
    }
  }
  return C;
}
