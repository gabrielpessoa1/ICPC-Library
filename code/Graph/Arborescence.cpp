// uncommented O(V^2) arborescence
struct Edges {
  //set<pair<long long, int>> cost; O(Elog^2)
  long long cost[ms];

  // possible optimization, use vector of size n
  // instead of ms
  long long sum = 0;

  Edges() {
    memset(cost, 0x3f, sizeof cost);
  }

  void addEdge(int u, long long c) {
    // cost.insert({c - sum, u}); O(Elog^2)
    cost[u] = min(cost[u], c - sum);
  }

  pair<long long, int> getMin() {
    //return *cost.begin(); O(E*log^2)
    pair<long long, int> ans(cost[0], 0);
    // in this loop can change ms to n to make it faster for many cases
    for(int i = 1; i < ms; i++) {
      if(cost[i] < ans.first) {
        ans = pair<long long, int>(cost[i], i);
      }
    }
    return ans;
  }

  void unite(Edges &e) {
    /*

    O(E*log^2E)
    if(e.cost.size() > cost.size()) {
      cost.swap(e.cost);
      swap(sum, e.sum);
    }
    for(auto i : e.cost) {
      addEdge(i.second, i.first + e.sum);
    }
    e.cost.clear();
    */

    // O(V^2)
    // can change ms to n
    for(int i = 0; i < ms; i++) {
      cost[i] = min(cost[i], e.cost[i] + e.sum - sum);
    }
  }
};

typedef vector<vector<pair<long long, int>>> Graph;

Edges ed[ms];
int par[ms];
long long best[ms];
int col[ms];
int getPar(int x) { return par[x] < 0 ? x : par[x] = getPar(par[x]); }
void makeUnion(int a, int b) {
  a = getPar(a);
  b = getPar(b);
  if(a == b) return;
  ed[a].unite(ed[b]);
  par[b] = a;
}

long long arborescence(Graph edges) {
  // root is 0
  // edges has transposed adjacency list (cost, from)
  // edge from i to j cost c is
  // edge[j].emplace_back(c, i)
  int n = (int) edges.size();
  long long ans = 0;
  for(int i = 0; i < n; i++) {
    ed[i] = Edges();
    par[i] = -1;
    for(auto j : edges[i]) {
      ed[i].addEdge(j.second, j.first);
    }
    col[i] = 0;
  }
  // to change the root you can simply change this next line to
  // col[root] = 2;
  col[0] = 2;
  for(int i = 0; i < n; i++) {
    if(col[getPar(i)] == 2) {
      continue;
    }
    int on = getPar(i);
    vector<int> st;
    while(col[on] != 2) {
      assert(getPar(on) == on);
      if(col[on] == 1) {
        // found cycle
        int v = on;
        vector<int> cycle;
        //cout << "found cycle\n";
        while(st.back() != v) {
          //cout << st.back() << endl;
          cycle.push_back(st.back());
          st.pop_back();
        }
        // compress cycle
        for(auto u : cycle) {
          makeUnion(v, u);
        }
        v = getPar(v);
        col[v] = 0;
        on = v;
      } else {
        // still no cycle
        // while best is in compressed cycle, remove

        /*
        THIS IS TO MAKE O(E*log^2) ALGORITHM!!
        while(!ed[on].cost.empty() && getPar(on) == getPar(ed[on].getMin().second)) {
          ed[on].cost.erase(ed[on].cost.begin());
        }
        */

        // O(V^2)
        for(int x = 0; x < n; x++) {
          if(on == getPar(x)) {
            ed[on].cost[x] = 0x3f3f3f3f3f3f3f3fLL;
          }
        }

        // best edge
        auto e = ed[on].getMin();
        // O(E*log^2) assert(!ed[on].cost.empty()) if every vertex appears in the arborescence
        // O(V^2)
        assert(e.first < 0x3f3f3f3f3f3f3f3fLL);
        int v = getPar(e.second);
        //cout << "found not cycle to " << v << " of cost " << e.first + ed[on].sum << '\n';
        assert(v != on);
        best[on] = e.first + ed[on].sum;
        ans += best[on];
        // compress edges
        ed[on].sum = -(e.first);
        st.push_back(on);
        col[on] = 1;
        on = v;
      }
    }
    // make everything 2
    for(auto u : st) {
      assert(getPar(u) == u);
      col[u] = 2;
    }
  }
  return ans;
}