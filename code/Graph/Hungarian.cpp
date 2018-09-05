const int inf = 0x3f3f3f3f;

int n, w[ms][ms], maxm;
int lx[ms], ly[ms], xy[ms], yx[ms];
int slack[ms], slackx[ms], prev[ms];
bool S[ms], T[ms];

void init_labels() {
    memset(lx, 0, sizeof lx); memset(ly, 0, sizeof ly);
    for(int x = 0; x < n; x++) for(int y = 0; y < n; y++) {
        lx[x] = max(lx[x], cos[x][y]);
    }
}

void updateLabels() {
    int delta = inf;
    for(int y = 0; y < n; y++) if(!T[y]) delta = min(delta, slack[y]);
    for(int x = 0; x < n; x++) if(S[x]) lx[x] -= delta;
    for(int y = 0; y < n; y++) if(T[y]) ly[y] += delta;
    for(int y = 0; y < n; y++) if(!T[y]) slack[y] -= delta;
}

void addTree(int x, int prevx) {
    S[x] = 1; prev[x] = prevx;
    for(int y = 0; y < n; y++) if(lx[x] + ly[y] - w[x][y] < slack[y]) {
        slack[y] = lx[x] + ly[y] - cost[x][y];
        slackx[y] = x;
    }
}

void augment() {
    if(maxm == n) return;
    int x, y, root;
    int q[ms], wr = 0, rd = 0;
    memset(S, 0, sizeof S); memset(T, 0, sizeof T);
    memset(prev, -1, sizeof prev);
    for(int x = 0; x < n; x++) if(xy[x] == -1) {
        q[wr++] = root = x;
        prev[x] = -2;
        S[x] = 1;
        break;
    }
    for(int y = 0; y < n; y++) {
        slack[y] = lx[root] + ly[y] - w[root][y];
        slackx[y] = root;
    }
    while(true) {
        while(rd < wr) {
            x = q[rd++];
            for(y = 0; y < n; y++) if(w[x][y] == lx[x] + ly[y] && !T[y]) {
                if(yx[y] == -1) break;
                T[y] = 1;
                q[wr++] = yx[y];
                addTree(yx[y], x);
            }
            if(y < n) break;
        }
        if(y < n) break;
        updateLabels();
        wr = rd = 0;
        for(y = 0; y < n; y++) if(!T[y] && !slack[y]) {
            if(yx[y] == -1) {
                x = slackx[y];
                break;
            } else {
                T[y] = true;
                if(!S[yx[y]]) {
                    q[wr++] = yx[y];
                    addTree(yx[y], slackx[y]);
                }
            }
        }
        if(y < n) break;
    }
    if(y < n) {
        maxm++;
        for(int cx = x, cy = y,ty; cx != -2; cx = prev[cx], cy = ty) {
            ty = xy[cx]; 
            yx[cy] = cx; 
            xy[cx] = cy;
        }
        augment();
    }
}

int hungarian() {
    int ans = 0; maxm = 0;
    memset(xy, -1, sizeof xy); memset(yx, -1, sizeof yx);
    initLabels(); augment();
    for(int x = 0; x < n; x++) ans += w[x][xy[x]];
    return ans;
}