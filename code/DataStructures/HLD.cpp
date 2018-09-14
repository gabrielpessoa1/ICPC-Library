// HLD + Euler Tour by adamant
// QTREE3
#include <bits/stdc++.h>
using namespace std;
const int N = 112345, inf = 0x3f3f3f3f;
 
vector<int> g[N];

void add(int a, int b){
	g[a].push_back(b), g[b].push_back(a);
}

int sz[N], par[N], h[N];

void dfs_sz(int v = 0, int p = -1){
	sz[v] = 1;
	for(auto &u: g[v]){
		if(u == p) continue;
		h[u] = 1+h[v], par[u] = v;
		dfs_sz(u, v);
		sz[v] += sz[u];
		if(g[v][0] == p || sz[u] > sz[g[v][0]]){
			swap(u, g[v][0]);
		}
	}
}
 
int t, in[N], out[N], rin[N], nxt[N];

void dfs_hld(int v = 0, int p = -1){
	in[v] = t++;
	rin[in[v]] = v;
	for(auto &u : g[v]){
		if(u == p) continue;
		nxt[u] = (u == g[v][0] ? nxt[v] : u);
		dfs_hld(u, v);
	}
	out[v] = t;
}

vector<int> tree;

void upd(int p, int value){
	for(tree[p += sz[0]] = value; p > 1; p >>= 1) tree[p>>1] = min(tree[p], tree[p^1]);
}
 
int rmq(int l, int r){
	int res = inf;
	for(l += sz[0], r += sz[0]; l < r; l >>= 1, r >>= 1) {
		if(l&1) res = min(res, tree[l++]);
		if(r&1) res = min(res, tree[--r]);
	}
	return res;
}

int up(int v){
	return (nxt[v] != v) ? nxt[v] : (~par[v] ? par[v] : v); 
}

int getLCA(int a, int b){
	while(nxt[a] != nxt[b]){
		if(h[a] == 0 || h[up(a)] < h[up(b)]) swap(a, b);
		a = up(a);
	}
	return h[a] < h[b] ? a : b;
}

int queryUp(int a, int p = 0){
	int ans = inf;
	while(nxt[a] != nxt[p]){
		ans = min(ans, rmq(in[nxt[a]], in[a]+1));
		a = par[nxt[a]];
	}
	ans = min(ans, rmq(in[p], in[a]+1)) ;
	return (ans == inf) ? -1 : rin[ans]+1;
}

int main(){
	int n, q;
	scanf("%d %d", &n, &q);
	for(int i = 0; i < n-1; i++){
		int a, b;
		scanf("%d %d", &a, &b);
		a--, b--;
		add(a, b);
	}
	
	dfs_sz();
	t = 0;
	dfs_sz();
	tree.assign(2*sz[0], inf);
	dfs_hld();
	
	for(int i = 0; i < q; i++){
		int o, v;
		scanf("%d %d", &o, &v);
		v--;
		if(o){
			printf("%d\n", queryUp(v));
		}else{
			upd(in[v], (rmq(in[v], in[v]+1) == inf) ? in[v] : inf);
		}
	}
}
