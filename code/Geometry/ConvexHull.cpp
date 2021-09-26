vector<PT> convexHull(vector<PT> p, bool needs = 1) {
  if(needs) sort(p.begin(), p.end());
  p.erase(unique(p.begin(), p.end()), p.end());
  int n = p.size(), k = 0;
  if(n <= 1) return p;
  vector<PT> h(n + 2);
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
