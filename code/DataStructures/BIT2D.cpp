int bit[ms][ms];
void update(int v, int x, int y) {
  for (x++, y++; x < ms; x += x&-x) {
    for (int y1 = y+1; y1 < ms; y1 += y1&-y1) {
      bit[x][y1] += v;
    }
  }
}
int query(int x, int y) {
  int r = 0;
  for (x++, y++; x > 0; x -= x&-x) {
    for (int y1 = y; y1 > 0; y1 -= y1&-y1) {
      r += bit[x][y1];
    }
  }
  return r;
}
