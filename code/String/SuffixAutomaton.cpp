int len[ms*2], link[ms*2], nxt[ms*2][sigma];
int sz, last;
void build(string &s) {
  len[0] = 0; link[0] = -1;
  sz = 1; last = 0;
  memset(nxt[0], -1, sizeof nxt[0]);
  for(char ch : s) {
    int c = ch-'a', cur = sz++;
    len[cur] = len[last]+1;
    memset(nxt[cur], -1, sizeof nxt[cur]);
    int p = last;
    while(p != -1 && nxt[p][c] == -1) {
      nxt[p][c] = cur; p = link[p];
    }
    if(p == -1) {
      link[cur] = 0;
    } else {
      int q = nxt[p][c];
      if(len[p] + 1 == len[q]) {
        link[cur] = q;
      } else {
        len[sz] = len[p]+1; link[sz] = link[q];
        memcpy(nxt[sz], nxt[q], sizeof nxt[q]);
        while (p != -1 && nxt[p][c] == q) {
          nxt[p][c] = sz; p = link[p];
        }
        link[q] = link[cur] = sz++;
      }
    }
    last = cur;
  }
}