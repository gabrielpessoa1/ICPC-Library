int bit[ms][ms], n, m;

void update(int v, int x, int y) {
    while(x <= n) {
        while(y <= m) {
            bit[x][y] += v;
            y += y&-y;
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