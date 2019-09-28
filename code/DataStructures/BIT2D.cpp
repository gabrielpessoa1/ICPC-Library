int bit[ms][ms], n, m;

void update(int v, int x, int y) {
  while(x <= n) {
    int yTemp = y;
    while(yTemp <= m) {
      bit[x][yTemp] += v;
      yTemp += yTemp&-yTemp;
    }
    x += x&-x;
  }
}

int query(int x, int y) {
  int r = 0;
  while(x > 0) {
    while(y > 0) {
      r += bit[x][y];
      y -= y&-y;   
    }
    x -= x&-x;
  }
  return r;
}
