struct L { // salvar (p[i], p[i + 1]) poligono CCW, (p[i + 1], p[i]) poligono CW
    PT a, b, dir;
    L(){}
    L(PT a, PT b) : a(a), b(b) {
      dir = b - a;
    }
    int quadrant() const {
      if (dir.y > 0 && dir.x >= 0) return 0;
      if (dir.x < 0 && dir.y >= 0) return 1;
      if (dir.y < 0 && dir.x <= 0) return 2;
      return 3;
    }
    bool operator < (const L &l) const {
      int q1 = quadrant(), q2 = l.quadrant();
      if (q1 != q2) return q1 < q2;
      double c = cross(dir, l.dir);
      if(cmp(c) == 0) {
        return cmp(cross((l.b - l.a), (b - l.a))) > 0;
      }
      return cmp(c) > 0;
    }
};
PT computeLineIntersection (L la, L lb) {
    return lineLine(la.a, la.b, lb.a, lb.b);
}
bool check (L la, L lb, L lc) {
    PT p = computeLineIntersection(lb, lc);
    double det = cross((la.b - la.a),  (p - la.a));
    return cmp(det) < 0;
}
vector<PT> hpi (vector<L> line) {
    vector<PT> box = {PT(inf, inf), PT(-inf, inf), PT(-inf, -inf), PT(inf, -inf)};
    for(int i = 0; i<4; i++) { 
        line.emplace_back(box[i], box[(i + 1) % 4]);
    }
    sort(line.begin(), line.end());
    vector<L> pl(1, line[0]);
    for (int i = 0; i < (int)line.size(); ++i) if (cmp(cross(line[i].dir, pl.back().dir)) != 0) pl.push_back(line[i]);    vector<int> dq;
    int start = 0;
    for (int i = 0; i < (int)pl.size(); ++i) {
        while ((int)dq.size() - start > 1 && check(pl[i], pl[dq.back()], pl[dq[dq.size() - 2]])) dq.pop_back();
        while ((int)dq.size() - start > 1 && check(pl[i], pl[dq[start]], pl[dq[start + 1]])) start++;
        if((int)dq.size() - start > 0 && cmp(cross(pl[i].dir, pl[dq.back()].dir)) == 0) {
          if(cmp(dot(pl[i].dir, pl[dq.back()].dir)) < 0) return vector<PT>();
          if(cmp(cross(pl[i].dir, pl[dq.back()].a - pl[i].a)) < 0) dq.pop_back(); 
          else continue;
        }
        dq.push_back(i);
    }
    while ((int)dq.size() - start > 1 && check(pl[dq[start]], pl[dq.back()], pl[dq[dq.size() - 2]])) dq.pop_back();
    while ((int)dq.size() - start > 1 && check(pl[dq.back()], pl[dq[start]], pl[dq[start + 1]])) start++;
    vector<PT> res;
    if((int)dq.size() - start < 3) return vector<PT>(); // remove this if res can be point/line
    for (int i = start; i < (int)dq.size(); ++i){
      res.emplace_back(computeLineIntersection(pl[dq[i]], pl[dq[i + 1 == dq.size() ? start : i + 1]]));
    }
    return res;
}
