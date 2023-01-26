struct L { // salvar (i, j) CCW, (j, i) CW
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
        return cross(dir, l.dir) > 0;
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
    sort(line.begin(), line.end());
    vector<L> pl(1, line[0]);
    for (int i = 0; i < (int)line.size(); ++i) if (cmp(cross(line[i].dir, pl.back().dir)) != 0) pl.push_back(line[i]);
    deque<int> dq;
    dq.push_back(0);
    dq.push_back(1);
    for (int i = 2; i < (int)pl.size(); ++i) {
        while ((int)dq.size() > 1 && check(pl[i], pl[dq.back()], pl[dq[dq.size() - 2]])) dq.pop_back();
        while ((int)dq.size() > 1 && check(pl[i], pl[dq[0]], pl[dq[1]])) dq.pop_front();
        dq.push_back(i);
    }
    while ((int)dq.size() > 1 && check(pl[dq[0]], pl[dq.back()], pl[dq[dq.size() - 2]])) dq.pop_back();
    while ((int)dq.size() > 1 && check(pl[dq.back()], pl[dq[0]], pl[dq[1]])) dq.pop_front();
    vector<PT> res;
    for (int i = 0; i < (int)dq.size(); ++i){
        res.emplace_back(computeLineIntersection(pl[dq[i]], pl[dq[(i + 1) % dq.size()]]));
    }
    return res;
}
