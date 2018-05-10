int adj[ms], to[me], ant[me], z;
int idx[ms], art[ms], bridge[me], ind, n, child;

void clear() {
    memset(adj, -1, sizeof adj);
    z = 0;
}

void add(int u, int v) {
    to[z] = v;
    ant[z] = adj[u];
    adj[u] = z++;
}

int dfs(int v, int par = -1) {
    int low = idx[v] = ind++;
    for(int i = adj[v]; i > -1; i = ant[i]) {
        int w = to[i];
        if(idx[w] == -1) {
            if(par == -1) child++;
            int temp = dfs(w, v);
            if(temp >= idx[v]) art[v] = true;
            if(temp > idx[v]) bridge[i] = true;
            low = min(low, temp);
        } else if(w != par) low = min(low, idx[w]);
    }
    return low;
}

void artPointAndBridge() {
    ind = 0;
    memset(idx, -1, sizeof idx);
    memset(art, 0, sizeof art);
    for(int i = 0; i < n; i++) if(idx[i] == -1) {
        child = 0;
        dfs(i);
        art[i] = child > 1;
    }
    cout << "Bridges:\n";
    for(int i = 0; i < z; i++) {
        if(bridge[i]) {
            cout << "(" << to[i] << ", " << to[i^1] << ") ";
        }
    }
    cout << "\n\nArticulation Points:\n";
    for(int i = 0; i < n; i++) {
        if(art[i]) {
            cout << i << ' ';
        }
    }
    cout << "\n";
}