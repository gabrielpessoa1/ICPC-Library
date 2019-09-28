// Usa a estrutura de Disjoint-Set acima

struct Edge{
	int u, v, cost;
	bool operator < (Edge b) {
		return cost < b.cost;
	}
};

void Kruskal() {
	vector<Edge> edge(m);
	for (int i = 0; i < m; i++) {
		cin >> edge[i].u >> edge[i].v >> edge[i].cost;
	}
	sort(edge.begin(), edge.end());
	long long total = 0;
	for (int i = 0; i < m; i++) {
		if (find(edge[i].u) != find(edge[i].v)) {
			merge(edge[i].u, edge[i].v);
			mst.push_back(edge[i]);
      total += edge[i].cost;
		}
	}
}
