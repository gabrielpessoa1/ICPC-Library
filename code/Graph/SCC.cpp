int idx[ms], low[ms], ind, comp[ms], ncomp;
stack<int> st;

int dfs(int v) {
    if(~idx[v]) return idx[v] ? idx[v] : ind;
    low[v] = idx[v] = idx++;
    s.push(v);
    onStack[v] = true;
    for(int w = adj[x]; ~w; w = ant[w]) {
        low[v] = min(low[v], dfs(to[w]));
    }
    if(low[v] == idx[v]) {
        while(!s.empty()) {
            int w = s.top();
            s.pop();
            idx[w] = 0;
            low[w] = low[v];
            comp[w] = ncomp;
        }
        ncomp++;
    }
    return low[v];
}

bool solveSat() {
    memset(idx, -1, sizeof idx);
    ind = 1;
    for(int i = 0; i < n; i++) dfs(i);
    for(int i = 0; i < n; i++) if(low[i] == low[i^1]) return false;
    return true;
}

// Operacoes comuns de 2-sat
// ~v = "nao v"
#define trad(v) (v<0?((~v)*2)^1:v*2)
void addImp(int a, int b) { add(trad(a), trad(b)); }
void addOr(int a, int b) { addImp(~a, b); addImp(~b, a); }
void addEqual(int a, int b) { addOr(a, ~b); addOr(~a, b); }
void addDiff(int a, int b) { addEqual(a, ~b); }
// valoracao: value[v] = comp[trad(v)] < comp[trad(~v)]