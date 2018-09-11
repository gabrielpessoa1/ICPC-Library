//HLD + Euler Tour by adamant http://codeforces.com/blog/entry/53170
void dfs_sz(int v = 0)
{
	sz[v] = 1;
	for(auto &u: g[v])
	{
		dfs_sz(u);
		sz[v] += sz[u];
		if(sz[u] > sz[g[v][0]])
			swap(u, g[v][0]);
	}
}

void dfs_hld(int v = 0)
{
	in[v] = t++;
	rin[in[v]] = v;
	for(auto u: g[v])
	{
		nxt[u] = (u == g[v][0] ? nxt[v] : u);
		dfs_hld(u);
	}
	out[v] = t;
}
