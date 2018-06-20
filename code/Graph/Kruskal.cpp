// Usa a estrutura de Disjoint-Set acima

typedef pair<int, int> ii;
typedef pair<int, ii> iii;

iii e[me], mst[me];
int z, mstLen;

void add(int u, int v, int w) {
    e[z++] = iii(w, ii(u, v));
}

int kruskal() {
    int ans = 0;
    dsBuild();
    sort(e, e + z);
    for(int i = 0; i < n; i++) {
        int u = e[i].second.first, v = e[i].second.second, ew = e[i].first;
        if(dsFind(u) != dsFind(v)) {
            dsUnion(u, v);
            ans += w;
            mst[mstLen++] = e[i];
        }
    }
    return ans;
}
