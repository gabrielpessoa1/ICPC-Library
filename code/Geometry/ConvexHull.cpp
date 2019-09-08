vector<PT> convexHull(vector<PT> p) {
  int n = p.size(), k = 0;
  vector<PT> h(2 * n);
  sort(p.begin(), p.end());
  for(int i = 0; i < n; i++) {
    while(k >= 2 && cmp(cross(h[k - 1] - h[k - 2], p[i] - h[k - 2])) <= 0) k--;
    h[k++] = p[i];
  }
  for(int i = n - 2, t = k + 1; i >= 0; i--) {
    while(k >= t && cmp(cross(h[k - 1] - h[k - 2], p[i] - h[k - 2])) <= 0) k--;
    h[k++] = p[i];
  }
  h.resize(k); // n+1 points where the first is equal to the last
  return h;
}

void sortByAngle (vector<PT>::iterator first, vector<PT>::iterator last, const PT o) {
  first = partition(first, last, [&o] (const PT &a) { return a == o; });
  auto pivot = partition(first, last, [&o] (const PT &a) {
    return !(a < o || a == o); // PT(a.y, a.x) < PT(o.y, o.x)
  });
  auto acmp = [&o] (const PT &a, const PT &b) { // C++11 only
    if (cmp(cross(a-o, b-o)) != 0) return cross(a-o, b-o) > 0;
    else return cmp(norm(a-o), norm(b-o)) < 0;
  };
  sort(first, pivot, acmp);
  sort(pivot, last, acmp);
}

vector<PT> graham (vector<PT> v) {
  sort(v.begin(), v.end());
  sortByAngle(v.begin(), v.end(), v[0]);
  vector<PT> u (v.size());
  int top = 0;
  for (int i = 0; i < v.size(); i++) {
    while (top > 1 && cmp(cross(u[top-1] - u[top-2], v[i]-u[top-2])) <= 0) top--;
    u[top++] = v[i];
  }
  u.resize(top);
  return u;
}
