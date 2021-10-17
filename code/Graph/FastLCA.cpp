template<class T>
struct RMQ {
  vector<vector<T>> jmp;
  
  RMQ(const vector<T>& V) : jmp(1, V) {
    for (int pw = 1, k = 1; pw * 2 <= (int)size(V); pw *= 2, ++k) {
      jmp.emplace_back(size(V) - pw * 2 + 1);
      for (int j = 0; j < (int)size(jmp[k]); ++j)
        jmp[k][j] = min(jmp[k - 1][j], jmp[k - 1][j + pw]);
    }
  }
  T query(int a, int b) {
    assert(a < b); // or return inf if a == b
    int dep = 31 - __builtin_clz(b - a);
    return min(jmp[dep][a], jmp[dep][b - (1 << dep)]);
  }
};

struct LCA {
  int T = 0;
  vector<int> time, path, ret;
  RMQ<int> rmq;

  LCA(vector<vector<int>>& C) : time(size(C)), rmq((dfs(C,0,-1), ret)) {}
  void dfs(vector<vector<int>>& C, int v, int par) {
    time[v] = T++;
    for (int y : C[v]) if (y != par) {
      path.push_back(v), ret.push_back(time[v]);
      dfs(C, y, v);
    }
  }
  int lca(int a, int b) {
    if (a == b) return a;
    tie(a, b) = minmax(time[a], time[b]);
    return path[rmq.query(a, b)];
  }
};
