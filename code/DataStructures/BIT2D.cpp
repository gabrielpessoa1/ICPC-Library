template<class T = int>
struct Bit2D {
public:
  // send updated points
  Bit2D(vector<pair<T, T>> pts) {
    sort(pts.begin(), pts.end());
    for(auto a : pts) {
      if(ord.empty() || a.first != ord.back()) {
        ord.push_back(a.first);
      }
    }
    fw.resize(ord.size() + 1);
    coord.resize(fw.size());
    for(auto &a : pts) {
      swap(a.first, a.second);
    }
    sort(pts.begin(), pts.end());
    for(auto &a : pts) {
      swap(a.first, a.second);
      for(int on = upper_bound(ord.begin(), ord.end(), a.first) - ord.begin(); on < fw.size(); on += on & -on) {
        if(coord[on].empty() || coord[on].back() != a.second) {
          coord[on].push_back(a.second);
        }
      }
    }
    for(int i = 0; i < fw.size(); i++) {
      fw[i].assign(coord[i].size() + 1, 0);
    }
  }
  void upd(T x, T y, T v) {
    for(int xx = upper_bound(ord.begin(), ord.end(), x) - ord.begin(); xx < fw.size(); xx += xx & -xx) {
      for(int yy = upper_bound(coord[xx].begin(), coord[xx].end(), y) - coord[xx].begin(); yy < fw[xx].size(); yy += yy & -yy) {
        fw[xx][yy] += v;
      }
    }
  }
  T qry(T x, T y) {
    T ans = 0;
    for(int xx = upper_bound(ord.begin(), ord.end(), x) - ord.begin(); xx > 0; xx -= xx & -xx) {
      for(int yy = upper_bound(coord[xx].begin(), coord[xx].end(), y) - coord[xx].begin(); yy > 0; yy -= yy & -yy) {
        ans += fw[xx][yy];
      }
    }
    return ans;
  }
  T qry(T x1, T y1, T x2, T y2) {
    return qry(x2, y2) - qry(x2, y1 - 1) - qry(x1 - 1, y2) + qry(x1 - 1, y1 - 1);
  }
  void upd(T x1, T y1, T x2, T y2, T v) {
    upd(x1, y1, v);
    upd(x1, y2 + 1, -v);
    upd(x2 + 1, y1, -v);
    upd(x2 + 1, y2 + 1, v);
  }
private:
  vector<T> ord;
  vector<vector<T>> fw, coord;
};
