vector<PT> convexHull(vector<PT> p, bool needs = 1) {
  if(needs) sort(p.begin(), p.end());
  p.erase(unique(p.begin(), p.end()), p.end());
  int n = p.size(), k = 0;
  if(n <= 1) return p;
  vector<PT> h(2*n + 5);
  for(int i = 0; i < n; i++) {
    while(k >= 2 && cross(h[k - 1] - h[k - 2], p[i] - h[k - 2]) <= 0) k--;
    h[k++] = p[i];
  }
  for(int i = n - 2, t = k + 1; i >= 0; i--) {
    while(k >= t && cross(h[k - 1] - h[k - 2], p[i] - h[k - 2]) <= 0) k--;
    h[k++] = p[i];
  }
  h.resize(k); // n+1 points where the first is equal to the last
  return h;
}
vector<PT> splitHull(const vector<PT> &hull) {
  vector<PT> ans(hull.size());
  for(int i = 0, j = (int) hull.size()-1, k = 0; k < (int) hull.size(); k++) {
    if(hull[i] < hull[j]) {
      ans[k] = hull[i++];
    } else {
      ans[k] = hull[j--];
    }
  }
  return ans;
}
// uniao de convex hulls
vector<PT> ConvexHull(const vector<PT> &a, const vector<PT> &b) {
  auto A = splitHull(a);
  auto B = splitHull(b);
  vector<PT> C(A.size() + B.size());
  merge(A.begin(), A.end(), B.begin(), B.end(), C.begin());
  return ConvexHull(C, false);
}
int maximizeScalarProduct(const vector<PT> &hull, PT vec) {
  // this code assumes that there are no 3 colinear points
  int ans = 0;
  int n = hull.size();
  if(n < 20) {
    for(int i = 0; i < n; i++) {
      if(dot(hull[i], vec) > dot(hull[ans], vec)) {
        ans = i;
      }
    }
  } else {
    if(dot(hull[1], vec) > dot(hull[ans], vec)) {
      ans = 1;
    }
    for(int rep = 0; rep < 2; rep++) {
      int l = 2, r = n - 1;
      while(l != r) {
        int mid = (l + r + 1) / 2;
        bool flag = dot(hull[mid], vec) >= dot(hull[mid-1], vec);
        if(rep == 0) { flag = flag && dot(hull[mid], vec) >= dot(hull[0], vec); }
        else { flag = flag || dot(hull[mid-1], vec) < dot(hull[0], vec); }
        if(flag) {
          l = mid;
        } else {
          r = mid - 1;
        }
      }
      if(dot(hull[ans], vec) < dot(hull[l], vec)) {
        ans = l;
      }
    }
  }
  return ans;
}
