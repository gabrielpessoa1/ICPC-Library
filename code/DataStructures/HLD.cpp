#include <bits/stdc++.h>
#define all(foo) foo.begin(), foo.end()
using namespace std;
const int N = 112345, inf = 0x3f3f3f3f;
 
int k, adj[N], ant[2*N], to[2*N];
 
void add(int a, int b, bool f = 1){
  ant[k] = adj[a], adj[a] = k, to[k] = b;
  k++;
  if(f) add(b, a, 0);
}
 
int par[N], h[N], big[N], sz[N];
void dfs(int v, int p, int hght){
  sz[v] = 1, par[v] = p, h[v] = hght, big[v] = -1;
  for(int i = adj[v]; ~i; i = ant[i]){
    if(to[i] != p){
      dfs(to[i], v, hght+1);
      sz[v] += sz[to[i]];
      if(big[v] == -1 || sz[big[v]] < sz[to[i]]) big[v] = to[i];
    }
  }
}
 
int chainNo, chain[N], ind[N], chainSz[N], head[N];
vector<int> tree[N];
vector<int> st[N];
 
void upd(int p, int value, vector<int> &tree){
  int n = tree.size()>>1;
  for(tree[p += n] = value; p > 1; p >>= 1) tree[p>>1] = min(tree[p], tree[p^1]);
}
 
int rmq(int l, int r, vector<int> &tree){
  int res = inf;
  int n = tree.size()>>1;
  for(l += n, r += n; l < r; l >>= 1, r >>= 1) {
    if(l&1) res = min(res, tree[l++]);
    if(r&1) res = min(res, tree[--r]);
  }
  return res;
}
 
void HLD(int v, int p, int cIn){
  if(cIn == 0) head[chainNo] = v;
  ind[v] = cIn;
  chain[v] = chainNo;
  st[chainNo].push_back(v);
  if(~big[v]){
    HLD(big[v], v, cIn+1);
  }else{
    int n = chainSz[chainNo] = st[chainNo].size();
    tree[chainNo].resize(2*n);
    fill(all(tree[chainNo]), inf);
    chainNo++;
  }
  for(int i = adj[v]; ~i; i = ant[i]){
    if(to[i] != p && to[i] != big[v]){
      HLD(to[i], v, 0);
    }
  }
}

int up(int v){
  return (head[chain[v]] != v) ? head[chain[v]] : (par[v] != -1 ? par[v] : v);
}

int LCA(int a, int b){
  while(chain[a] != chain[b]){
    if(par[a] == -1 || h[up(a)] < h[up(b)]) swap(a, b);
    a = up(a);
  }
  return h[a] < h[b] ? a : b;
}

int queryUp(int a, int b){
  int ans = -1, curr;
  while(chain[a] != chain[b]){
    curr = rmq(0, ind[a]+1, tree[chain[a]]);
    if(curr != inf) ans = st[chain[a]][curr];
    a = par[head[chain[a]]];
  }
  curr = rmq(ind[b], ind[a]+1, tree[chain[a]]);
  if(curr != inf) ans = st[chain[a]][curr];
  return ans;
}

int main(){
  int n, q;
  scanf("%d %d", &n, &q);
  memset(adj, -1, sizeof adj);
  for(int i = 0; i < n-1; i++){
    int a, b;
    scanf("%d %d", &a, &b);
    add(a, b);
  }
  dfs(1, -1, 0);
  HLD(1, -1, 0);
  for(int i = 0; i < q; i++){
    int o, v;
    scanf("%d %d", &o, &v);
    if(o){
      printf("%d\n", queryUp(v, 1));
    }else{
      int ans = rmq(ind[v], ind[v]+1, tree[chain[v]]);
      upd(ind[v], (ans == inf) ? ind[v] : inf, tree[chain[v]]);
    }
  }
} 
