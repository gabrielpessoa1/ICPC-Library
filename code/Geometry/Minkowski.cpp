bool comp(PT a, PT b){
  int hp1 = (a.x < 0 || (a.x==0 && a.y<0));
  int hp2 = (b.x < 0 || (b.x==0 && b.y<0));
  if(hp1 != hp2) return hp1 < hp2;
  long long R = cross(a, b);
  if(R) return R > 0;
  return dot(a, a) < dot(b, b);
}

vector<PT> minkowskiSum(const vector<PT> &a, const vector<PT> &b){
  if(a.empty() || b.empty()) return vector<PT>(0);
  vector<PT> ret;
  int n1 = a.size(), n2 = b.size();
  if(min(n1, n2) < 2){
    for(int i = 0; i < n1; i++) {
      for(int j = 0; j < n2; j++) {
        ret.push_back(a[i]+b[j]);
      }
    }
    return ret;
  }
  PT v1, v2, p = a[0]+b[0];
  ret.push_back(p);
  for (int i = 0, j = 0; i + j + 1 < n1+n2; ){
    v1 = a[(i+1)%n1]-a[i];
    v2 = b[(j+1)%n2]-b[j];
    if(j == n2 || (i < n1 && comp(v1, v2))) p = p + v1, i++;
    else p = p + v2, j++;
    while(ret.size() >= 2 && cmp(cross(p-ret.back(), p-ret[(int)ret.size()-2])) == 0) {
      // removing colinear points
      // needs the scalar product stuff it the result is a line
      ret.pop_back();
    }
    ret.push_back(p);
  }
  return ret;
}
