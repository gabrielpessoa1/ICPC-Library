// Usa a estrutura de Disjoint-Set acima

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
typedef vector<iii> viii;

iii e[me], z;

void add(int u, int v, int w) {
    e[z++] = iii(u, ii(v, w));
}

int kruskal() {
    int ans = 0;
    // viii mst;
    dsBuild();
    sort(e, e + z);
    for(auto i : e) {
        int u = i.second.first, v = i.second.second, w = i.first;
        if(dsFind(u) != dsFind(v)) {
            dsUnion(u, v);
            ans += w;
            // mst.push_back(i)
        }
    }
    return ans;
}