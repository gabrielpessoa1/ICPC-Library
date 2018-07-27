int idx[ms], low[ms], ind, comp[ms], ncomp, st[ms], top;

int dfs(int v) {
    if(~idx[v]) return idx[v] ? idx[v] : ind;
    low[v] = idx[v] = idx++;
    st[top++] = v;
    for(int w = adj[v]; ~w; w = ant[w]) {
        low[v] = min(low[v], dfs(to[w]));
    }
    if(low[v] == idx[v]) {
        idx[st[--top]] = 0;
        while(st[top] != v) {
            int w = st[--top];
            idx[w] = 0;
            low[w] = low[v];
            comp[w] = ncomp;
        }
        comp[v] = ncomp++;
    }
    return low[v];
}

bool solveSat() {
    memset(idx, -1, sizeof idx);
    ind = 1; top = -1;
    for(int i = 0; i < n; i++) dfs(i);
    for(int i = 0; i < n; i++) if(comp[i] == comp[i^1]) return false;
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