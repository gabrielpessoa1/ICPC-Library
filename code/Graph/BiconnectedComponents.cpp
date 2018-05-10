int idx[ms], bc[me], ind, nbc, child;
stack<int> st;

void generateBc(int edge) {
    while(st.top() != edge) {
        bc[st.top()] = nbc;
        st.pop();
    }
    bc[edge] = nbc++;
}

int dfs(int v, int par = -1) {
    int low = idx[v] = ind++;
    for(int i = adj[v]; i > -1; i = ant[i]) {
        int w = to[i];
        if(idx[w] == -1) {
            if(par == -1) child++;
            st.push(i);
            int temp = dfs(w, v);
            if(par == -1 && child > 1 || ~par && temp >= idx[v]) {
                generateBc(i);
            }
            if(temp >= idx[v]) art[v] = true;
            if(temp > idx[v]) bridge[i] = true;
            low = min(low, temp);
        } else if(w != par && idx[w] < low) {
            low = idx[w];
            st.push(i);
        }
    }
    return low;
}

void biconnected() {
    ind = 0;
    nbc = 0;
    memset(idx, -1, sizeof idx);
    for(int i = 0; i < n; i++) if(idx[i] == -1) {
        child = 0;
        dfs(i);
    }
}