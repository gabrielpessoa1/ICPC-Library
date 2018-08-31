//Centroid decomposition1

void dfsSize(int v, int pa) {
	sz[v] = 1;
	for(int u : adj[v]) {
		if (u == pa || rem[u]) continue;
		dfsSize(u, v);
		sz[v] += sz[u];
	}
}

int getCentroid(int v, int pa, int tam) {
	for(int u : adj[v]) {
		if (u == pa || rem[u]) continue;
		if (2 * sz[u] > tam) return getCentroid(u, v, tam);
	}
	return v;
}

void decompose(int v, int pa = -1) {
	//cout << v << ' ' << pa << '\n';
	dfsSize(v, pa);
	int c = getCentroid(v, pa, sz[v]);
	//cout << c << '\n';
	par[c] = pa;
	rem[c] = 1;
	for(int u : adj[c]) {
		if (!rem[u] && u != pa) decompose(u, c);
	}
	adj[c].clear();
}

//Centroid decomposition2

void dfsSize(int v, int par) {
	sz[v] = 1;
	for(int u : adj[v]) {
		if (u == par || removed[u]) continue;
		dfsSize(u, v);
		sz[v] += sz[u];
	}
}

int getCentroid(int v, int par, int tam) {
	for(int u : adj[v]) {
		if (u == par || removed[u]) continue;
		if (2 * sz[u] > tam) return getCentroid(u, v, tam);
	}
	return v;
}

void setDis(int v, int par, int nv, int d) {
	dis[v][nv] = d;
	for(int u : adj[v]) {
		if (u == par || removed[u]) continue;
		setDis(u, v, nv, d + 1);
	}
}

void decompose(int v, int par, int nv) {
	dfsSize(v, par);
	int c = getCentroid(v, par, sz[v]);
	ct[c] = par;
	removed[c] = 1;
	setDis(c, par, nv, 0);
	for(int u : adj[c]) {
		if (!removed[u]) {
			decompose(u, c, nv + 1);
		}
	}
}
