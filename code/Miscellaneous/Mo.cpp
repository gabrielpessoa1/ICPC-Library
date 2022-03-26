const int blk_sz = 170;

struct Query {
  int l, r, idx;
  bool operator < (Query a) {
    if (l / blk_sz == a.l / blk_sz) {
      return r < a.r;
    }
    return (l / blk_sz) < (a.l / blk_sz);
  }
};

vector<Query> queries;
int a[MAXN], ans[MAXN], qnt[1000010];
int diff = 0;

void add(int x) {
  x = a[x];
  if (qnt[x] == 0) {
    diff++;
  }
  qnt[x]++;
}

void remove(int x) {
  x = a[x];
  qnt[x]--;
  if (qnt[x] == 0) {
    diff--;
  }
}

void mos() {
  int curr_l = 0, curr_r = -1;
  sort(queries.begin(), queries.end());
  for (Query q : queries) {
    while (curr_l > q.l) {
      curr_l--;
      add(curr_l);
    }
    while (curr_r < q.r) {
      curr_r++;
      add(curr_r);
    }
    while (curr_l < q.l) {
      remove(curr_l);
      curr_l++;
    }
    while (curr_r > q.r) {
      remove(curr_r);
      curr_r--;
    }
    ans[q.idx] = diff;
  }
}
