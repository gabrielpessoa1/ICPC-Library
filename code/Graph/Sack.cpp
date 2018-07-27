void solve(int a, int p, bool f){
	int big = -1;
	for(auto &b : adj[a]){
		if(b != p && (big == -1 || en[b]-st[b] > en[big]-st[big])){
			big = b;
		}
	}
	for(auto &b : adj[a]){
		if(b == p || b == big) continue;
		solve(b, a, 0);
	}
	if(~big) solve(big, a, 1);
	add(cnt[v[a]], -1);
	cnt[v[a]]++;
	add(cnt[v[a]], +1);
	for(auto &b : adj[a]){
		if(b == p || b == big) continue;
		for(int i = st[b]; i < en[b]; i++){
			add(cnt[ett[i]], -1);
			cnt[ett[i]]++;
			add(cnt[ett[i]], +1);
		}
	}
	for(auto &q : Q[a]){
		ans[q.first] = query(mx-1)-query(q.second-1);
	}
	if(!f){
		for(int i = st[a]; i < en[a]; i++){
			add(cnt[ett[i]], -1);
			cnt[ett[i]]--;
			add(cnt[ett[i]], +1);
		}
	}
}
