// Usa a estrutura de Disjoint-Set acima

typedef pair<int, int> ii;
typedef pair<int, ii> iii;

iii e[me], mst[me];
int z, mstLen;

void add(int u, int v, int w) {
    e[z++] = iii(u, ii(v, w));
}

int kruskal() {
    int ans = 0;
    dsBuild();
    sort(e, e + z);
    for(auto i : e) {
        int u = i.second.first, v = i.second.second, w = i.first;
        if(dsFind(u) != dsFind(v)) {
            dsUnion(u, v);
            ans += w;
            mst[mstLen++] = i;
        }
    }
    return ans;
}